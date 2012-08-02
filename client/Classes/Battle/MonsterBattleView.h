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
#include "Basic.h"
#include "TaskBasic.h"
#include "BattleDefine.h"
#include "LuckySprite.h"
#include "BattleResultView.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class MonsterBattleView : public CCLayer 
{
public:
    //
    LAYER_CREATE_FUNC(MonsterBattleView);
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher(void);
    
    void initLayer(const stPage *p_page, CCObject *target, SEL_CallFuncND pfnSelector);
    
    void fightAction();
    
    CCFiniteTimeAction * createMonsterAction(unsigned int action_id);
    CCFiniteTimeAction * createBossAction(unsigned int action_id);
    
    void playAction();
    
    void playOneActionEnd();
    
    void showNextTask();
    
    //是否在战斗中
    static bool getIsInBattle();
    
    static void setIsInBattle(bool _b_state);
    
    
private:
    LuckySprite *pMonsterSprite;
    
    CCLabelTTF *pLabDes;
    CCLabelTTF *pLabEffect;
    CCLabelTTF *pLabSubHp;
    
    LuckySprite *pPlayerSprite;
    CCProgressTimer *pMonsterPLine;
    CCProgressTimer *pPlayerPLine;
    
    std::vector<unsigned int> mActionList;
    
    CCPoint pBeginPoint;
    
    CCObject*       m_target;         //callback listener
    
    SEL_CallFuncND  m_pfnSelector;    //callback selector
    
    const stPage *p_pPage;
    
    EventType mEventType;
    
    stTask *p_CurTask;
    stTalk *p_CurTalk;
    
    std::vector<stTalk *> mTalkList;
    
    CCLayerColor *m_LayerDialogBg;
    CCLabelTTF *m_LabDialog;
    
    GRole * p_Boss;
    
    std::vector<GRole *> mPlayerList;
    
    std::vector<stTask *> mTaskList;
    
    bool m_bIsWaitingForAction;
    
    BattleResultView *pBattleResultView;
    
    /*
     *@brief show all UI. hidden some.
     */
    void showUI();
    
    void showTalkUI();
    
    void showMonsterBattleUI();
    
    void showBossBattleUI();
    
    /*
     *@brief get the Event Type.
     */
    EventType getEventType();
    
    /*
     *@brief show the action in screan.
     */
    void showCurentEvent();
    
    /*
     *@brief get current task
     */
    stTask * getCurTask(int task_id);
    
    /*
     *@brief get next task
     */
    stTask * getNextTask();
    
    /*
     *@brief get current talk.
     */
    stTalk * getCurTalk();
    
    stTalk * getNextTalk();
    
    /*
     *@brief get the next event.
     */
    void getNextEvent();
    
    /*
     *@brief show an dialog
     */
    void showDialog();
    
    /*
     *@brief show an fight animation;
     */
    void showfightAnimation();
};

#endif
