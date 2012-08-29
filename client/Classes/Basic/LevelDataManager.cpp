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
#include "BasicFunction.h"

USING_NS_CC;

LevelDataManager *LevelDataManager::m_pInstance = NULL;
LevelDataManager::XLRelease LevelDataManager::Garbo;

LevelDataManager::LevelDataManager( void )
{
}

LevelDataManager::~LevelDataManager( void )
{
}

bool LevelDataManager::init( void )
{
    string strFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/LuckyCat.sqlite");
    CppSQLite3DB db;
    db.open(strFullPath.c_str());
	if (!db.isOpen())
	{
		return false;
	}
    
    stBible tempBible;
    CppSQLite3Query q1 = db.execQuery("select * from dict_bible;");
	while(!q1.eof())
	{
        tempBible.id = q1.getIntField("id");
        tempBible.name = q1.getStringField("name");
        tempBible.bgId = q1.getIntField("bg_id");
        tempBible.chapterBgId = q1.getIntField("chapter_bg_id");
        {
            char tempSql[256];
            sprintf(tempSql, "select * from dict_chapter where bible_id = %d order by id;", tempBible.id);
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
                    sprintf(tempSql, "select * from dict_page where chapter_id = %d order by id;", tempChapter.id);
                    CppSQLite3Query q3 = db.execQuery(tempSql);
                    while(!q3.eof())
                    {
                        stPage  tempPage;
                    
                        tempPage.id =  q3.getIntField("id");
                        tempPage.name = q3.getStringField("name");
                        tempPage.content = q3.getStringField("content");
                        tempPage.imageId =  q3.getIntField("image_id");
                        tempPage.eventId =  q3.getIntField("event_id");
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
  
    CppSQLite3Query result = db.execQuery("select * from dict_actor_level_upgrade;");
    
    std::vector<stActorLevelUpgrade *> tLevelList;
	while(!result.eof())
	{
        stActorLevelUpgrade *tmpLevel = new stActorLevelUpgrade();
        
        tmpLevel->level = result.getIntField("level");
        tmpLevel->title = result.getStringField("title");
        tmpLevel->content = result.getStringField("content");
        
        std::string strBonus = result.getStringField("bonus");
        std::vector<int> tmpBonusList = separateStringToNumberVector(strBonus, ",");
        
        if (tmpBonusList.size() > 0)
        {
            CCAssert( tmpBonusList[0]*2 == tmpBonusList.size()-1, "Something error in sql field\n");
            for (int i = 1; tmpBonusList[0] != 0 && i+1 < tmpBonusList.size(); i+=2) {
                stGood _good;
                _good.id = tmpBonusList[i];
                _good.count = tmpBonusList[i+1];
                tmpLevel->bonus.push_back(_good);
            }
        }

        
        tmpLevel->print();
        tLevelList.push_back(tmpLevel);
        
        result.nextRow();
    }
    this->setMapActorLevelUpgrade(tLevelList);
    
    db.close();
    
    return true;
}

const stBible *LevelDataManager::getBible()
{
    return &m_mapBible[1];
}

const stPage *LevelDataManager::getNewPage(int chapterId)
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
    bool bRetValue = false;
    vector<stChapter>::iterator iterTemp;
    for (iterTemp = m_mapBible[1].listChapter.begin();
         iterTemp != m_mapBible[1].listChapter.end();
         iterTemp++) 
    {
        if ((*iterTemp).id == chapterId && (*iterTemp).listPage.size() > 0) 
        {
            bRetValue = (*iterTemp).listPage.back().state == 1;
        }
    }
    
    return bRetValue;
}

bool LevelDataManager::isLastPageOfChapter(int chapterId, int pageId)
{
    bool bRetValue = false;

    vector<stChapter>::iterator iterTemp;
    for (iterTemp = m_mapBible[1].listChapter.begin();
         iterTemp != m_mapBible[1].listChapter.end();
         iterTemp++) 
    {
        if ((*iterTemp).id == chapterId) 
        {
            bRetValue =  (*iterTemp).listPage.back().id == pageId;
        }
    }
    
    return bRetValue;
}

const stChapter *LevelDataManager::getChapter(int chapterId)
{
    stChapter *pRetValue = NULL;
    vector<stChapter>::iterator iterTemp;
    for (iterTemp = m_mapBible[1].listChapter.begin();
         iterTemp != m_mapBible[1].listChapter.end();
         iterTemp++) 
    {
        if ((*iterTemp).id == chapterId) 
        {
            pRetValue =  &(*iterTemp);
        }
    }
    
    return pRetValue;
}

const stPage *LevelDataManager::getPage(int chapterId, int pageId)
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

void LevelDataManager::setMapActorLevelUpgrade( vector<stActorLevelUpgrade *> tmpList)
{
    this->deleteMapActorLevelUpgrade();
    
    for (vector<stActorLevelUpgrade *>::iterator _iter = tmpList.begin(); _iter != tmpList.end(); _iter++) {
        stActorLevelUpgrade *tmp = *_iter;
        m_mapActorLevelUpgrade.insert(make_pair(tmp->level, tmp));
    }
}

void LevelDataManager::deleteMapActorLevelUpgrade()
{
    for (map<int, stActorLevelUpgrade *>::iterator _iter = m_mapActorLevelUpgrade.begin(); _iter != m_mapActorLevelUpgrade.end(); _iter++) {
        stActorLevelUpgrade *tmp = _iter->second;
        CC_SAFE_DELETE(tmp);
    }
    m_mapActorLevelUpgrade.clear();
}

const stActorLevelUpgrade * LevelDataManager::getMapActorLevelUpgrade(int _level)
{
    stActorLevelUpgrade *pRetValue = NULL;
    map<int, stActorLevelUpgrade *>::iterator _iter = m_mapActorLevelUpgrade.find(_level);
    if ( _iter == m_mapActorLevelUpgrade.end() )
    {
        pRetValue = NULL;
    }
    else 
    {
        pRetValue = _iter->second;
    }
    
    return pRetValue;
}

bool LevelDataManager::changePageState(int chapterId, int pageId)
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
                if ((*iterPage).id == pageId) 
                {
                    pPage = &(*iterPage);
                    pPage->state = 1;
                    break;
                }
            }
            break;
        }
    }
    
    return pPage != NULL;
}