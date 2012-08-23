//
//  OpenBoxView.h
//  LuckyCat
//
//  Created by XiaoZhong Zhu on 12-8-10.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef LuckyCat_OpenBoxView_h
#define LuckyCat_OpenBoxView_h

#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "extensions/CCBReader/CCLayerLoader.h"

#include "EventBasic.h"

class OpenBoxView 
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    OpenBoxView();
    ~OpenBoxView();
    
    static OpenBoxView *create(cocos2d::CCObject * pOwner);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(OpenBoxView, create);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onMenuItemClicked(cocos2d::CCObject *pTarget);
    
    void onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    void setSelector(cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector);
    
    void setEvent(LEventData *t);
    
    void netCallBack(CCNode* pNode, void* data);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher(void);
private:
    LEventData *p_CurEvent;
    
    bool m_bIsOpen;
    
    cocos2d::CCPoint pBeginPoint;
    
    cocos2d::CCObject*       m_target;         //callback listener
    
    cocos2d::SEL_CallFuncND  m_pfnSelector;    //callback selector
};

class CCBReader;

class OpenBoxViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(OpenBoxViewLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(OpenBoxView);
};

#endif
