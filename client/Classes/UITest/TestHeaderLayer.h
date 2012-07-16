//
//  TestHeaderLayer.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_TestHeaderLayer_h
#define HelloWorld_TestHeaderLayer_h

#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"

class TestHeaderLayer
: public cocos2d::CCLayer
, public cocos2d::extension::CCBSelectorResolver
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(TestHeaderLayer, create);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    
    void pressBTNLogin(cocos2d::CCObject * pSender);
    
    void pressBTNRegister(cocos2d::CCObject * pSender);
};

#endif
