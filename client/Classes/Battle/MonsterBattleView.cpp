//
//  MonsterBattleView.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MonsterBattleView.h"
#include "BattleDefine.h"
#include "LevelDataManager.h"
#include "DictDataManager.h"
#include "TaskDataManager.h"

static bool m_bIsInBattle = false;

void MonsterBattleView::onEnter()
{
    CCLayer::onEnter();
    
    this->setTouchEnabled(true);
    
    pMonsterSprite = NULL;
    pLabDes = NULL;
    pLabEffect = NULL;
    pLabSubHp = NULL;
    pPlayerSprite = NULL;
    pMonsterPLine = NULL;
    pPlayerPLine = NULL;
    
}

bool MonsterBattleView::ccTouchBegan(CCTouch* touch, CCEvent *pEvent)
{
    if ( mEventType == monsterBattleEvent && !touch) return false;
    
    pBeginPoint = this->convertTouchToNodeSpace(touch);
    
    return true;
}

void MonsterBattleView::ccTouchMoved(CCTouch* touch, CCEvent *pEvent)
{
    
}

void MonsterBattleView::ccTouchEnded(CCTouch* touch, CCEvent *pEvent)
{
    if ( !touch ) return;
    CCPoint endPoint = this->convertTouchToNodeSpace(touch);
    
    CCFloat distance_ = ccpDistanceSQ(endPoint, pBeginPoint);
    
    if (distance_ > 2.0f)
    {
        //触发随机事件
        this->showCurentEvent();
    }
}

void MonsterBattleView::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}


void MonsterBattleView::initLayer(stPage *p_page, CCObject *target, SEL_CallFuncND pfnSelector)
{
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    p_pPage = p_page;
    
    if ( p_pPage == NULL )return;
    
    getCurTask(p_pPage->taskId);
    
    setIsInBattle(true);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    //    cocos2d::CCLabelTTF *titleLabel = cocos2d::CCLabelTTF::create( "Monster Fight!", CCSizeMake(screanSize.width, 50),kCCVerticalTextAlignmentCenter,kCCVerticalTextAlignmentCenter,"Arial", 24); 
    //    titleLabel = CCLabelTTF::initWithString("Monster Fight!", "Arial", 50);
    
    CCLabelTTF *titleLabel = CCLabelTTF::create(p_pPage->name.c_str(), CCSizeMake(screanSize.width, 50), kCCTextAlignmentCenter,"Arial", 30);
    //cellLabel->setPosition(ccp(cellSize.width , cellSize.height )); 
    titleLabel->setAnchorPoint(ccp(0.5,0.5));
    titleLabel->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height- 40));
    titleLabel->setColor(ccc3(255,55,0));
    this->addChild(titleLabel);
    
    string tempName;
    const stMonster* pMonster = DictDataManager::shareDictDataManager()->getMonsterImageId(p_CurTask->targetId);
    tempName = "image/monster/" + LevelDataManager::shareLevelDataManager()->ConvertToString(pMonster->image_id) + ".png";
    
    pMonsterSprite = CCSprite::create(tempName.c_str());
    pMonsterSprite->setPosition(CCPointMake(screanSize.width*0.5f, 260));
    this->addChild(pMonsterSprite);
    pMonsterSprite->setTag(TAG_MONSTER_SPRITE);
    
    CCLabelTTF *dscLabel = CCLabelTTF::create("", CCSizeMake(screanSize.width, 50), kCCTextAlignmentCenter,"Arial", 30);
    //cellLabel->setPosition(ccp(cellSize.width , cellSize.height )); 
    dscLabel->setAnchorPoint(ccp(0.5,0.5));
    dscLabel->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.75f));
    dscLabel->setColor(ccc3(255,55,0));
    this->addChild(dscLabel);
    dscLabel->setTag(TAG_LABEL_DES);
    
    dscLabel->setVisible(false);
    
    pMonsterSprite->setScale(0.5f);
    
    
    if ( getEventType() == talkEvent )
    {
        m_LayerDialogBg = CCLayerColor::create(ccc4(0, 0, 0, 255));
        m_LayerDialogBg->setAnchorPoint(CCPointZero);
        m_LayerDialogBg->setContentSize(CCSizeMake(screanSize.width * 0.8f, screanSize.height * 0.2f));
        m_LayerDialogBg->setPosition(CCPointMake(screanSize.width * 0.1f, 100));
        this->addChild(m_LayerDialogBg);
        
//        CCRect tDailogRect = CCRectMake(0, 0, m_LayerDialogBg->getContentSize().width, m_LayerDialogBg->getContentSize().height);
//        CCRect tCapRect = CCRectMake(0, 0, 4, 4);
//        CCScale9Sprite *p_dailogImgBg = CCScale9Sprite::create("image/extensions/scale9bg_1.png", tDailogRect,tCapRect);
//        p_dailogImgBg->setAnchorPoint(CCPointZero);
//        p_dailogImgBg->setPosition(CCPointZero);
//        m_LayerDialogBg->addChild(p_dailogImgBg);
        
        m_LabDialog = CCLabelTTF::create("", m_LayerDialogBg->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter,"Arial", 18);
        m_LabDialog->setColor(ccWHITE);
        m_LabDialog->setAnchorPoint(CCPointZero);
        m_LabDialog->setPosition(CCPointZero);
        m_LayerDialogBg->addChild(m_LabDialog);
        
        m_LayerDialogBg->setVisible(false);
    }
    
    CCFiniteTimeAction *pAction = CCSequence::create(CCScaleTo::create(ACTION_INTERVAL_TIME,1.0f),CCCallFunc::create(this, callfunc_selector(MonsterBattleView::showCurentEvent)),NULL);
    
    pMonsterSprite->runAction(pAction);
    
}

