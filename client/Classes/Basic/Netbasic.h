//
//  NetManager.h
//  cocos2dx
//
//  Created by Cocos2d on 12-8-9.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//


#ifndef LuckyCat_Netbasic_h
#define LuckyCat_Netbasic_h

enum ModeRequestType
{
	kModeStart = 0,
	kModeGame,
	//add more

	MOD_COUNT,
};

const std::string g_modNames[MOD_COUNT] = {
	"start",
	"game",
	//add more
};

enum DoRequestType
{
	kDoLogin = 0,
	kDoGetUserInfo,
    
	DO_COUNT,
};

const std::string g_doNames[DO_COUNT] = {
	"login",
	"getUserInfo",
};

const std::string g_url[DO_COUNT] = {
	"login/",
    "game/getUserInfo/",
};

const int g_doVersion[DO_COUNT] = {
	1,
    1,
};

#endif
