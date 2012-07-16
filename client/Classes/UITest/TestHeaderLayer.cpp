//
//  TestHeaderLayer.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "TestHeaderLayer.h"

#include "extensions/CCBReader/CCBReader.h"

USING_NS_CC;
USING_NS_CC_EXT;

SEL_MenuHandler TestHeaderLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBackClicked", TestHeaderLayer::onBackClicked);
    
    return NULL;    
}

SEL_CCControlHandler TestHeaderLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    
    return NULL;
}

void TestHeaderLayer::pressBTNLogin(cocos2d::CCObject * pSender)
{
    
}

void TestHeaderLayer::pressBTNRegister(cocos2d::CCObject * pSender)
{
    
}