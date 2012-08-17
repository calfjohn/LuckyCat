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
    kModeTask = 0,
    kModeEvent,
    kModeActor,
    kModeBox,
    kModeBattle,
	//add more

	MOD_COUNT,
};

const std::string g_modNames[MOD_COUNT] = {
    "task",
    "event",
    "actor",
    "box",
    "battle",
    
    //add more
};

enum DoRequestType
{
	kDoGetActorInfo=0,
    kDoOpenBox,
	kDoGetUserInfo,
    kDoFight1,
    kDoFight2,
    kDoGetBasicInfo,
	DO_COUNT,
};

const std::string g_doNames[DO_COUNT] = {
	"getActorInfo",
    "openBox",
	"getUserInfo",
    "fight1",
    "fight2",
    "getBasicInfo",
};

const int g_doVersion[DO_COUNT] = {
	1,
    1,
    1,
    1,
    1,
    1,
};

#endif
