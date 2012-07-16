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


#ifndef COCOS2DX_CCNETWORK_H
#define COCOS2DX_CCNETWORK_H

#include "cocos2d.h"
#include "CCHttpClient.h"

/**
 @brief    The cocos2d Network Module.
           implement send/dispatch/release net package
 */

NS_CC_NETWORK_BEGIN 

class CC_DLL CCNetwork {
public:
    /** returns a shared instance of the network */
	static CCNetwork* sharedNetwork(void)
	{
		if (!m_pInstance)  
		{
			m_pInstance = new CCNetwork();
			m_pInstance->init();
		}
		return m_pInstance; 
	}
    
    /* send net data to server */
    void sendNetPackage(std::string strUrl, int mode, const char *buf, cocos2d::SEL_CallFuncND selector, cocos2d::CCObject *rec);
    
    /* dispatch data responsed from server */
    void dispatchNetPackage();

protected:    
    virtual bool init(void);

protected:
    CCNetwork(void);
    virtual ~CCNetwork(void);
	static CCNetwork *m_pInstance;
    
    class CCSingletonRelease //purpose of the class is only to delete instance of CCNetwork
	{  
	public:  
		~CCSingletonRelease()  
		{  
            CC_SAFE_DELETE(CCNetwork::m_pInstance); 
		}  
	};  
	static CCSingletonRelease Garbo; //destructor will be invoked before program exit  
};

NS_CC_NETWORK_END
#endif
