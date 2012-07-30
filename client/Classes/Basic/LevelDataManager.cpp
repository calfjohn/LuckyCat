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
    string strFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/LuckyCat.sqlite");
    CppSQLite3DB db;
    db.open(strFullPath.c_str());
	if (!db.isOpen())
	{
		return;
	}
    
    stBible tempBible;
    CppSQLite3Query q1 = db.execQuery("select * from bible;");
	while(!q1.eof())
	{
        tempBible.id = q1.getIntField("id");
        tempBible.name = q1.getStringField("name");
        tempBible.bgId = q1.getIntField("bg_id");
        tempBible.chapterBgId = q1.getIntField("chapter_bg_id");
        {
            char tempSql[256];
            sprintf(tempSql, "select * from chapter where bible_id = %d order by id;", tempBible.id);
            CppSQLite3Query q2 = db.execQuery(tempSql);
            while(!q2.eof())
            {
                stChapter tempChapter;
                
                tempChapter.id = q2.getIntField("id");
                tempChapter.name = q2.getStringField("name");
                tempChapter.imageId = q2.getIntField("image_id");
                tempChapter.position.x = q2.getFloatField("position_x");
                tempChapter.position.y = q2.getFloatField("position_y");
                {
                    sprintf(tempSql, "select * from page where chapter_id = %d order by id;", tempChapter.id);
                    CppSQLite3Query q3 = db.execQuery(tempSql);
                    while(!q3.eof())
                    {
                        stPage  tempPage;
                    
                        tempPage.id =  q3.getIntField("id");
                        tempPage.name = q3.getStringField("name");
                        tempPage.content = q3.getStringField("content");
                        tempPage.imageId =  q3.getIntField("image_id");
                        tempPage.taskId =  q3.getIntField("task_id");
                        tempPage.state = q3.getIntField("state");
                        tempPage.position.x = q3.getFloatField("position_x");
                        tempPage.position.y = q3.getFloatField("position_y");
                        tempPage.end = false;
                        tempChapter.listPage.push_back(tempPage);
                        q3.nextRow();
                        if (q3.eof()) 
                        {
                            tempChapter.listPage.back().end = true;
                        }
                    }
                }
                tempBible.listChapter.push_back(tempChapter);
                q2.nextRow();
            }
        }

        m_mapBible[tempBible.id] = tempBible;
        q1.nextRow();
    }

    db.close();

/*    
    string strFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/level");
    unsigned long nSize = 0;
    const char* pBuffer = (const char *)CCFileUtils::sharedFileUtils()->getFileData(strFullPath.c_str(), "rb", &nSize);
    
    Json::Reader reader;
	Json::Value json_root;
	if (!reader.parse(pBuffer, json_root))
		return;
    
    json_root = json_root["bible"];
    m_stBible.name = json_root["name"].asString();
    CCLOG("%s", m_stBible.name.c_str());

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
        tempChapter.position.x = jsonTempChapter["position"]["x"].asInt();
        tempChapter.position.y = jsonTempChapter["position"]["y"].asInt();
        CCLOG("id:%d name:%s", tempChapter.id, tempChapter.name.c_str());

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
            
            CCLOG("id:%d name:%s content:%s monsterId:%d state:%d", tempPage.id, tempPage.name.c_str(), tempPage.content.c_str(), tempPage.monsterId, tempPage.state);            
        }
        
        m_stBible.listChapter.push_back(tempChapter);
    }
*/    
}

const stBible *LevelDataManager::getBible()
{
    return &m_mapBible[1];
}

stPage *LevelDataManager::getNewPage(int chapterId)
{
    stPage *pPage = NULL;
    vector<stChapter>::iterator iterTemp;
    for (iterTemp = m_mapBible[1].listChapter.begin();
        iterTemp != m_mapBible[1].listChapter.end();
         iterTemp++) 
    {
        if ((*iterTemp).id == chapterId) 
        {
            vector<stPage>::iterator iterPage;
            for (iterPage = (*iterTemp).listPage.begin();
                 iterPage != (*iterTemp).listPage.end();
                 iterPage++) 
            {
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
    for (iterTemp = m_mapBible[1].listChapter.begin();
         iterTemp != m_mapBible[1].listChapter.end();
         iterTemp++) 
    {
        if ((*iterTemp).id == chapterId && (*iterTemp).listPage.size() > 0) 
        {
            return (*iterTemp).listPage.back().state == 1;
        }
    }
    
    return false;
}

bool LevelDataManager::isLastPageOfChapter(int chapterId, int pageId)
{
    vector<stChapter>::iterator iterTemp;
    for (iterTemp = m_mapBible[1].listChapter.begin();
         iterTemp != m_mapBible[1].listChapter.end();
         iterTemp++) 
    {
        if ((*iterTemp).id == chapterId) 
        {
            return (*iterTemp).listPage.back().id == pageId;
        }
    }
    
    return false;
}

stChapter *LevelDataManager::getChapter(int chapterId)
{
    vector<stChapter>::iterator iterTemp;
    for (iterTemp = m_mapBible[1].listChapter.begin();
         iterTemp != m_mapBible[1].listChapter.end();
         iterTemp++) 
    {
        if ((*iterTemp).id == chapterId) 
        {
            return &(*iterTemp);
        }
    }
    return NULL;
}

stPage *LevelDataManager::getPage(int chapterId, int pageId)
{
    stPage *pPage = NULL;
    vector<stChapter>::iterator iterTemp;
    for (iterTemp = m_mapBible[1].listChapter.begin();
         iterTemp != m_mapBible[1].listChapter.end();
         iterTemp++) 
    {
        if ((*iterTemp).id == chapterId) 
        {
            vector<stPage>::iterator iterPage;
            for (iterPage = (*iterTemp).listPage.begin();
                 iterPage != (*iterTemp).listPage.end();
                 iterPage++) 
            {
                pPage = &(*iterPage);
                if (pPage->id == pageId) 
                {
                    break;
                }
            }
            break;
        }
    }
    
    return pPage;
}

void LevelDataManager::reload()
{
    m_mapBible[1].name = "";
    m_mapBible[1].listChapter.clear();
    init();
}

