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

#include "CCNetwork.h"
#include "CCMessageQueue.h"

NS_CC_NETWORK_BEGIN

CCNetwork* CCNetwork::m_pInstance = NULL;
CCNetwork::CCSingletonRelease CCNetwork::Garbo;

CCNetwork::CCNetwork(void)
{
    
}

CCNetwork::~CCNetwork(void)
{
}

bool CCNetwork::init()
{
    return true;
}

void CCNetwork::sendNetPackage(std::string strUrl, int mode, const char *buf, cocos2d::SEL_CallFuncND selector, cocos2d::CCObject *rec)
{
    CCLOG("url:%s",strUrl.c_str());
    CCLOG("post:%s", buf);
    
    CCMessageQueue::sharedMessagequeue()->push(strUrl, mode, buf, selector, rec);
}

void CCNetwork::dispatchNetPackage()
{
    RequestInfo *pRequestInfo = CCMessageQueue::sharedMessagequeue()->popUp();
    if (!pRequestInfo)
    {
        return;
    }
    
    ((pRequestInfo->target)->*(pRequestInfo->pfnSelector))(NULL, pRequestInfo);
    
    CC_SAFE_DELETE(pRequestInfo);
}


NS_CC_NETWORK_END
