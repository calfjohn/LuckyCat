//
//  BattleDefine.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_BattleDefine_h
#define HelloWorld_BattleDefine_h

static const float ACTION_INTERVAL_TIME    = 0.25f;

//翻页所用时间
#define TRANSITION_PAGE_INTERVAL_TIME    3.0f

static const int TAG_MONSTER_SPRITE      = 9;
static const int TAG_LABEL_DES           = 10;
static const int TAG_LABEL_EFFECT        = 11;
static const int TAG_LABEL_SUB_HP        = 12;


static const int TAG_PLAYER_SPRITE       = 21;
static const int TAG_MONSTER_PLINE       = 22;
static const int TAG_PLAYER_PLINE        = 23;


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
    
private:
    float curPercentHP;
    
public:
    float getCurPercentHP()
    {
        
        if ( maxHp ) curPercentHP = curHP * ( 1.0 / maxHp );
        
        return curPercentHP*100;
    }
    
    void setMaxHp(unsigned int _max_hp)
    {
        maxHp = _max_hp;
        curHP = _max_hp;
    }
    
    void setSubHp(unsigned int _hp)
    {
        if ( curHP < _hp)curHP = 0;
        else curHP -= _hp;
    }
};


#endif
