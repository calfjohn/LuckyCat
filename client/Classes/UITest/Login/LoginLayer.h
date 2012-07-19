//
//  LoginLayer.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_LoginLayer_h
#define HelloWorld_LoginLayer_h

#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#include "cocos2d.h"

class LoginLayer : public cocos2d::CCLayer
//, public cocos2d::extension::CCBSelectorResolver
{
public:
    //
    //    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MLoginLayer, create);
    //    
    //    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    //    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    //    
    //    void onBackClicked(cocos2d::CCObject * pSender);
    
    LAYER_CREATE_FUNC(LoginLayer);
    
    virtual void onEnter();
    
    void initLayer();
    
};

#endif
