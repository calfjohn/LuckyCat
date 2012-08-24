//
//  BattleResultView.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_BattleResultView_h
#define HelloWorld_BattleResultView_h

#include "TouchLayer.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCLayerLoader.h"
#include "Basic.h"
#include "EventBasic.h"
#include "BattleDefine.h"
#include "LuckySprite.h"



class BattleResultView : public TouchLayer 
{
public:
    
    static BattleResultView *create(cocos2d::CCObject * pOwner);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BattleResultView, create);
    
    virtual void notificationTouchEvent(LTouchEvent tLTouchEvent);
    
    void initView(LEventData *tEvent);
    
    void initView(std::vector<stGood> tGoodsList);
    
    void setSelector(cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector);
    
    void netCallBack(CCNode* pNode, void* data);
    
private:
    LEventData *p_CurEvent;
    
    cocos2d::CCObject*       m_target;         //callback listener
    
    cocos2d::SEL_CallFuncND  m_pfnSelector;    //callback selector
    
    cocos2d::CCPoint        pBeginPoint;
};

class CCBReader;

class BattleResultViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BattleResultViewLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(BattleResultView);
};

#endif
