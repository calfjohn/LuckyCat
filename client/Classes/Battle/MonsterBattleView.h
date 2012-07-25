//
//  MonsterBattleView.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_MonsterBattleView_h
#define HelloWorld_MonsterBattleView_h

#include "cocos2d.h"
#include "Basic.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class MonsterBattleView : public CCLayer 
{
public:
    //
    LAYER_CREATE_FUNC(MonsterBattleView);
    
    virtual void onEnter();
    
    void initLayer(stPage *p_page, CCObject *target, SEL_CallFuncND pfnSelector);
    
    void fightAction();
    
    CCFiniteTimeAction * createSequece(unsigned int action_id);
    
    void playAction();
    
    //是否在战斗中
    static bool getIsInBattle();
    
    static void setIsInBattle(bool _b_state);
    
private:
    CCSprite *pMonsterSprite;
    
    std::vector<unsigned int> mActionList;
    
    CCObject*       m_target;         //callback listener
    
    SEL_CallFuncND  m_pfnSelector;    //callback selector
    
    stPage *p_pPage;
    
};

#endif
