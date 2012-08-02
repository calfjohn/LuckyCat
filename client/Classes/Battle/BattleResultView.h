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



class BattleResultView : public cocos2d::CCLayer 
{
public:
    //
    LAYER_CREATE_FUNC(BattleResultView);
    
    void initView(stTask *tTask);
    
};

#endif
