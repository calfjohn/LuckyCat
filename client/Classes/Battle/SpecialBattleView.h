//
//  SpecialBattleView.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-8-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_SpecialBattleView_h
#define HelloWorld_SpecialBattleView_h

#include "TouchLayer.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "extensions/CCBReader/CCLayerLoader.h"
#include "json.h"
#include "EventBasic.h"
#include "BattleDefine.h"

typedef struct
{
	int type;
	int teamId;
	int dTid;
	int dPos;
	int hurt;
	int point;
	int talentId;
}stAction;

class SpecialBattleView 
: public TouchLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
{
public:
    SpecialBattleView();
    ~SpecialBattleView();
    
    static SpecialBattleView *create(cocos2d::CCObject * pOwner);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SpecialBattleView, create);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onMenuItemClicked(cocos2d::CCObject *pTarget);
    
    void onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    virtual void notificationTouchEvent(LTouchEvent tLTouchEvent);
    
    void setData(LEventData *tEvent, cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector);
    
    void removeAndCleanSelf(float dt);
    
    void menuBackCallback(CCObject* pSender);
private:
    void CallBackHeroAction();//战斗表现回调寒暑
    
    void responseFight(CCNode *pNode, void* data);//服务器数据回调
    
    void CreateTeam(Json::Value &data);//创建战斗组，关联数据对象
    
    int m_nIndexList;               //战斗数据索引
    
    Json::Value battleResult;       //战斗数据
    
    cocos2d::CCPoint         pBeginPoint;
    
    LEventData *p_CurEvent;
    
    cocos2d::CCObject*       m_target;         //callback listener
    
    cocos2d::SEL_CallFuncND  m_pfnSelector;    //callback selector
    
    map<string, map<int, CCNode*> > m_mapTeam;    //team id assiated with CCSprite
    
    CCAnimate *animationEffect[4];
    
    int m_nRound;           //current battle round
    
public:
    /*
     1. 进入战斗 (BOSS出现 / A vs B) 
     2. 分析 最新一回合战斗数据
     3. 显示 第几回合
     4. 如果,是操作者的角色,则倒计时. 时间到了玩家还没有按色子,然后执行4 ,程序主动帮玩家按一下.然后,执行4
     如果,不是操作者的角色, 执行 5
     5. 按色子, 显示色子结果
     6. 谁出手
     7. 翻放战斗效果. 1. 技能名, 2. 技能光效
     8. 被 打者动画, 1. 被打者闪一闪, 2. 扣血,闪避, 爆击, 3 血条变化.
     9. 如果, 双方到还没挂, 回到 2. 否则,到9
     10. 显示战斗结果
     */
    //1. 进入战斗 (BOSS出现 / A vs B) 
    void startBattle();
    
    //2. 分析 最新一回合战斗数据
    void analyseBattleData();
    
    //2. 显示 第几回合
    void showRoundNumber();
    
    //3. 倒计时,
    void countDown();
    
    void countDownSchedule(float tArg);
    
    //4. 按色子后, 显示色子结果.
    void showDiceResult();
    
    void pressControlButtonDice();
    
    //***************************
    
    
    //根据数据创建动画
    void battleAnimationCreate(Json::Value tOneRound);
    
    //攻击者动画, 显示攻击者是谁                1
    void attackerAnimation();//(GRole *pNodeRole,GRoleAction *pAction);
    
    //攻击者效果显示, 技能光效,                 2
    void attackerEffectAnimation();//(GRole *pNodeRole,GRoleAction *pAction);
    
    //显示技能名                               2
    void showSkillNameAnimation();//(GRole *pNodeRole,GRoleAction *pAction);
    
    //防守者动画, 显示防守者是谁                 3
    void defenderAnimation();//(GRole *pNodeRole,GRoleAction *pAction);
    
    //防守者效果显示, 如,扣血,闪避,爆击等         3
    void defenderEffectAnimation();//(GRole *pNodeRole,GRoleAction *pAction);
    
public:
    //在动作结束时,移除对像
    void callbackRemoveNodeWhenDidAction(CCNode * pNode);
    
    CCNode *pAttackEffectNode;
    GRole *pNodeAttacker;
    GRole *pNOdeDefener;
    
    GRoleAction *pRoleAction;
    
    std::vector<CCNode *> mHpLineList;
    std::vector<CCNode *> mHpLineBgList;
    
    std::vector<CCNode *> mHeroSpriteList;
    std::vector<CCNode *> mMonsterSpriteList;
    
    std::vector<CCProgressTimer *> mHpProgressTimerList;
    
    int m_nCountTime;
};

class CCBReader;

class SpecialBattleViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SpecialBattleViewLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SpecialBattleView);
};

#endif
