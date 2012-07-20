//
//  BattleDefine.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_BattleDefine_h
#define HelloWorld_BattleDefine_h

#define ACTION_INTERVAL_TIME    0.25f

//翻页所用时间
#define TRANSITION_PAGE_INTERVAL_TIME   1.0f

#define TAG_MONSTER_SPRITE      9
#define TAG_LABEL_DES      10
#define TAG_PLAYER_SPRITE   11
#define TAG_MONSTER_PLINE       12
#define TAG_PLAYER_PLINE       13


#define TAG_BATTLE_LAYER        99


class GRole
{
public:
    GRole():
    roleID(0),
    curHP(0),
    maxHp(0),
    curPercentHP(0.0f)
    {}
    virtual ~GRole(){}
    unsigned int roleID;
    unsigned int curHP;
    unsigned int maxHp;
    float curPercentHP;
    float getCurPercentHP()
    {
        
        if ( maxHp ) curPercentHP = curHP * ( 1.0 / maxHp );
        
        return curPercentHP;
    }
};


#endif
