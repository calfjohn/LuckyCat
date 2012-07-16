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


#ifndef COCOS2DX_HTTPCLIENT_H
#define COCOS2DX_HTTPCLIENT_H

#include "cocos2d.h"
#include "curl/curl.h"

/**
 @brief    The cocos2d HttpClient Module.
           implement asyn/sync request base on curl
           thanks to huyiyang2010
           LINK: http://blog.csdn.net/huyiyang2010/article/details/7664201
 */

NS_CC_NETWORK_BEGIN

class CCHttpClient {
public:
    /** returns a shared instance of the HttpClient */
	static CCHttpClient* sharedHttpClient(void)
	{
		if (!m_pInstance)  
		{
			m_pInstance = new CCHttpClient();
			m_pInstance->init();
		}
		return m_pInstance; 
	}

	/** HTTP POST REQUEST*/
	CURLcode Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse);
    
	/** HTTP GET REQUEST*/
	CURLcode Get(const std::string & strUrl, std::string & strResponse);
    
	/** HTTPS POSTS QEQUEST,no certification */
//	CURLcode Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath = NULL);
    
	/** HTTPS GETS,no certification*/
//	CURLcode Gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath = NULL);
    
    CC_PROPERTY(bool, m_bDebug, Debug);
        
protected:    
    virtual bool init(void);

    static int OnDebug(CURL *, curl_infotype itype, char * pData, size_t size, void *);
    
    static size_t WriteCallback( void *buff, size_t size, size_t nmemb, void *lpVoid);   
    
protected:
    CCHttpClient(void);
    virtual ~CCHttpClient(void);
	static CCHttpClient *m_pInstance;
    
    class CCSingletonRelease //purpose of the class is only to delete instance of CCHttpClient
	{  
	public:  
		~CCSingletonRelease()  
		{  
            CC_SAFE_DELETE(CCHttpClient::m_pInstance); 
		}  
	};  
	static CCSingletonRelease Garbo; //destructor will be invoked before program exit  
    
    CURL * m_curl;
};

NS_CC_NETWORK_END
#endif
