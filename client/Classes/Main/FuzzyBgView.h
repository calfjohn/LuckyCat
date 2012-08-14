//
//  FuzzyBgView.h
//  LuckyCat
//
//  Created by XiaoZhong Zhu on 12-8-13.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef LuckyCat_FuzzyBgView_h
#define LuckyCat_FuzzyBgView_h

#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "extensions/CCBReader/CCLayerLoader.h"

#include "TaskBasic.h"

class FuzzyBgView
:public cocos2d::CCLayer
{
public:
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(FuzzyBgView, create);
};

class CCBReader;

class FuzzyBgViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(FuzzyBgViewLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(FuzzyBgView);
};

#endif
