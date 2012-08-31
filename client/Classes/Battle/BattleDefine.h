//
//  BattleDefine.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_BattleDefine_h
#define HelloWorld_BattleDefine_h

#include "cocos2d.h"

#define ACTION_TIME_JUMP        0.5f

#define ACTION_TIME_BLINK       1.2f
#define ACTION_BLINK_TIMES      5

#define ACTION_TIME_ACTTACK_EFFECT      1.2f

#define ACTION_TIME_SHOW_SKILL_NAME     0.5f

#define ACTION_TIME_DEFENCE_EFFECT      0.5f

#define ACTION_TIME_LABEL_SHOW_TIME     0.5f

#define COUNT_DOWN_TIMES                5
#define COUNT_DOWN_INTERVAL             1.0f

#define SHOW_ROUND_TIME                 1.0f


#define LABEL_MOVE_DISTANCE             35

enum GRolePosition {
    kGRolePositionUpOne      =   1,
    kGRolePositionUpTwo      =   2,
    kGRolePositionDownOne    =   3,
    kGRolePositionDownTwo    =   4,
    };

enum GRoleType {
    kGRoleTypeLeadingActor      =   1,
    kGRoleTypeMonster           =   2,
};

//ATTACK : int = 1;攻击
//CTRITICAL : int ＝2; 爆击
//CRUSH : int = 3;破防
//SUCK_BLOOD : int = 4;吸血
//
//HURT : int = 5;受击
//DODGE : int = 6;闪避
//REVERT : int = 7;反震
//
//DEAD : int = 8;死亡
enum GActionType {
    kGActionTypeAttack          =   1,
    kGActionTypeCritical_1      =   2,
    kGActionTypeCritical_2      =   3,
    kGActionTypeCrush           =   4,
    kGActionTypeSuckBlood_1     =   5,
    kGActionTypeSuckBlood_2     =   6,
    
    kGActionTypeHurt            =   7,
    kGActionTypeDodge           =   8,
    kGActionTypeRevert          =   9,
    kGActionTypeAddBlood        =   10,
    kGActionTypeDead            =   11,
    };

enum GTeam {
    kGTeamA = 1,
    kGTeamB = 2,
    };

class GRole
{
public:
    GRole():
    roleID(0),
    curHP(0),
    maxHp(0),
    curPercentHP(0.0f),
    pNodeRole(NULL),
    teamId(kGTeamA),
    actId(0),
    pProgressTimer(NULL),
    mStrName("")
    {}
    virtual ~GRole(){}
    int roleID;
    int curHP;
    int maxHp;
    cocos2d::CCNode *pNodeRole; //这个角色之所指向的对象
    cocos2d::CCProgressTimer *pProgressTimer;     //角色的血条
    GTeam teamId;
    int actId;
    std::string mStrName;
    
private:
    float curPercentHP;
    
public:
    float getCurPercentHP()
    {
        
        if ( maxHp ) curPercentHP = curHP * ( 1.0 / maxHp );
        
        return curPercentHP*100;
    }
    
    void setMaxHp(int _max_hp)
    {
        maxHp = _max_hp;
        curHP = _max_hp;
        if (maxHp < 0) {
            maxHp = 0;
            curHP = 0;
        }
    }
    
    void setCurHp(int _cur_hp)
    {
        curHP = _cur_hp;
        if (curHP < 0)
            curHP = 0;
        if (curHP > maxHp)
            curHP = maxHp;
    }
    
    void setSubHp(int _hp)
    {
        if ( curHP < _hp)
        {
            curHP = 0;
        }
        else
        {
            curHP -= abs(_hp);
        }
        printf("--->>>>CurHp : %d , Percentage %f\n",curHP,getCurPercentHP());
    }
    
    void setPlusHp(int _hp)
    {
        curHP += abs(_hp);
        if (curHP > maxHp)
            curHP = maxHp;
        printf("--->>>>CurHp : %d , Percentage %f\n",curHP,getCurPercentHP());
    }
    
    std::string getTeamStrName()
    {
        if (teamId == kGTeamB) {
            return "B";
        }
        else {
            return "A";
        }
    }
};

struct GRoleAction
{
public:
    GTeam           teamId;
    int             actId;
    GActionType     type;
    int             hurt;
    int             skillId;
    int             fx;
    
    std::string getTeamStrName()
    {
        if (teamId == kGTeamB) {
            return "B";
        }
        else {
            return "A";
        }
    }
};


#endif
