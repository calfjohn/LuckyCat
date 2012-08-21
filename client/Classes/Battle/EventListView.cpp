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
#include "ChapterScene.h"
#include "HeroHeadView.h"

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
    
    p_HeroHeadView = NULL;
    p_OpenBoxView = NULL;
    
    if ( p_pPage == NULL )return;
    
    this->getEventDataList();
    
    this->showCurEvent();
    
    this->showHeroHeadView();
};

void EventListView::getEventDataList()
{
    this->netCallBackEventList(NULL,NULL);
}

void EventListView::netCallBackEventList(CCNode* pNode, void* data)
{
    mEventDataList.clear();
    std::vector<stEvent *> tStEventList = EventDataManager::getShareInstance()->getASeriesOfEvent(p_pPage->eventId);
    
    for (std::vector<stEvent *>::iterator _iter = tStEventList.begin(); _iter != tStEventList.end(); _iter++) {
        stEvent *tStEvent = *_iter;
        
        if (tStEvent)
        {
            LEventData *tEventData = new LEventData();
            
            tEventData->id = tStEvent->id;
            tEventData->type = tStEvent->type;
            tEventData->pStEvent = tStEvent;
            tEventData->targetId = tStEvent->targetId;
            tEventData->bonus = tStEvent->bonus;
            tEventData->pBattle = NULL;
            tEventData->box_id = tStEvent->box_id;
            
            mEventDataList.push_back(tEventData);
        }
    }
    
    p_CurEvent = getCurEvent();
}

LEventData * EventListView::getCurEvent()
{
    if ( mEventDataList.empty() == false )
    {
        p_CurEvent = mEventDataList[0];
        
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
    if ( mEventDataList.empty() == false )
    {
        std::vector<LEventData *>::iterator _iter = mEventDataList.begin();
        mEventDataList.erase(_iter);
        
        if ( mEventDataList.empty() == false )
        {
            p_CurEvent = mEventDataList[0];
            
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
//    CCScene *pScene = Chapter::scene();
//    
//    CCTransitionPageTurn *pTp = CCTransitionPageTurn::create(TRANSITION_PAGE_INTERVAL_TIME, pScene, false);
//    
//    CCDirector::sharedDirector()->replaceScene(pTp);
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
        
        this->addChild(p_CurLayer,kTagLayerDialog);
    }
}

void EventListView::showGeneralBattleView()
{
    GeneralBattleView *tGeneralBattle = GeneralBattleView::create(this);
    if (tGeneralBattle)
    {
        tGeneralBattle->setData(p_CurEvent, this, callfuncND_selector(EventListView::callbackEventWasFinished));
        
        p_CurLayer = static_cast<cocos2d::CCLayer *>(tGeneralBattle);
        
        this->addChild(p_CurLayer,kTagLayerBattle);
    }
}

void EventListView::showSpecialBattleView()
{
    SpecialBattleView *tSpecialBattle = SpecialBattleView::create(this);
    if (tSpecialBattle)
    {
        tSpecialBattle->setData(p_CurEvent, this, callfuncND_selector(EventListView::callbackEventWasFinished));
        
        p_CurLayer = static_cast<cocos2d::CCLayer *>(tSpecialBattle);
        
        this->addChild(p_CurLayer,kTagLayerBattle);
    }
}

void EventListView::showOpenBoxView()
{
    if ( p_CurEvent && p_CurEvent->mBoxIsOpened == false && p_CurEvent->box_id != -1 )
    {
        p_OpenBoxView = OpenBoxView::create(this);
        p_OpenBoxView->setSelector(this, callfuncND_selector(EventListView::callbackEventWasFinished));
        p_OpenBoxView->setEvent(p_CurEvent);
        this->addChild(p_OpenBoxView,kTagLayerOpenBox);
    }
}

void EventListView::showHeroHeadView()
{
    if (p_HeroHeadView)
    {
        p_HeroHeadView->removeFromParentAndCleanup(true);
        p_HeroHeadView = NULL;
    }
    else {
        p_HeroHeadView = HeroHeadView::create(this);
        this->addChild(p_HeroHeadView,kTagLayerHeroHead);
    }
}

void EventListView::showNextEvent(float dt)
{
    if ( p_CurEvent && p_CurEvent->mBoxIsOpened == false && p_CurEvent->box_id != -1 ) {
        this->showOpenBoxView();
    }
    else {
        if ( p_CurLayer )
        {
            p_CurLayer->removeFromParentAndCleanup(true);
            
            p_CurLayer = NULL;
        }
        if (p_HeroHeadView)
        {
            p_HeroHeadView->removeFromParentAndCleanup(true);
            p_HeroHeadView = NULL;
        }
        if (p_OpenBoxView)
        {
            p_OpenBoxView->removeFromParentAndCleanup(true);
            p_OpenBoxView = NULL;
        }
        
        popEvent();
        
        showCurEvent();
    }
}