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
#include "touch_dispatcher/CCTouch.h"
#include "Basic.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class BossBattleView : public CCLayer
{
public:
    LAYER_CREATE_FUNC(BossBattleView);
    
    virtual void onEnter();
    
    void initLayer(const stPage *p_Page, CCObject *target, SEL_CallFuncND pfnSelector);
    
    void fightAction();
    
    CCFiniteTimeAction * createSequece(unsigned int action_id);
    
    void playAction();
    
    void playOneActionEnd();
    
    //是否在战斗中
    static bool getIsInBattle();
    
    static void setIsInBattle(bool _b_state);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher(void);
    
private:
    CCSprite *pMonsterSprite;
    
    std::vector<unsigned int> mActionList;
    
    int mIntBossHPMax,mIntPlayerHPMax;
    
    CCObject*       m_target;         //callback listener
    
    SEL_CallFuncND  m_pfnSelector;    //callback selector
    
    GRole * p_Boss;
    std::vector<GRole *> mPlayerList;
    
    CCPoint pBeginPoint;
    
    bool m_bIsWaitingForAction;
    
    const stPage *p_pPage;
};


#endif
