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

#include "NetManager.h"
#include "CCMessageQueue.h"
#include "json/json.h"

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

void EventListView::initLayer(const int tChapterId,const stPage *p_page, CCObject *target, SEL_CallFuncND pfnSelector)
{
    m_bIsInEvent = true;
    
    mLEventType = kLEventTypeOneEventWasFinished;
    
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    p_pPage = p_page;
    
    mChapterId = tChapterId;
    
    p_HeroHeadView = NULL;
    
    if ( p_pPage == NULL )return;
    
    this->getEventDataList();
    
    //this->showHeroHeadView();
};

void EventListView::getEventDataList()
{
    NetManager::shareNetManager()->sendEx(kModeEvent, kDoGetEventList, callfuncND_selector(EventListView::netCallBackEventList), this, "\"chapterId\": %d, \"pageId\": %d, \"eventId\": %d", mChapterId, p_pPage->id, p_pPage->eventId);
}

void EventListView::netCallBackEventList(CCNode* pNode, void* data)
{
    if ( data )
    {
        ccnetwork::RequestInfo *tempInfo = static_cast<ccnetwork::RequestInfo *>(data);
        
        vector<stGood> tGoodsList;
        
        Json::Reader reader;
        Json::Value json_root;
        if (!reader.parse(tempInfo->strResponseData.c_str(), json_root))
            return;

        Json::Value json_meta = json_root["meta"];
        Json::Value json_out = json_meta["out"];
        int ret = json_out["result"].asInt();
        if ( ret != 0 )
        {
            return;
        }
        
        mEventDataList.clear();
        for (int i = 0; i < json_out["eventList"].size(); i++) 
        {
            Json::Value jEvent = json_out["eventList"][i];
            LEventData tEventData = LEventData();
            
            tEventData.id = jEvent["id"].asInt();
            tEventData.targetId = atoi(jEvent["target"].asCString());
            
            for (int j = 0; j < jEvent["bonus"].size(); j++) 
            {
                Json::Value jBonus = jEvent["bonus"][j];
                stGood tGoods;
                tGoods.id = jBonus["id"].asInt();
                tGoods.type = jBonus["type"].asInt();
                tGoods.count = jBonus["count"].asInt();
                
                tEventData.bonus.push_back(tGoods);
            }
            
            for (int j = 0; j < jEvent["awardArray"].size(); j++) 
            {
                Json::Value jBonus = jEvent["awardArray"][j];
                stGood tGoods;
                tGoods.id = jBonus["id"].asInt();
                tGoods.type = jBonus["type"].asInt();
                tGoods.count = jBonus["count"].asInt();
                
                tEventData.awardArray.push_back(tGoods);
            }
            
            stEvent *tStEvent = EventDataManager::getShareInstance()->getEvent(tEventData.id);
            tEventData.type = (LEventType)(jEvent["type"].asInt());
            tEventData.pStEvent = tStEvent;
            
            tEventData.box_id = jEvent["box_id"].asInt();
            
            if ( tEventData.box_id != -1 )
            {
                Json::Value jBonusArray = jEvent["boxAward"];
                std::vector<stGood> tVectorGood;
                for (int j = 0; j < jBonusArray.size(); j++) {
                    Json::Value jBonus = jBonusArray[j];
                    stGood tGoods;
                    tGoods.id = jBonus["id"].asInt();
                    tGoods.type = jBonus["type"].asInt();
                    tGoods.count = jBonus["count"].asInt();
                    
                    tVectorGood.push_back(tGoods);
                }
                tEventData.boxAward = tVectorGood;
            }else {
                tEventData.boxAward.clear();
            }
            
            if (tEventData.bonus.empty() == false) {
                tEventData.m_bBattleResultIsShowed = false;
            }
            else {
                tEventData.m_bBattleResultIsShowed = true;
            }
            
            Json::Value tempInfo = jEvent["basicInfo"];
            tEventData.basicInfo.userUuid = tempInfo["id"].asInt();
            tEventData.basicInfo.userNickName = tempInfo["nickname"].asString();
            tEventData.basicInfo.userSpeed = tempInfo["image_id"].asInt();
            tEventData.basicInfo.userLevel = tempInfo["level"].asInt();
            tEventData.basicInfo.userExp = tempInfo["exp"].asInt();
            tEventData.basicInfo.userHp = tempInfo["hp"].asDouble();
            tEventData.basicInfo.userCareerId = tempInfo["career_id"].asInt();
            tEventData.basicInfo.userChapterId = tempInfo["chapter_id"].asInt();
            tEventData.basicInfo.userPageId = tempInfo["page_id"].asInt();
            tEventData.basicInfo.userAttack = tempInfo["attack"].asDouble();
            tEventData.basicInfo.userDefence = tempInfo["defence"].asDouble();
            tEventData.basicInfo.userSpeed = tempInfo["speed"].asDouble();
            tEventData.basicInfo.userMaxHp = tempInfo["max_hp"].asInt();
                        
            mEventDataList.push_back(tEventData);
        }
        
        p_CurEvent = getCurEvent();
        
        this->showCurEvent();
    }
}

