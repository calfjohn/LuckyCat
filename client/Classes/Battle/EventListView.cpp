//
//  EventListView.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-8-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "EventListView.h"
#include "BattleDefine.h"
#include "LevelDataManager.h"
#include "DictDataManager.h"
#include "EventDataManager.h"
#include "NPCDialogView.h"
#include "GeneralBattleView.h"
#include "SpecialBattleView.h"
#include "OpenBoxView.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

static bool m_bIsInEvent = false;

bool EventListView::getIsInEvent()
{
    return m_bIsInEvent;
}

void EventListView::onEnter()
{
    CCLayer::onEnter();
}

void EventListView::initLayer(const stPage *p_page, CCObject *target, SEL_CallFuncND pfnSelector)
{
    mLEventType = kLEventTypeOneEventWasFinished;
    
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    p_pPage = p_page;
    
    if ( p_pPage == NULL )return;
    
    mEventList.clear();
    mEventList = EventDataManager::getShareInstance()->getASeriesOfEvent(p_pPage->eventId);
    
    p_CurEvent = getCurEvent();
    
    this->showCurEvent();
};

stEvent * EventListView::getCurEvent()
{
    if ( mEventList.empty() == false )
    {
        p_CurEvent = mEventList[0];
        
        switch (p_CurEvent->type) {
            case kLEventTypeGeneralBattle:
            {
                mLEventType = kLEventTypeGeneralBattle;

                break;
            }
            case kLEventTypeDialogue:
            {
                mLEventType = kLEventTypeDialogue;
                break;
            }
            case kLEventTypeSpecialBattle:
            {
                mLEventType = kLEventTypeSpecialBattle;
            }
            default:
                break;
        }
    }
    else {
        p_CurEvent = NULL;
    }
    
    return p_CurEvent;
}

void EventListView::popEvent()
{
    if ( mEventList.empty() == false )
    {
        std::vector<stEvent *>::iterator _iter = mEventList.begin();
        mEventList.erase(_iter);
        
        if ( mEventList.empty() == false )
        {
            p_CurEvent = mEventList[0];
            
            switch (p_CurEvent->type) {
                case kLEventTypeGeneralBattle:
                {
                    mLEventType = kLEventTypeGeneralBattle;
                    break;
                }
                case kLEventTypeDialogue:
                {
                    mLEventType = kLEventTypeDialogue;
                    break;
                }
                case kLEventTypeSpecialBattle:
                {
                    mLEventType = kLEventTypeSpecialBattle;
                    break;
                }
                default:
                {
                    mLEventType = kLEventTypeFinishedEvent;
                    p_CurEvent = NULL;
                    break;
                }
            }
        }
        else {
            mLEventType = kLEventTypeFinishedEvent;
            p_CurEvent = NULL;
        }
    }
    else {
        mLEventType = kLEventTypeFinishedEvent;
        p_CurEvent = NULL;
    }
}

LEventType EventListView::getLEventType()
{
    return mLEventType;
}

void EventListView::removeAndCleanSelf(float dt)
{
    m_bIsInEvent = false;
    
    ((m_target)->*(m_pfnSelector))(this, NULL);
    
    CCLayer *pLayer = (CCLayer *)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_BATTLE_LAYER));
    if ( pLayer )
    {
        pLayer->removeFromParentAndCleanup(true);
    }
}

void EventListView::callbackEventWasFinished(CCNode* node, void* data)
{
    this->scheduleOnce(schedule_selector(EventListView::showNextEvent), 0.1f);
}

void EventListView::showCurEvent()
{
    if ( mLEventType == kLEventTypeDialogue )
    {
        showDialogView();
    }
    else if ( mLEventType == kLEventTypeSpecialBattle )
    {
        showSpecialBattleView();
    }
    else if ( mLEventType == kLEventTypeGeneralBattle ){
        showGeneralBattleView();
    }
    else  if ( mLEventType == kLEventTypeFinishedEvent ||  mLEventType == kLEventTypeOneEventWasFinished ) {
        this->scheduleOnce(schedule_selector(EventListView::removeAndCleanSelf), 0.05f);
    }
}

void EventListView::showDialogView()
{
    NPCDialogView *tDialog = NPCDialogView::create(this);
    if (tDialog)
    {
        tDialog->setData(p_CurEvent, this, callfuncND_selector(EventListView::callbackEventWasFinished));
        
        p_CurLayer = static_cast<cocos2d::CCLayer *>(tDialog);
        
        this->addChild(p_CurLayer);
    }
}

void EventListView::showGeneralBattleView()
{
    GeneralBattleView *tGeneralBattle = GeneralBattleView::create(this);
    if (tGeneralBattle)
    {
        tGeneralBattle->setData(p_CurEvent, this, callfuncND_selector(EventListView::callbackEventWasFinished));
        
        p_CurLayer = static_cast<cocos2d::CCLayer *>(tGeneralBattle);
        
        this->addChild(p_CurLayer);
        
        this->showOpenBoxView();
    }
}

void EventListView::showSpecialBattleView()
{
    SpecialBattleView *tSpecialBattle = SpecialBattleView::create(this);
    if (tSpecialBattle)
    {
        tSpecialBattle->setData(p_CurEvent, this, callfuncND_selector(EventListView::callbackEventWasFinished));
        
        p_CurLayer = static_cast<cocos2d::CCLayer *>(tSpecialBattle);
        
        this->addChild(p_CurLayer);
        
        this->showOpenBoxView();
    }
}

void EventListView::showOpenBoxView()
{
    if ( p_CurEvent && p_CurEvent->box_id != -1 )
    {
        OpenBoxView *p = OpenBoxView::create(this);
        p->setEvent(p_CurEvent);
        this->addChild(p,99);
    }
}

void EventListView::showNextEvent(float dt)
{
    if ( p_CurLayer )
    {
        p_CurLayer->removeFromParentAndCleanup(true);
        
        p_CurLayer = NULL;
    }
    
    popEvent();
    
    showCurEvent();
}