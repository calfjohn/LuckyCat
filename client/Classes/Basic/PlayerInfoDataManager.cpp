//
//  PlayerInfoDataManager.cpp
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-20.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "PlayerInfoDataManager.h"
#include "json/json.h"
#include "CppSQLite3.h"

USING_NS_CC;

PlayerInfoDataManager *PlayerInfoDataManager::m_pInstance = NULL;
PlayerInfoDataManager::XLRelease PlayerInfoDataManager::Garbo;


PlayerInfoDataManager::PlayerInfoDataManager(){
    m_curUserInfo = NULL;
}
PlayerInfoDataManager::~PlayerInfoDataManager(){
    if (m_curUserInfo != NULL) {
        delete m_curUserInfo;
        m_curUserInfo = NULL;
    }
    
}

bool PlayerInfoDataManager::init(){
    string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/luckycat.sqlite");
    
    CppSQLite3DB db;
    db.open(path.c_str());
	if (!db.isOpen())
	{
		return false;
	}
    CppSQLite3Query q = db.execQuery("select * from dict_equipment;");
    while(!q.eof())
    {
        stActorUserEquipInfo  tempInfo;
        
        tempInfo.userEquipId = q.getIntField("id");
        tempInfo.userEquipType = q.getIntField("class");
        tempInfo.userPutOn = false;
        
        stActorEquipInfo *equipInfo = new stActorEquipInfo();
        equipInfo->equipName = q.getStringField("name");
        equipInfo->equipImageId = q.getIntField("image_id");
        equipInfo->equipLife = q.getIntField("life");
        equipInfo->equipLevelLimit = q.getIntField("level_limit");
        equipInfo->equipAttack = q.getIntField("attack");
        equipInfo->equipDefence = q.getIntField("defence");
        equipInfo->equipSpeed = q.getIntField("speed");
        equipInfo->equipDescription = q.getStringField("description");
        
        tempInfo.equipInfo = equipInfo;

        m_vecUserEquipInfos.push_back(tempInfo);
        
        q.nextRow();
    }
    
    return true;
}

int PlayerInfoDataManager::getUserEquipInfoCount(){
    return m_vecUserEquipInfos.size();
}

stActorUserEquipInfo* PlayerInfoDataManager::getUserEquipInfo(int index){
    if(index < 0 || index > m_vecUserEquipInfos.size())
        return NULL;
    return &m_vecUserEquipInfos[index];
}

stActorUserEquipInfo* PlayerInfoDataManager::getUserEquipInfoForId(int equipid){
    for (int i = 0; i < m_vecUserEquipInfos.size() ; i++) {
        if(equipid == m_vecUserEquipInfos[i].userEquipId)
            return &m_vecUserEquipInfos[i];
    }
    return NULL;
}

stActorUserInfo* PlayerInfoDataManager::getCurUserInfo(){
    return m_curUserInfo;
}

void PlayerInfoDataManager::setCurUserInfo(stActorUserInfo* info){
    if (m_curUserInfo == NULL) {
        m_curUserInfo = new stActorUserInfo();
    }
    if (info != NULL) {
        m_curUserInfo->userNickName = info->userNickName;
        m_curUserInfo->userImageId = info->userImageId;
        m_curUserInfo->userLevel = info->userLevel;
        m_curUserInfo->userExp = info->userExp;
        m_curUserInfo->userHp = info->userHp;
        m_curUserInfo->userCareerId = info->userCareerId;
        m_curUserInfo->userChapterId = info->userChapterId;
        m_curUserInfo->userPageId = info->userPageId;
        m_curUserInfo->userAttack = info->userAttack;
        m_curUserInfo->userDefence = info->userDefence;
        m_curUserInfo->userSpeed = info->userSpeed;
        m_curUserInfo->userMaxHp = info->userMaxHp;
    }
    //m_curUserInfo = info;
}

void PlayerInfoDataManager::setCurUserInfoAttack(float attack){
    if (m_curUserInfo != NULL) {
        m_curUserInfo->userAttack = attack;
    }
}
void PlayerInfoDataManager::setCurUserInfoDefence(float defence){
    if (m_curUserInfo != NULL) {
        m_curUserInfo->userDefence = defence;
    }
}
void PlayerInfoDataManager::setCurUserInfoSpeed(float speed){
    if (m_curUserInfo != NULL) {
        m_curUserInfo->userSpeed = speed;
    }
}