LEventData * EventListView::getCurEvent()
{
    if ( mEventDataList.empty() == false )
    {
        p_CurEvent = &mEventDataList[0];
        
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
        std::vector<LEventData>::iterator _iter = mEventDataList.begin();
        mEventDataList.erase(_iter);
        
        if ( mEventDataList.empty() == false )
        {
            p_CurEvent = &mEventDataList[0];
            
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
    
    this->removeAllChildLayer();
    
    ((m_target)->*(m_pfnSelector))(this, NULL);
}

void EventListView::callbackEventWasFinished(CCNode* node, void* data)
{
    this->scheduleOnce(schedule_selector(EventListView::showNextEvent), 0.01f);
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
        this->removeAllChildLayer();
        
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
        this->removeAllChildLayer();
        
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
        this->removeAllChildLayer();
        
        tSpecialBattle->setData(p_CurEvent, this, callfuncND_selector(EventListView::callbackEventWasFinished));
        
        p_CurLayer = static_cast<cocos2d::CCLayer *>(tSpecialBattle);
        
        this->addChild(p_CurLayer,kTagLayerBattle);
    }
}

void EventListView::showOpenBoxView()
{
    if ( p_CurEvent && p_CurEvent->m_bBoxIsOpened == false && p_CurEvent->box_id != -1 )
    {
        this->removeAllChildLayer();
        
        OpenBoxView *pLayer = OpenBoxView::create(this);
        pLayer->setSelector(this, callfuncND_selector(EventListView::callbackEventWasFinished));
        pLayer->setEvent(p_CurEvent);
        
        p_CurLayer = static_cast<cocos2d::CCLayer *>(pLayer);
        this->addChild(p_CurLayer,kTagLayerOpenBox);
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

void EventListView::showBattleResultView()
{
    this->removeAllChildLayer();
    
    BattleResultView *pLayer = BattleResultView::create(this);
    pLayer->setSelector(this, callfuncND_selector(EventListView::callbackEventWasFinished));
    p_CurEvent->setBattleResultIsShowed();
    pLayer->initView(p_CurEvent);
    
    p_CurLayer = static_cast<cocos2d::CCLayer *>(pLayer);
    
    this->addChild(p_CurLayer,kTagLayerBattleResult);
}

void EventListView::showNextEvent(float dt)
{
    if ( p_CurEvent && p_CurEvent->getBattleResultIsShowed() == false )
    {
        this->showBattleResultView(); 
    }
    else if ( p_CurEvent && p_CurEvent->mBattleProcess.m_battleResult == kBattleResultWin && p_CurEvent->m_bBoxIsOpened == false && p_CurEvent->box_id != -1 ) {
        this->showOpenBoxView();
    }
    else if ( p_CurEvent && p_CurEvent->mBattleProcess.m_battleResult == kBattleResultLost ){//战斗失败,事件不再执行
        removeAndCleanSelf(0);
    }else {
        popEvent();
        
        showCurEvent();
    }
}

void EventListView::removeAllChildLayer()
{
    if ( p_CurLayer )
    {
        p_CurLayer->removeFromParentAndCleanup(true);
        
        p_CurLayer = NULL;
    }
}