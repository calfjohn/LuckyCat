/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCMessageQueue.h"
#include "CCHttpClient.h"
#include <semaphore.h>
#include <errno.h>
#include <pthread.h>
#include "CCCallbackNode.h"

NS_CC_NETWORK_BEGIN

static pthread_mutex_t      s_asyncRequestMutex;
static pthread_mutex_t      s_asyncResponseMutex;
static pthread_t s_requestThread;
static pthread_t s_responseThread;
static unsigned int s_requestCount = 1;
static sem_t* s_pSem = NULL;
static sem_t* s_pSemResponse = NULL;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#define CC_ASYNC_TEXTURE_CACHE_USE_NAMED_SEMAPHORE 1
#else
#define CC_ASYNC_TEXTURE_CACHE_USE_NAMED_SEMAPHORE 0
#endif

#if CC_ASYNC_TEXTURE_CACHE_USE_NAMED_SEMAPHORE
#define CC_ASYNC_TEXTURE_CACHE_SEMAPHORE "ccnetworkAsync"
#define CC_ASYNC_TEXTURE_CACHE_SEMAPHORE_RESPONSE "ccnetworkAsyncResponse"
#else
static sem_t s_sem;
static sem_t s_semResponse;
#endif

bool CCMessageQueue::m_bQuit = false;
CCMessageQueue* CCMessageQueue::m_pInstance = NULL;
CCMessageQueue::CCSingletonRelease CCMessageQueue::Garbo;

CCMessageQueue::CCMessageQueue()
{
    m_pCallbackNode = CCCallbackNode::node();
    
    m_requestQueue.clear();
    m_responseQueue.clear();
}

CCMessageQueue::~CCMessageQueue()
{
    m_bQuit = true;
    pthread_kill(s_requestThread, 0);
    pthread_kill(s_responseThread, 0);

    if (s_pSem != NULL)
    {
        sem_post(s_pSem);
    }
    
    if (s_pSemResponse != NULL)
    {
        sem_post(s_pSemResponse);
    }
    
    pthread_mutex_destroy(&s_asyncRequestMutex);
    pthread_mutex_destroy(&s_asyncResponseMutex);

    std::vector<RequestInfo *>::iterator iterTemp;
    for (iterTemp = m_requestQueue.begin(); iterTemp != m_requestQueue.end(); iterTemp++) 
    {
        CC_SAFE_DELETE(*iterTemp);
    }
   
    for (iterTemp = m_responseQueue.begin(); iterTemp != m_responseQueue.end(); iterTemp++) 
    {
        CC_SAFE_DELETE(*iterTemp);
    }        
}

bool CCMessageQueue::init(void)
{
#if CC_ASYNC_TEXTURE_CACHE_USE_NAMED_SEMAPHORE
        cc_timeval  tempTime;
        CCTime::gettimeofdayCocos2d(&tempTime, NULL);
        char szName[100] = {0};
        sprintf(szName, "%ld", tempTime.tv_sec*1000 + tempTime.tv_usec/1000);
        s_pSem = sem_open(szName, O_CREAT, 0644, 0);
        if( s_pSem == SEM_FAILED )
        {
            CCLOG( "CCTextureCache async thread semaphore init error: %s\n", strerror( errno ) );
            s_pSem = NULL;
            return false;
        }
#else
        int semInitRet = sem_init(&s_sem, 0, 0);
        if( semInitRet < 0 )
        {
            CCLOG( "CCTextureCache async thread semaphore init error: %s\n", strerror( errno ) );
            return false;
        }
        s_pSem = &s_sem;
#endif
    
#if CC_ASYNC_TEXTURE_CACHE_USE_NAMED_SEMAPHORE
    sprintf(szName, "%ldResponse", tempTime.tv_sec*1000 + tempTime.tv_usec/1000);    
    s_pSemResponse = sem_open(szName, O_CREAT, 0644, 0);
    if( s_pSemResponse == SEM_FAILED )
    {
        CCLOG( "CCTextureCache async thread semaphore init error: %s\n", strerror( errno ) );
        s_pSemResponse = NULL;
        return false;
    }
#else
    semInitRet = sem_init(&s_semResponse, 0, 0);
    if( semInitRet < 0 )
    {
        CCLOG( "CCTextureCache async thread semaphore init error: %s\n", strerror( errno ) );
        return false;
    }
    s_pSemResponse = &s_semResponse;
#endif    

    pthread_mutex_init(&s_asyncRequestMutex, NULL);
    pthread_mutex_init(&s_asyncResponseMutex, NULL);
    pthread_create(&s_requestThread, NULL, requestThread, NULL);
    pthread_create(&s_responseThread, NULL, responseThread, NULL);

    return true;
}

void CCMessageQueue::push(std::string strUrl, int mode, const char * requestData, SEL_CallFuncND selector, CCObject *rec)
{
    RequestInfo *tempInfo = new RequestInfo();
    tempInfo->requestId = s_requestCount++;
	tempInfo->strUrl = strUrl;
	if(requestData){
		tempInfo->strRequestData = requestData;
	}else{
		tempInfo->strRequestData.clear();
	}
    tempInfo->strResponseData.clear();
    tempInfo->target = rec;
    tempInfo->pfnSelector = selector;
    tempInfo->stateCode = CURL_LAST;
    tempInfo->requestMode = mode;
    CC_SAFE_RETAIN(tempInfo->target);

    CCTime::gettimeofdayCocos2d(&tempInfo->sendTime, NULL);
    
    pthread_mutex_lock(&s_asyncRequestMutex);
    m_requestQueue.insert(m_requestQueue.begin(), tempInfo);
    pthread_mutex_unlock(&s_asyncRequestMutex);
    
    CCLOG("request %d send", tempInfo->requestId);//, tempInfo->sendTime.tv_usec*1000+tempInfo->sendTime.tv_usec/1000);

    sem_post(s_pSem);
}

