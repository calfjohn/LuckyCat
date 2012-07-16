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

#include "CCHttpClient.h"

NS_CC_NETWORK_BEGIN

#define CC_HTTPCLIENT_TIMEOUT 10

CCHttpClient* CCHttpClient::m_pInstance = NULL;
CCHttpClient::CCSingletonRelease CCHttpClient::Garbo;

CCHttpClient::CCHttpClient(void) : 
m_bDebug(false)
{
    curl_global_init(CURL_GLOBAL_NOTHING);
    
    /* init easy handle */
    m_curl =curl_easy_init();
}

CCHttpClient::~CCHttpClient(void)
{
	/* cleanup easy handle */
	curl_easy_cleanup(m_curl);
    
    curl_global_cleanup();
}

bool CCHttpClient::init()
{
    if (m_curl == NULL) 
    {
        return false;
    }
    /* reset all curl option */
    curl_easy_setopt(m_curl, CURLOPT_HTTPGET, 1L); 

	/* init curl option */    
	curl_easy_setopt(m_curl, CURLOPT_CONNECTTIMEOUT, CC_HTTPCLIENT_TIMEOUT);
	curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, CC_HTTPCLIENT_TIMEOUT);
    curl_easy_setopt(m_curl, CURLOPT_READFUNCTION, NULL);
	curl_easy_setopt(m_curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(m_curl, CURLOPT_DEBUGFUNCTION, &CCHttpClient::OnDebug);
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &CCHttpClient::WriteCallback);   
    curl_easy_setopt(m_curl, CURLOPT_VERBOSE, m_bDebug ? 1: 0);

    return true;
}

int CCHttpClient::OnDebug(CURL *, curl_infotype itype, char * pData, size_t size, void *)
{
	if(itype == CURLINFO_TEXT)
	{
		//printf("[TEXT]%s\n", pData);
	}
	else if(itype == CURLINFO_HEADER_IN)
	{
		printf("[HEADER_IN]%s\n", pData);
	}
	else if(itype == CURLINFO_HEADER_OUT)
	{
		printf("[HEADER_OUT]%s\n", pData);
	}
	else if(itype == CURLINFO_DATA_IN)
	{
		printf("[DATA_IN]%s\n", pData);
	}
	else if(itype == CURLINFO_DATA_OUT)
	{
		printf("[DATA_OUT]%s\n", pData);
	}
	return 0;
}

void CCHttpClient::setDebug(bool bDebug)
{
	m_bDebug = bDebug;
}

bool CCHttpClient::getDebug()
{
	return m_bDebug;
}

size_t CCHttpClient::WriteCallback(void* buffer, size_t size, size_t nmemb, void* lpVoid)
{
	std::string* str = dynamic_cast<std::string*>((std::string *)lpVoid);
	if( NULL == str || NULL == buffer )
	{
		return -1;
	}
    
    char* pData = (char*)buffer;
    str->append(pData, size * nmemb);
	return nmemb;
}

CURLcode CCHttpClient::Post(const std::string & strUrl, const std::string & strPost, std::string & strResponse)
{
    init();
    
	CURLcode res;

	curl_easy_setopt(m_curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(m_curl, CURLOPT_POST, 1);
	curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, strPost.c_str());
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    res = curl_easy_perform(m_curl);

	return res;
}

CURLcode CCHttpClient::Get(const std::string & strUrl, std::string & strResponse)
{
    init();
    
	CURLcode res;

    curl_easy_setopt(m_curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(m_curl, CURLOPT_POST, 0);    
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&strResponse);
	res = curl_easy_perform(m_curl);

	return res;
}
/*
CURLcode CCHttpClient::Posts(const std::string & strUrl, const std::string & strPost, std::string & strResponse, const char * pCaPath)
{
    init();
    
	CURLcode res;

    curl_easy_setopt(m_curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(m_curl, CURLOPT_POST, 1);
	curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, strPost.c_str());
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&strResponse);
	if(NULL == pCaPath)
	{
		curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, false);
	}
	else
	{
		//缺省情况就是PEM，所以无需设置，另外支持DER
		//curl_easy_setopt(m_curl,CURLOPT_SSLCERTTYPE,"PEM");
		curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, true);
		curl_easy_setopt(m_curl, CURLOPT_CAINFO, pCaPath);
	}

	res = curl_easy_perform(m_curl);

	return res;
}

CURLcode CCHttpClient::Gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath)
{
    init();
    
	CURLcode res;

	curl_easy_setopt(m_curl, CURLOPT_URL, strUrl.c_str());
	curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, (void *)&strResponse);
	if(NULL == pCaPath)
	{
		curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, false);
	}
	else
	{
		curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, true);
		curl_easy_setopt(m_curl, CURLOPT_CAINFO, pCaPath);
	}
	res = curl_easy_perform(m_curl);
    
	return res;
}
*/

NS_CC_NETWORK_END
