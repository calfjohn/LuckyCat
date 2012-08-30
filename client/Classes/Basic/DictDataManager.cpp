//
//  DictDataManager.cpp
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "DictDataManager.h"
#include "json/json.h"
#include "cocos2d.h"

USING_NS_CC;

DictDataManager *DictDataManager::m_pInstance = NULL;
DictDataManager::XLRelease DictDataManager::Garbo;

DictDataManager::DictDataManager( void )
{
}

DictDataManager::~DictDataManager( void )
{

}

bool DictDataManager::init( void )
{
   string strFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/LuckyCat.sqlite");

    m_db.open(strFullPath.c_str());
	if (!m_db.isOpen())
	{
		return false;
	}
     
    initImage();
    initMonster();
    initEquipment();
    
    m_db.close();

    return true;
}

bool DictDataManager::initMonster()
{
    CppSQLite3Query q = m_db.execQuery("select * from dict_monster;");
    while(!q.eof())
    {
        stMonster tempMonster;
        
        tempMonster.id = q.getIntField("id");
        tempMonster.name = q.getStringField("name");
        tempMonster.imageId = q.getIntField("image_id");
        
        m_mapMonster[tempMonster.id] = tempMonster;
        
        q.nextRow();
    }
    
    return true;
}

bool DictDataManager::initImage()
{
    CppSQLite3Query q = m_db.execQuery("select * from dict_image;");
    while(!q.eof())
    {
        stImage tempImage;
        
        tempImage.id = q.getIntField("id");
        tempImage.type = q.getIntField("type");
        tempImage.name = q.getStringField("name");
        tempImage.filePath = q.getStringField("file_path");
        tempImage.plistPath = q.getStringField("plist_path");
        m_mapImage[tempImage.id] = tempImage;
        
        q.nextRow();
    }    
    
    return true;
}

bool DictDataManager::initEquipment()
{
    CppSQLite3Query q = m_db.execQuery("select * from dict_equipment;");
    while(!q.eof())
    {
        stActorEquipInfo equipInfo;
        
        equipInfo.equipId = q.getIntField("id");
        equipInfo.equipName = q.getStringField("name");
        equipInfo.equipImageId = q.getIntField("image_id");
        equipInfo.equipType = q.getIntField("class");
        equipInfo.equipLife = q.getIntField("life");
        equipInfo.equipLevelLimit = q.getIntField("level_limit");
        equipInfo.equipAttack = q.getIntField("attack");
        equipInfo.equipDefence = q.getIntField("defence");
        equipInfo.equipSpeed = q.getIntField("speed");
        equipInfo.equipDescription = q.getStringField("description");
        
        m_mapEuipment[equipInfo.equipId] = equipInfo;
        q.nextRow();
    }
}

const stMonster *DictDataManager::getMonsterImageId(int monsterId)
{   
    const stMonster *pRetValue = NULL;
    map<int, stMonster>::iterator iterTemp;
    iterTemp = m_mapMonster.find(monsterId);
    if (iterTemp != m_mapMonster.end()) 
    {
        pRetValue = &(*iterTemp).second;
    }
    
    return pRetValue;
}

const stImage *DictDataManager::getImage(int imageId)
{
    const stImage *pRetValue = NULL;

    map<int, stImage>::iterator iterTemp;
    iterTemp = m_mapImage.find(imageId);
    if (iterTemp != m_mapImage.end()) 
    {
        pRetValue = &(*iterTemp).second;
    }
    
    return pRetValue;
}

const stActorEquipInfo *DictDataManager::getEquipment(int equipId)
{
    const stActorEquipInfo *pRetValue = NULL;
    
    map<int, stActorEquipInfo>::iterator iterTemp;
    iterTemp = m_mapEuipment.find(equipId);
    if (iterTemp != m_mapEuipment.end()) 
    {
        pRetValue = &(*iterTemp).second;
    }
    
    return pRetValue;
}