void MonsterBattleView::fightAction()
{
    mActionList.push_back(3);
    mActionList.push_back(1);
    mActionList.push_back(2);
    mActionList.push_back(1);
    
    
    CCDelayTime *pDelay1 = CCDelayTime::create(TRANSITION_PAGE_INTERVAL_TIME);
    CCFiniteTimeAction *pAction = CCSequence::create(pDelay1,CCCallFunc::create(this, callfunc_selector(MonsterBattleView::showCurentEvent)),NULL);
    
    this->runAction(pAction);
}

CCFiniteTimeAction * MonsterBattleView::createSequece(unsigned int action_id)
{
    CCFiniteTimeAction *pAction = NULL;
    switch (action_id) {
        case 1:
        {
            CCSprite *pSprite = (CCSprite *)this->getChildByTag(TAG_MONSTER_SPRITE);
            CCPoint p_curPos = pSprite->getPosition();
            CCMoveTo *move1 = CCMoveTo::create(ACTION_INTERVAL_TIME, CCPointMake(p_curPos.x -30 , p_curPos.y -30));
            CCMoveTo *move2 = CCMoveTo::create(ACTION_INTERVAL_TIME, CCPointMake(p_curPos.x + 60, p_curPos.y +60));
            CCMoveTo *move3 = CCMoveTo::create(ACTION_INTERVAL_TIME, p_curPos);
            
            pAction = CCSequence::create(move1,move2,move3,CCCallFunc::create(this, callfunc_selector(MonsterBattleView::playAction)),NULL);
            
            break;
        }
        case 2:
        {
            CCScaleBy *scale1 = CCScaleBy::create(ACTION_INTERVAL_TIME, 1.2f);
            CCScaleBy *scale2 = CCScaleBy::create(ACTION_INTERVAL_TIME, 1 / 1.2f);
            
            pAction = CCSequence::create(scale1,scale2,CCCallFunc::create(this, callfunc_selector(MonsterBattleView::playAction)),NULL);
            
            break;
            
        }
        case 3:
        {
            CCFadeIn *fade1 = CCFadeIn::create(ACTION_INTERVAL_TIME*2);
            pAction = CCSequence::create(fade1,CCDelayTime::create(ACTION_INTERVAL_TIME*3),CCCallFunc::create(this, callfunc_selector(MonsterBattleView::playAction)),NULL);
            
            break;
            
        }
        default:
            break;
    }
    
    return pAction;
}

void MonsterBattleView::playAction()
{
    
    
    if ( mActionList.empty() == false )
    {
        unsigned int tAcitonID = mActionList[mActionList.size()-1];
        CCFiniteTimeAction *pAction = this->createSequece(tAcitonID);
        mActionList.pop_back();
        
        if(pAction)
        {
            if ( tAcitonID == 3 )
            {
                CCLabelTTF *pLabel = (CCLabelTTF *)this->getChildByTag(TAG_LABEL_DES);
                pLabel->setColor(ccGREEN);
                pLabel->setString("你获得胜利!");
                pLabel->setVisible(true);
                pLabel->runAction(pAction);
            }
            else {
                CCSprite *pSprite = (CCSprite *)this->getChildByTag(TAG_MONSTER_SPRITE);
                pSprite->runAction(pAction);
            }
        }
    }
    else {
//        CCDirector::sharedDirector()->popScene();
        
        CCLayer *pLayer = (CCLayer *)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_BATTLE_LAYER));
        if ( pLayer )
        {
            pLayer->removeFromParentAndCleanup(true);
        }
        
        setIsInBattle(false);
        
        ((m_target)->*(m_pfnSelector))(this, NULL);
    }
}

