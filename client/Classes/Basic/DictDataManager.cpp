//
//  DictDataManager.cpp
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "DictDataManager.h"
#include "json/json.h"
#include "CppSQLite3.h"
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

void DictDataManager::init( void )
{
   string strFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/LuckyCat.sqlite");

    CppSQLite3DB db;
    db.open(strFullPath.c_str());
	if (!db.isOpen())
	{
		return;
	}

    CppSQLite3Query q = db.execQuery("select * from monster;");
    while(!q.eof())
    {
        stMonster tempMonster;
        
        tempMonster.id = q.getIntField("id");
        tempMonster.name = q.getStringField("name");
        tempMonster.imageId = q.getIntField("image_id");
        
        m_mapMonster[tempMonster.id] = tempMonster;
        
        q.nextRow();
    }
    
    q = db.execQuery("select * from image;");
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
    db.close();
/*
    string strFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/monster");
    unsigned long nSize = 0;
    const char* pBuffer = (const char *)CCFileUtils::sharedFileUtils()->getFileData(strFullPath.c_str(), "rb", &nSize);
    
	Json::Reader reader;
	Json::Value json_root;
	if (!reader.parse(pBuffer, json_root))
		return;
    
    json_root = json_root["monster_dict"];
    if(!json_root.isArray())
    {
        return;
    }
    
    Json::Value jsonTempMonster;
    for (int i = 0; i < json_root.size(); i++) 
    {
        stMonster tempMonster;
        jsonTempMonster = json_root[i];
        
        tempMonster.id = jsonTempMonster["id"].asInt();
        tempMonster.name = jsonTempMonster["name"].asString();
        tempMonster.image_id = jsonTempMonster["image_id"].asInt();
        CCLOG("id:%d name:%s image_id:%d", tempMonster.id, tempMonster.name.c_str(), tempMonster.image_id);
        
        m_mapMonster[tempMonster.id] = tempMonster;
    }
*/
}

const stMonster *DictDataManager::getMonsterImageId(int monsterId)
{   
    map<int, stMonster>::iterator iterTemp;
    iterTemp = m_mapMonster.find(monsterId);
    if (iterTemp != m_mapMonster.end()) 
    {
        return &(*iterTemp).second;
    }
    
    return NULL;
}

const stImage *DictDataManager::getImage(int imageId)
{
    map<int, stImage>::iterator iterTemp;
    iterTemp = m_mapImage.find(imageId);
    if (iterTemp != m_mapImage.end()) 
    {
        return &(*iterTemp).second;
    }
    
    return NULL;
}
