//
//  LevelDataManager.cpp
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "LevelDataManager.h"
#include "json/json.h"
#include "CppSQLite3.h"
#include "cocos2d.h"

USING_NS_CC;

LevelDataManager *LevelDataManager::m_pInstance = NULL;
LevelDataManager::XLRelease LevelDataManager::Garbo;

LevelDataManager::LevelDataManager( void )
{
}

LevelDataManager::~LevelDataManager( void )
{

}

void LevelDataManager::init( void )
{
    string strFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/level");
    unsigned long nSize = 0;
    strFullPath = "/Users/cocos2d/Library/Application Support/iPhone Simulator/5.1/Applications/1A03B516-08FF-43DE-9AD4-586435D16DBD/HelloWorld.app/config/level";
    const char* pBuffer = (const char *)CCFileUtils::sharedFileUtils()->getFileData(strFullPath.c_str(), "rb", &nSize);
    
	Json::Reader reader;
	Json::Value json_root;
	if (!reader.parse(pBuffer, json_root))
		return;
    
    json_root = json_root["bible"];
    m_stBible.name = json_root["name"].asString();
    
    if(!json_root["listChpater"].isArray())
    {
        return;
    }
    
    Json::Value jsonTempPage;
    Json::Value jsonTempChapter;
    for (int i = 0; i < json_root["listChpater"].size(); i++) 
    {
        stChapter tempChapter;
        jsonTempChapter = json_root["listChpater"][i];
        
        tempChapter.id = jsonTempChapter["id"].asInt();
        tempChapter.name = jsonTempChapter["name"].asString();
        for (int j = 0; j < jsonTempChapter["listPage"].size(); j++) 
        {
            stPage  tempPage;
            jsonTempPage = jsonTempChapter["listPage"][j];
            
            tempPage.id = jsonTempPage["id"].asInt();
            tempPage.name = jsonTempPage["name"].asString();
            tempPage.content = jsonTempPage["content"].asString();
            tempPage.monsterId = jsonTempPage["monsterId"].asInt();
            tempPage.state = jsonTempPage["state"].asInt();
            
            tempChapter.listPage.push_back(tempPage);
        }
        
        m_stBible.listChapter.push_back(tempChapter);
    }
    
}

stPage *LevelDataManager::getNewPage(int chapterId)
{
    stPage *pPage = NULL;
    vector<stChapter>::iterator iterTemp;
    for (iterTemp = m_stBible.listChapter.begin();
         iterTemp != m_stBible.listChapter.end();
         iterTemp++) 
    {
//        CCLOG("%s", (*iterTemp).name.c_str());
        if ((*iterTemp).id == chapterId) 
        {
            vector<stPage>::iterator iterPage;
            for (iterPage = (*iterTemp).listPage.begin();
                 iterPage != (*iterTemp).listPage.end();
                 iterPage++) 
            {
//                CCLOG("id:%d name:%s content:%s monsterId:%d state:%d", (*iterPage).id, (*iterPage).name.c_str(), (*iterPage).content.c_str(), (*iterPage).monsterId, (*iterPage).state);
                pPage = &(*iterPage);
                if (pPage->state != 1) 
                {
                    break;
                }
            }
            break;
        }
    }
    
    return pPage;
}

bool LevelDataManager::isChapterEnd(int chapterId)
{
    vector<stChapter>::iterator iterTemp;
    for (iterTemp = m_stBible.listChapter.begin();
         iterTemp != m_stBible.listChapter.end();
         iterTemp++) 
    {
        if ((*iterTemp).id == chapterId && (*iterTemp).listPage.size() > 0) 
        {
            return (*iterTemp).listPage.back().state == 1;
        }
    }
    
    return false;
}

stChapter *LevelDataManager::getChapter(int chapterId)
{
    vector<stChapter>::iterator iterTemp;
    for (iterTemp = m_stBible.listChapter.begin();
         iterTemp != m_stBible.listChapter.end();
         iterTemp++) 
    {
        if ((*iterTemp).id == chapterId) 
        {
            return &(*iterTemp);
        }
    }
}

