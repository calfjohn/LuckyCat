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

#ifndef cocos2dx_CCMessageQueue_h
#define cocos2dx_CCMessageQueue_h

#include "cocos2d.h"
#include "curl/curl.h"

USING_NS_CC;

NS_CC_NETWORK_BEGIN

typedef struct _RequestInfo
{
    unsigned int requestId;         //request id
    std::string  strUrl;            //request url
    std::string  strRequestData;    //request data
    std::string  strResponseData;   //response data
    CCObject*       target;         //callback listener
    SEL_CallFuncND  pfnSelector;    //callback selector
    CURLcode    stateCode;          //response state
    cc_timeval  sendTime;           //send time
    cc_timeval  responseTime;       //response time
    int         requestMode;        //http mode 0:get 1 and orther numbers:post
}RequestInfo;

class CCCallbackNode;

class CCMessageQueue {
    friend class CCNetwork;
public:
	static CCMessageQueue* sharedMessagequeue(void)
	{
		if (!m_pInstance)  
		{
			m_pInstance = new CCMessageQueue();
			m_pInstance->init();
		}
		return m_pInstance; 
	}    
       
    CCCallbackNode *getCallbackNode();
    
protected:
    /* push request on request queue, First Input First Output */
    void push(std::string strUrl, int mode, const char *requestData, SEL_CallFuncND selector, CCObject *rec);

    /* pop up a valid response */
    RequestInfo *popUp();
private:
    CCMessageQueue();
    virtual ~CCMessageQueue();
    
	static CCMessageQueue *m_pInstance;
    
    class CCSingletonRelease //purpose of the class is only to delete instance of CCMessageQueue
	{  
	public:  
		~CCSingletonRelease()  
		{  
            CC_SAFE_DELETE(CCMessageQueue::m_pInstance); 
		}  
	};  
	static CCSingletonRelease Garbo; //destructor will be invoked before program exit  
    
private:
    virtual bool init(void);
    
    /* pop up a request and put it into response queue */
    RequestInfo *popUpRequest();

    void pushResponse(RequestInfo *requestInfo);
    
    /*wait request by semaphore send it to server */
    static void* requestThread(void* data);

    /*wait response by semaphore and invoke callback function */    
    static void* responseThread(void* data);
    
    std::vector<RequestInfo *> m_requestQueue;
    
    std::vector<RequestInfo *> m_responseQueue;
    
    static bool m_bQuit;
};

NS_CC_NETWORK_END


#endif
