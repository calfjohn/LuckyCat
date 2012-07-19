//
//  MTabLayer.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_MTabLayer_h
#define HelloWorld_MTabLayer_h

#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "CCPTextFieldTTF.h"

class MTabLayer 
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::CCTextFieldDelegate
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MTabLayer, create);
    
    MTabLayer();
    virtual ~MTabLayer();
    
    void initLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onCCControlButtonClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    
private:
    
    cocos2d::extension::CCControlButton *p_CurButton;
    cocos2d::CCLayer *p_CurLayer;
    int m_intCurTab;
    
    cocos2d::CCPTextFieldTTF *m_LongText;
    
    void initLongCCTextFieldTTF(cocos2d::CCLayer *p_parent);
};

#endif
