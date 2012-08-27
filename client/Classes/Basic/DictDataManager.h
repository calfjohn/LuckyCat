//
//  DictDataManager.h
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#if !defined _DictDataManager_H__
#define _DictDataManager_H__

#include "Basic.h"
#include "CppSQLite3.h"

class DictDataManager
{
public:
	static DictDataManager* shareDictDataManager(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new DictDataManager();
			m_pInstance->init();
		}
		return m_pInstance;

	}
    
    const stMonster* getMonsterImageId(int monsterId);
    
    const stImage *getImage(int imageId);
protected:
	bool init(void);
    
    bool initMonster();
    
    bool initImage();
    
	DictDataManager(void);
	virtual ~DictDataManager(void);

	static DictDataManager *m_pInstance;

	class XLRelease
	{
	public:
		~XLRelease()
		{
			if(DictDataManager::m_pInstance)
			{
				delete DictDataManager::m_pInstance;
				DictDataManager::m_pInstance = NULL;
			}
		}
	};
	static XLRelease Garbo;
    
    map<int, stMonster> m_mapMonster;
    map<int, stImage> m_mapImage; 

    CppSQLite3DB m_db;
};

#endif