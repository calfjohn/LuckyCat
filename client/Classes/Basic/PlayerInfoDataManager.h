//
//  PlayerInfoDataManager.h
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-20.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef __LuckyCat__PlayerInfoDataManager__
#define __LuckyCat__PlayerInfoDataManager__

#include <iostream>
#include "Basic.h"

using namespace std;

class PlayerInfoDataManager{
public:
    
    static PlayerInfoDataManager* sharedPlayerInfoDataManager(){
        if (m_pInstance == NULL) {
            m_pInstance = new PlayerInfoDataManager();
            m_pInstance->init();
            
        }
        return m_pInstance;
    }
    
    int getUserEquipInfoCount();
    
    stActorUserEquipInfo* getUserEquipInfo(int index);
    
protected:
    PlayerInfoDataManager();
    virtual ~PlayerInfoDataManager();
    
    bool init();
    static PlayerInfoDataManager* m_pInstance;
    
    class XLRelease
	{
	public:
		~XLRelease()
		{
			if(PlayerInfoDataManager::m_pInstance)
			{
				delete PlayerInfoDataManager::m_pInstance;
				PlayerInfoDataManager::m_pInstance = NULL;
			}
		}
	};
	static XLRelease Garbo;
    
    vector<stActorUserEquipInfo> m_vecUserEquipInfos;
};



#endif /* defined(__LuckyCat__PlayerInfoDataManager__) */
