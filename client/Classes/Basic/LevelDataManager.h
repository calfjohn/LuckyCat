//
//  LevelDataManager.h
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#if !defined _LevelDataManager_H__
#define _LevelDataManager_H__

#include "Basic.h"

class LevelDataManager
{
public:
	static LevelDataManager* shareLevelDataManager(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new LevelDataManager();
			m_pInstance->init();
		}
		return m_pInstance;

	}
    
    void reload();
    
    bool changePageState(int chapterId, int pageId);

    const stPage *getPage(int chapterId, int pageId);

    const stPage *getNewPage(int chapterId);
    
    const stChapter *getChapter(int chapterId);

    bool isChapterEnd(int chapterId);
    
    bool isLastPageOfChapter(int chapterId, int pageId);

    map<int, stBible>m_mapBible;
    
    const stBible *getBible();
    
    template <class T> 
	static std::string ConvertToString(T value) {
		std::stringstream ss;
		ss << value;
		return ss.str();
        
	}
    
    map<int, stActorLevelUpgrade *> m_mapActorLevelUpgrade;
    void setMapActorLevelUpgrade( vector<stActorLevelUpgrade *> tmpList);
    void deleteMapActorLevelUpgrade();
    const stActorLevelUpgrade * getMapActorLevelUpgrade(int _level);
protected:
	bool init(void);
	LevelDataManager(void);
	virtual ~LevelDataManager(void);

	static LevelDataManager *m_pInstance;

	class XLRelease
	{
	public:
		~XLRelease()
		{
			if(LevelDataManager::m_pInstance)
			{
				delete LevelDataManager::m_pInstance;
				LevelDataManager::m_pInstance = NULL;
			}
		}
	};
	static XLRelease Garbo;
};

#endif