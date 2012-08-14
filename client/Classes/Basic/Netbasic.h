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
    kModeBattle,
	//add more

	MOD_COUNT,
};

const std::string g_modNames[MOD_COUNT] = {
	"start",
	"game",
    "battle",
    
    //add more
};

enum DoRequestType
{
	kDoLogin = 0,
	kDoGetUserInfo,
    kDoFight1,
    
	DO_COUNT,
};

const std::string g_doNames[DO_COUNT] = {
	"login",
	"getUserInfo",
    "fight1",
};

const std::string g_url[DO_COUNT] = {
	"login/",
    "getUserInfo/",
    "battle/fight1/",
};

const int g_doVersion[DO_COUNT] = {
	1,
    1,
    1,
};

#endif
