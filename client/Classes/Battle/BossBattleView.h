//
//  BossBattleView.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_BossBattleView_h
#define HelloWorld_BossBattleView_h

#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class RolePro
{
public:
    unsigned int curHP;
    unsigned int MaxHp;
    float curPercentHP;
    float getCurPercentHP()
    {
        curPercentHP = curHP * ( 1.0 / MaxHp );
        
        return curPercentHP;
    }
};

class BossBattleView : public CCLayer
{
public:
    LAYER_CREATE_FUNC(BossBattleView);
    
    virtual void onEnter();
    
    void initLayer();
    
    void fightAction();
    
    CCFiniteTimeAction * createSequece(unsigned int action_id);
    
    void playAction();
    
private:
    CCSprite *pMonsterSprite;
    
    std::vector<unsigned int> mActionList;
    
    int mIntBossHPMax,mIntPlayerHPMax;
    
};


#endif
