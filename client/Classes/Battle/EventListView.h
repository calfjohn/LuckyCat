//
//  EventListView.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-8-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_EventListView_h
#define HelloWorld_EventListView_h

#include "cocos2d.h"
#include "Basic.h"
#include "EventBasic.h"
#include "BattleDefine.h"
#include "LuckySprite.h"
#include "BattleResultView.h"
#include "NPCDialogView.h"

class HeroHeadView;

class EventListView : public cocos2d::CCLayer 
{
public:
    static bool getIsInEvent();
    //
    LAYER_CREATE_FUNC(EventListView);
    
    virtual void onEnter();
    
    void initLayer(const int tChapterId,const stPage *p_page, cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector);
    
    /*
     * this function will callback, when current Event was finished.
     */
    void callbackEventWasFinished(CCNode* node, void* data);

private:
    /*
     * pop current Event and show next Event, If there is no exit any Event, remove EventListView
     * It is work in fuctionf callbackEventWasFinished.
     */
    void showNextEvent(float dt);
    
    /*
     *@brief get current Event
     */
    LEventData * getCurEvent();
    
    /*
     *@brief pop current Event
     */
    void popEvent();
    
    /*
     *@brief get the Event Type.
     */
    LEventType getLEventType();
    
    
    /*
     * this function is show UI.
     */
    void showCurEvent();
    
    void showDialogView();
    
    void showGeneralBattleView();
    
    void showSpecialBattleView();
    
    void showOpenBoxView();
    
    void showHeroHeadView();
    
    void showBattleResultView();
    
    void removeAndCleanSelf(float dt);
    
    void removeAllChildLayer();
    
private:
    /*
     * get all EventData in one page.
     */
    void getEventDataList();
    
public:
    /*
     * net work will callback this fuction. init mEventDataList.
     */
    void netCallBackEventList(CCNode* pNode, void* data);
private:
    
    cocos2d::CCPoint pBeginPoint;
    
    cocos2d::CCObject*       m_target;         //callback listener
    
    cocos2d::SEL_CallFuncND  m_pfnSelector;    //callback selector
    
    const stPage *p_pPage;      //Point of page
    
    int mChapterId;
    
    LEventType mLEventType;       //Current Event's event type
    
    LEventData *p_CurEvent;          //Current Event
    
    std::vector<LEventData *> mEventDataList;        //All Event in this page
    
    cocos2d::CCLayer *p_CurLayer;       //Current Show Layer
    
    HeroHeadView *p_HeroHeadView;
};


#endif
