//
//  MonsterBattleView.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_MonsterBattleView_h
#define HelloWorld_MonsterBattleView_h

#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class MonsterBattleView : public CCLayer 
{
public:
    //
    LAYER_CREATE_FUNC(MonsterBattleView);
    
    virtual void onEnter();
    
    void initLayer();
    
    void fightAction();
    
    CCFiniteTimeAction * createSequece(unsigned int action_id);
    
    void playAction();
    
private:
    CCSprite *pMonsterSprite;
    
    std::vector<unsigned int> mActionList;
};

#endif
