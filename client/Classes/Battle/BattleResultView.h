//
//  BattleResultView.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_BattleResultView_h
#define HelloWorld_BattleResultView_h

#include "cocos2d.h"
#include "Basic.h"
#include "TaskBasic.h"
#include "BattleDefine.h"
#include "LuckySprite.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class BattleResultView : public CCLayer 
{
public:
    //
    LAYER_CREATE_FUNC(BattleResultView);
    
    void initView();
    
};

#endif
