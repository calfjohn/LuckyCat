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
#include "BattleDefine.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class BossBattleView : public CCLayer
{
public:
    LAYER_CREATE_FUNC(BossBattleView);
    
    virtual void onEnter();
    
    void initLayer(int monsterId, CCObject *target, SEL_CallFuncND pfnSelector);
    
    void fightAction();
    
    CCFiniteTimeAction * createSequece(unsigned int action_id);
    
    void playAction();
    
    //是否在战斗中
    static bool getIsInBattle();
    
    static void setIsInBattle(bool _b_state);
    
private:
    CCSprite *pMonsterSprite;
    
    std::vector<unsigned int> mActionList;
    
    int mIntBossHPMax,mIntPlayerHPMax;
    
    CCObject*       m_target;         //callback listener
    
    SEL_CallFuncND  m_pfnSelector;    //callback selector
    
    std::vector<GRole *> mBossList;
    std::vector<GRole *> mPlayerList;
    
};


#endif
