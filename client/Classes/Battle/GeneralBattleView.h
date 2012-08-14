//
//  GeneralBattleView.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-8-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_GeneralBattleView_h
#define HelloWorld_GeneralBattleView_h

#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "extensions/CCBReader/CCLayerLoader.h"

#include "TaskBasic.h"

class GeneralBattleView 
: public cocos2d::CCLayer
{
public:
    GeneralBattleView();
    ~GeneralBattleView();
    
    static GeneralBattleView *create(cocos2d::CCObject * pOwner);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GeneralBattleView, create);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onMenuItemClicked(cocos2d::CCObject *pTarget);
    
    void onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher(void);
    
    void setData(stTask *tTask, cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector);
    
    void removeAndCleanSelf(float dt);
    
    void menuBackCallback(CCObject* pSender);
private:
    cocos2d::CCPoint         pBeginPoint;
    
    stTask *p_CurTask;
    
    cocos2d::CCObject*       m_target;         //callback listener
    
    cocos2d::SEL_CallFuncND  m_pfnSelector;    //callback selector
    
    void showBattleResultView();
};

class CCBReader;

class GeneralBattleViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GeneralBattleViewLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GeneralBattleView);
};

#endif