//
//  NetManager.h
//  cocos2dx
//
//  Created by Cocos2d on 12-8-9.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "NetManager.h"
#include "BasicFunction.h"
#include "CCNetwork.h"

USING_NS_CC_NETWORK;
using namespace std;

NetManager* NetManager::m_pInstance = NULL;
NetManager::Release NetManager::Garbo;

USING_NS_CC_NETWORK;
using namespace std;

bool NetManager::init(void)
{
//	m_mapError[-1] = "通讯错误或者返回的json数据内容错误";
//	m_mapError[6] = "订单无效";
//	m_mapError[7] = "不能充值或支付";

    m_strToken = "0";
    m_strUrl = "http://192.168.0.128:22222/";
    m_nIndex = 1;
	return true;
}

bool NetManager::send(ModeRequestType modEnum, DoRequestType doEnum,const char* requestData, cocos2d::SEL_CallFuncND selector, cocos2d::CCObject *rec)
{
    CCNetwork::sharedNetwork()->sendNetPackage(GenerateUrl(doEnum), 1, GeneratePost(modEnum, doEnum, requestData).c_str(), selector, rec);
    
    return true;
}

string NetManager::GeneratePost(ModeRequestType modEnum, DoRequestType doEnum,const char* requestData)
{
	char temp[10240];
	if (requestData == NULL || strlen(requestData) == 0)
	{
		sprintf(temp, "{\"header\":{\"token\": \"%s\", \"index\": %d}, \"meta\":{\"mod\": \"%s\", \"do\": \"%s\", \"ver\":%d, \"in\":{}}}}", m_strToken.c_str(), m_nIndex++, g_modNames[modEnum].c_str(), g_doNames[doEnum].c_str(), g_doVersion[doEnum]);
	} 
	else
	{
		sprintf(temp, "{\"header\":{\"token\": \"%s\", \"index\": %d}, \"meta\":{\"mod\": \"%s\", \"do\": \"%s\", \"ver\":%d,  \"in\":{%s}}}", m_strToken.c_str(), m_nIndex++, g_modNames[modEnum].c_str(), g_doNames[doEnum].c_str(), g_doVersion[doEnum], requestData);
	}
        
	return string(temp);
}

string NetManager::GenerateUrl(DoRequestType doEnum)
{
    return m_strUrl + g_url[doEnum];
}

string NetManager::GetErrorInfo(int errorCode)
{
	map<int, string>::iterator tempIter;
	tempIter = m_mapError.find(errorCode);
	if (tempIter != m_mapError.end())
	{
		return (*tempIter).second;
	}
	
	return "无效的错误代码：" + ConvertToString(errorCode);
}