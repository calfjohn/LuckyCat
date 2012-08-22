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
using namespace std;

class PlayerInfoDataManager{
public:
    PlayerInfoDataManager();
    virtual ~PlayerInfoDataManager();
    
    static PlayerInfoDataManager* sharedPlayerInfoDataManager(){
        if (m_pInstance == NULL) {
            m_pInstance = new PlayerInfoDataManager();
            
        }
        return m_pInstance;
    }
    
protected:
    static PlayerInfoDataManager* m_pInstance;
};



#endif /* defined(__LuckyCat__PlayerInfoDataManager__) */
