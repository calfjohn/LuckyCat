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
};

class CCBReader;

class SpecialBattleViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SpecialBattleViewLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SpecialBattleView);
};

#endif
