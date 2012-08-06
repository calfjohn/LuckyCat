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



class MonsterBattleView : public cocos2d::CCLayer 
{
public:
    //
    LAYER_CREATE_FUNC(MonsterBattleView);
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher(void);

    void initLayer(const stPage *p_page, cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector);
    
    void fightAction();
    
    cocos2d::CCFiniteTimeAction * createMonsterAction(unsigned int action_id);
    cocos2d::CCFiniteTimeAction * createBossAction(unsigned int action_id);
    
    void playAction();
    
    void playOneActionEnd();
    
    void showNextTask();
    
    //是否在战斗中
    static bool getIsInBattle();
    
    static void setIsInBattle(bool _b_state);
    
    void removeAndCleanSelf(float dt);
    
    // a selector callback
    void menuBackCallback(cocos2d::CCObject* pSender);
private:
    LuckySprite *pMonsterSprite;
    
    cocos2d::CCLabelTTF *pLabDes;
    cocos2d::CCLabelTTF *pLabEffect;
    cocos2d::CCLabelTTF *pLabSubHp;
    
    LuckySprite *pPlayerSprite;
    cocos2d::CCProgressTimer *pMonsterPLine;
    cocos2d::CCProgressTimer *pPlayerPLine;
    
    std::vector<unsigned int> mActionList;
    
    cocos2d::CCPoint pBeginPoint;
    
    cocos2d::CCObject*       m_target;         //callback listener
    
    cocos2d::SEL_CallFuncND  m_pfnSelector;    //callback selector
    
    const stPage *p_pPage;
    
    EventType mEventType;
    
    stTask *p_CurTask;
    stTalk *p_CurTalk;
    
    std::vector<stTalk *> mTalkList;
    
    cocos2d::CCLayerColor *m_LayerDialogBg;
    cocos2d::CCLabelTTF *m_LabDialog;
    
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
