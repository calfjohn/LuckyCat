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
/*   string strFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/LuckyCat.db");

    CppSQLite3DB db;
    db.open(strFullPath.c_str());
	if (!db.isOpen())
	{
		return;
	}

    CppSQLite3Query q3 = db.execQuery("select * from monster;");
    while(!q3.eof())
    {
        q3.nextRow();
    }
    
    db.close();
*/
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