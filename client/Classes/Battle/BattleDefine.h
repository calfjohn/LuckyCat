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


#define LABEL_MOVE_DISTANCE             15

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
    kGActionTypeCritical        =   2,
    kGActionTypeCrush           =   3,
    kGActionTypeSuckBlood       =   4,
    kGActionTypeHurt            =   5,
    kGActionTypeDodge           =   6,
    kGActionTypeRevert          =   7,
    kGActionTypeDead            =   8,
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
    rolePosition(kGRolePositionUpOne),
    pCCProgressTimer(NULL)
    {}
    virtual ~GRole(){}
    unsigned int roleID;
    unsigned int curHP;
    unsigned int maxHp;
    cocos2d::CCNode *pNodeRole; //这个角色之所指向的对象
    cocos2d::CCProgressTimer *pCCProgressTimer;     //角色的血条
    GRolePosition rolePosition;  //角色站位
    
private:
    float curPercentHP;
    
public:
    float getCurPercentHP()
    {
        
        if ( maxHp ) curPercentHP = curHP * ( 1.0 / maxHp );
        
        if (curPercentHP > 100)
        {
            curPercentHP = 100;
        }
        return curPercentHP;//*100;
    }
    
    void setMaxHp(unsigned int _max_hp)
    {
        maxHp = _max_hp;
        curHP = _max_hp;
        if (pCCProgressTimer)
            pCCProgressTimer->setPercentage(maxHp);
    }
    
    void setCurHp(unsigned int _cur_hp)
    {
        curHP = _cur_hp;
        if (pCCProgressTimer)
            pCCProgressTimer->setPercentage(curHP);
    }
    
    void setSubHp(unsigned int _hp)
    {
        if ( curHP < _hp)
        {
            curHP = 0;
        }
        else
        {
            curHP -= _hp;
        }
        printf("--->>>>CurHp : %d , Percentage %f\n",curHP,getCurPercentHP());
        if (pCCProgressTimer)
        {
            cocos2d::CCProgressTo *toAction = cocos2d::CCProgressTo::create(ACTION_TIME_BLINK, getCurPercentHP());
            pCCProgressTimer->runAction(toAction);
            pCCProgressTimer->setPercentage(curHP);
        }
    }
};

class GRoleAction
{
public:
    GRoleAction():
    m_Attacker(kGRoleTypeLeadingActor),
    m_Defender(kGRoleTypeMonster),
    m_ActionType(kGActionTypeAttack){}
    virtual ~GRoleAction(){}
    
    unsigned int m_nHuntHp;
    
    GRoleType m_Attacker;
    GRoleType m_Defender;
    GActionType m_ActionType;
    
};


#endif
