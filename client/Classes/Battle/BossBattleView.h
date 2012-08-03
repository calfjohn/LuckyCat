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

class BossBattleView : public cocos2d::CCLayer
{
public:
    LAYER_CREATE_FUNC(BossBattleView);
    
    virtual void onEnter();
    
    void initLayer(const stPage *p_Page, CCObject *target, cocos2d::SEL_CallFuncND pfnSelector);
    
    void fightAction();
    
    cocos2d::CCFiniteTimeAction * createSequece(unsigned int action_id);
    
    void playAction();
    
    void playOneActionEnd();
    
    //是否在战斗中
    static bool getIsInBattle();
    
    static void setIsInBattle(bool _b_state);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher(void);
    
private:
    cocos2d::CCSprite *pMonsterSprite;
    
    std::vector<unsigned int> mActionList;
    
    int mIntBossHPMax,mIntPlayerHPMax;
    
    cocos2d::CCObject*       m_target;         //callback listener
    
    cocos2d::SEL_CallFuncND  m_pfnSelector;    //callback selector
    
    GRole * p_Boss;
    std::vector<GRole *> mPlayerList;
    
    cocos2d::CCPoint pBeginPoint;
    
    bool m_bIsWaitingForAction;
    
    const stPage *p_pPage;
};


#endif