bool MonsterBattleView::getIsInBattle()
{
    return m_bIsInBattle;
}

void MonsterBattleView::setIsInBattle(bool _b_state)
{
    m_bIsInBattle = _b_state;
}

stTask * MonsterBattleView::getCurTask(int task_id)
{
    p_CurTask = TaskDataManager::getShareInstance()->getTask(task_id);
    
    if ( p_CurTalk == NULL )
    {
        
    }
    else
    {
        switch (p_CurTask->type) {
            case generalBattle:
            {
                mEventType = monsterBattleEvent;
                p_CurTalk = NULL;
                break;
            }
            case DialogueTask:
            {
                mEventType = talkEvent;
                mTalkList = TaskDataManager::getShareInstance()->getAllTalk(p_pPage->taskId);
                break;
            }
            case specialBattle:
            {
                mEventType = bossBattleEvent;
                p_CurTalk = NULL;
            }
            default:
                break;
        }
    }
    
    mTalkList = TaskDataManager::getShareInstance()->getAllTalk(p_pPage->taskId);
    if (mTalkList.empty() == false)
    {
        mEventType = talkEvent;
    }
    return p_CurTask;
}

stTask * MonsterBattleView::getNextTask()
{
    if ( p_CurTask && p_CurTask->nextTaskId != 0)
        return this->getCurTask(p_CurTask->nextTaskId);
    else
        return NULL;
//    if ( p_CurTask && p_CurTask->nextTaskId != 0)
//    {
//        p_CurTask = TaskDataManager::getShareInstance()->getTask(p_CurTask->nextTaskId);
//        
//        mTalkList = TaskDataManager::getShareInstance()->getAllTalk(p_CurTask->nextTaskId);
//        
//        if ( mTalkList.empty() == false )
//            p_CurTalk = mTalkList[0];
//        else 
//            p_CurTalk = NULL;
//    }
//    
//    return p_CurTask;
}

stTalk * MonsterBattleView::getCurTalk()
{
    if ( mTalkList.empty() == false )
    {
        return mTalkList[0];
    }
    else return NULL;
}

stTalk * MonsterBattleView::getNextTalk()
{
    if ( mTalkList.empty() == false )
    {
        mTalkList.erase(mTalkList.begin());
        if ( mTalkList.empty() == false )
        {
            return mTalkList[0];
        }
        else
            return NULL;
    }
    else
        return NULL;
}

void MonsterBattleView::showUI()
{
    if ( mEventType == talkEvent )
    {
        
    }
    else if ( mEventType == monsterBattleEvent )
    {
        
    }
    else {
        
    }
}

EventType MonsterBattleView::getEventType()
{
    return talkEvent;
}

void MonsterBattleView::showCurentEvent()
{
    EventType _event =  getEventType();
    if ( talkEvent == _event ) {
        showDialog();
    }
    else
    {
        showfightAnimation();
    }
}

void MonsterBattleView::getNextEvent()
{
    if ( p_CurTask )
    {
        if ( mEventType == talkEvent )
        {
            //getNextTalk();
        }
        else
        {
            
        }
    }
}

void MonsterBattleView::showDialog()
{
    stTalk *tTalk = getCurTalk();
    if ( tTalk )
    {
        string dialog = "" + tTalk->npcName + " : " + tTalk->dialog;
        
        m_LabDialog->setString(dialog.c_str());
        
        m_LayerDialogBg->setVisible(true);
        
        this->getNextTalk();
    }
    else
    {
        CCLayer *pLayer = (CCLayer *)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_BATTLE_LAYER));
        if ( pLayer )
        {
            pLayer->removeFromParentAndCleanup(true);
        }
        
        setIsInBattle(false);
        
        ((m_target)->*(m_pfnSelector))(this, NULL);
    }
}

void MonsterBattleView::showfightAnimation()
{
    fightAction();
}
