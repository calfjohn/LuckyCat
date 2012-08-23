//
//  BattleDefine.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_BattleDefine_h
#define HelloWorld_BattleDefine_h




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
