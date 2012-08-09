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

#include "CCCallbackNode.h"

NS_CC_NETWORK_BEGIN

CCCallbackNode * CCCallbackNode::node(void)
{
    return CCCallbackNode::create();
}

CCCallbackNode * CCCallbackNode::create(void)
{
	CCCallbackNode * pRet = new CCCallbackNode();
	pRet->autorelease();
    pRet->schedule(schedule_selector(CCCallbackNode::performedCallback));
    pRet->pauseSchedulerAndActions();
    
	return pRet;
}

void CCCallbackNode::callback(void* data)
{
    m_pRequestInfo =  (RequestInfo *)data;
    this->resumeSchedulerAndActions();
}

void CCCallbackNode::performedCallback(float dt)
{
    CCLOG("%s", m_pRequestInfo->strResponseData.c_str());

    if(m_pRequestInfo && m_pRequestInfo->target && m_pRequestInfo->pfnSelector)
    {
        ((m_pRequestInfo->target)->*(m_pRequestInfo->pfnSelector))(this, m_pRequestInfo);

        CC_SAFE_DELETE(m_pRequestInfo);
    }
    
    this->pauseSchedulerAndActions();
}

NS_CC_NETWORK_END