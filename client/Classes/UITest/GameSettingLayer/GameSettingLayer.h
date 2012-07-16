//
//  GameSettingLayer.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_GameSettingLayer_h
#define HelloWorld_GameSettingLayer_h

#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"

class GameSettingLayer 
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::CCTextFieldDelegate
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameSettingLayer, create);
    
    GameSettingLayer();
    virtual ~GameSettingLayer();
    
    void initLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onCCControlButtonClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    void valueChanged(cocos2d::CCObject *sender, cocos2d::extension::CCControlEvent controlEvent);
    
    void SwitchControlValueChanged(cocos2d::CCObject *sender, cocos2d::extension::CCControlEvent controlEvent);
    
private:
    
};

#endif
