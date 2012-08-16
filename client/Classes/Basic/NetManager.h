//
//  NetManager.h
//  cocos2dx
//
//  Created by Cocos2d on 12-8-9.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#if !defined _NetManager_H__
#define _NetManager_H__

#include <string>
#include <map>
#include "json.h"
#include "Netbasic.h"
#include "cocos2d.h"
#include "CCNetwork.h"

class NetManager
{
public:
	bool send(ModeRequestType modEnum, DoRequestType doEnum, cocos2d::SEL_CallFuncND selector, cocos2d::CCObject *rec, const char* requestData);
    
    bool sendEx(ModeRequestType modEnum, DoRequestType doEnum, cocos2d::SEL_CallFuncND selector, cocos2d::CCObject *rec, const char* format,...);

    std::string GetLastError(){return m_lastError;}
    
    std::string GetLastSuccess(){return m_lastSuccess;}
    
    const char* response(void *data);
public:
	static NetManager* shareNetManager(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new NetManager();
			m_pInstance->init();
		}
		return m_pInstance;
	}

private:
	NetManager(void){};
    ~NetManager(void){};
	
	static NetManager *m_pInstance;
    
	class Release	//它的唯一作用是在析构函数中删除单例
	{
	public:
		~Release()
		{
			if(NetManager::m_pInstance)
			{
				delete NetManager::m_pInstance;
				NetManager::m_pInstance = NULL;
			}
		}
	};
	static Release Garbo;

private:
	bool init(void);
    
    std::string GetErrorInfo(int errorCode);

	std::string GeneratePost(ModeRequestType modEnum, DoRequestType doEnum,const char* requestData);

	std::string GenerateUrl(ModeRequestType modEnum, DoRequestType doEnum);

	std::map<int, std::string> m_mapError;
    
	std::string m_lastError;		//最近一条通讯业务错误的信息
    
	std::string m_lastSuccess;	//最近一条通讯业务成功的信息
    
    std::string m_strToken;
    
    std::string m_strUrl;
    
    int m_nIndex;
};

#endif