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
#include "json/json.h"
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

enum TipMotion {
    kTipMotionGeneral       = 1,
    kTipMotionRise          = 2,
    kTipMotionSink          = 3,
    };

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
    void responseFight(CCNode *pNode, void* data);//服务器数据回调
    
    void CreateTeam(Json::Value &data);//创建战斗组，关联数据对象
    
    int m_nIndexList;               //战斗数据索引
    
    void showTips(const char *tips, CCPoint positon);
    
    void removeSelf(CCNode *pNode);
    
    Json::Value battleResult;       //战斗数据

    Json::Value playList;           //战斗动作序列
    
    cocos2d::CCPoint         pBeginPoint;
    
    LEventData *p_CurEvent;
    
    cocos2d::CCObject*       m_target;         //callback listener
    
    cocos2d::SEL_CallFuncND  m_pfnSelector;    //callback selector
    
    //map<string, map<int, CCNode*> > m_mapTeam;    //team id assiated with CCSprite
    
    CCAnimate *animationEffect[4];
    
    int m_nRound;           //current battle round
    
    
public:
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
    
    //显示一个动作
    void showRoleAction();
    
public:
    //在动作结束时,移除对像
    void callbackRemoveNodeWhenDidAction(CCNode * pNode);

    //显示Tip由上到下
    void showTip(std::string tStr, cocos2d::ccColor3B tColor, TipMotion tTipMotion = kTipMotionGeneral,unsigned int fontSize = 26,cocos2d::CCCallFuncN *callBack = NULL);
    
    CCActionInterval *GetSkillEffect(GActionType type);
    
    CCNode *getActionNode(GRoleAction tAction);
    
    std::string getActionName(GActionType type);
    
    //处理一个行为,对角色属性的影响
    void dealRoleAction(GRole *pRole,GRoleAction tAction);
private:
    //第几回合
    
    //当前回合中的第几个动作
    int m_nActionNumber;
    
    //倒计时冷却时间
    int m_nCountTime;
    
    //共有几个回合
    int m_nTotalRound;
    
    //一个回合内的动作列表
    std::vector<GRoleAction> m_OneRoundActionList;
    
    map<string, map<int, GRole> > m_mapTeam;    //team id assiated with CCSprite
};

class CCBReader;

class SpecialBattleViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SpecialBattleViewLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SpecialBattleView);
};

#endif