RequestInfo* CCMessageQueue::popUpRequest()
{
    // pop up request from request queue
    RequestInfo *tempInfo = NULL;
    
    pthread_mutex_lock(&s_asyncRequestMutex);
    if (!m_requestQueue.empty())
    {
        tempInfo = m_requestQueue.back();
        m_requestQueue.pop_back();
    }
    pthread_mutex_unlock(&s_asyncRequestMutex);
    
    // push request on response queue    
    if (tempInfo) 
    {
        pushResponse(tempInfo);
    }
    
    return tempInfo;
}


void CCMessageQueue::pushResponse(RequestInfo *requestInfo)
{    
    pthread_mutex_lock(&s_asyncResponseMutex);
    m_responseQueue.insert(m_responseQueue.begin(), requestInfo);
    pthread_mutex_unlock(&s_asyncResponseMutex);
}

RequestInfo* CCMessageQueue::popUp()
{
    RequestInfo *tempInfo = NULL;
    
    pthread_mutex_lock(&s_asyncResponseMutex);
    if (!m_responseQueue.empty())
    {
        tempInfo = m_responseQueue.back();
        if (tempInfo->stateCode == CURL_LAST) 
        {
            //wait for response
            tempInfo = NULL;
        }
        else
        {
            CC_SAFE_RELEASE(tempInfo->target);
            m_responseQueue.pop_back();
        }
    }
    pthread_mutex_unlock(&s_asyncResponseMutex);
    
    if (tempInfo) 
    {
        CCLOG("request %d back at %.2f(send:%d response:%d)", tempInfo->requestId, CCTime::timersubCocos2d(&tempInfo->sendTime, &tempInfo->responseTime), tempInfo->sendTime.tv_sec*1000+tempInfo->sendTime.tv_usec/1000, tempInfo->responseTime.tv_sec*1000+tempInfo->responseTime.tv_usec/1000); 
    }
    
    return tempInfo;
}

void* CCMessageQueue::requestThread(void* data)
{
    // create autorelease pool for iOS
    CCThread thread;
    thread.createAutoreleasePool();
    
    while (!m_bQuit)
    {
        // wait for sem_post
        int semWaitRet = sem_wait(s_pSem);
        if( semWaitRet < 0 )
        {
            CCLOG( "CCTextureCache async thread semaphore error: %s\n", strerror( errno ) );
            break;
        }
        
        RequestInfo *pRequestInfo = CCMessageQueue::sharedMessagequeue()->popUpRequest();
        if (!pRequestInfo)
        {
            continue;
        }
        
        if (!pRequestInfo->requestMode) 
        {
            pRequestInfo->stateCode = CCHttpClient::sharedHttpClient()->Get(pRequestInfo->strUrl, pRequestInfo->strResponseData);
        }
        else 
        {
            pRequestInfo->stateCode = CCHttpClient::sharedHttpClient()->Post(pRequestInfo->strUrl, pRequestInfo->strRequestData, pRequestInfo->strResponseData);
        }
        
        CCTime::gettimeofdayCocos2d(&pRequestInfo->responseTime, NULL);

        sem_post(s_pSemResponse);
    }
    
    if( s_pSem != NULL )
    {
#if CC_ASYNC_TEXTURE_CACHE_USE_NAMED_SEMAPHORE
        sem_unlink(CC_ASYNC_TEXTURE_CACHE_SEMAPHORE);
        sem_close(s_pSem);
#else
        sem_destroy(s_pSem);
#endif
        s_pSem = NULL;
    }
    
    return 0;
}

void* CCMessageQueue::responseThread(void* data)
{
    // create autorelease pool for iOS
    CCThread thread;
    thread.createAutoreleasePool();
    
    while (!m_bQuit)
    {
        // wait for sem_post
        int semWaitRet = sem_wait(s_pSemResponse);
        if( semWaitRet < 0 )
        {
            CCLOG( "CCTextureCache async thread semaphore error: %s\n", strerror( errno ) );
            break;
        }
        
        RequestInfo *pRequestInfo = NULL;
        while (true) 
        {
            pRequestInfo = CCMessageQueue::sharedMessagequeue()->popUp();
            if (!pRequestInfo)
            {
                break;
            }   
                        
            CCMessageQueue::sharedMessagequeue()->getCallbackNode()->callback(pRequestInfo);
        }
    }
    
    if( s_pSemResponse != NULL )
    {
#if CC_ASYNC_TEXTURE_CACHE_USE_NAMED_SEMAPHORE
        sem_unlink(CC_ASYNC_TEXTURE_CACHE_SEMAPHORE_RESPONSE);
        sem_close(s_pSemResponse);
#else
        sem_destroy(s_pSemResponse);
#endif
        s_pSemResponse = NULL;
    }
    
    return 0;
}

NS_CC_NETWORK_END