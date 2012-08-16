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
    kModeTask,
    kModeActor,
    kModeBox,
    kModeBattle,
	//add more

	MOD_COUNT,
};

const std::string g_modNames[MOD_COUNT] = {
	"start",
	"game",
    "task",
    "actor",
    "box",
    "battle",
    
    //add more
};

enum DoRequestType
{
	kDoLogin = 0,
	kDoGetActorInfo,
    kDoOpenBox,
	kDoGetUserInfo,
    kDoFight1,
    kDoGetBasicInfo,
    kDoGetEquipmentInfo,
    
	DO_COUNT,
};

const std::string g_doNames[DO_COUNT] = {
	"login",
	"getActorInfo",
    "openBox",
	"getUserInfo",
    "fight1",
    "getBasicInfo",
    "getEquipmentInfo",
};

const std::string g_url[DO_COUNT] = {
	"login/",
    "actor/getActorInfo/",
    "box/openBox/",
    "getUserInfo/",
    "battle/fight1/",
    "actor/getBasicInfo/",
    "actor/getEquipmentInfo",
};

const int g_doVersion[DO_COUNT] = {
	1,
    1,
    1,
    1,
    1,
    1,
    1,
};

#endif
