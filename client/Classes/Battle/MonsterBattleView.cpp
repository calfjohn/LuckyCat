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
        if ( mEventType == oneEventWasFinished )
        {
            getNextTask();
        }
        //触发随机事件
        if ( mEventType == talkEvent )
        {
            this->showCurentEvent();
        }
        else if ( mEventType == bossBattleEvent )
        {
            if (m_bIsWaitingForAction)
            {
                this->playOneActionEnd();
            }
            else {
                this->showCurentEvent();
            }

        }
        else if ( mEventType == monsterBattleEvent ){
            stTask *tmp = this->getNextTask();
            if (tmp)this->showCurentEvent();
            else {
                CC_ASSERT(true);
            }
        }
        else  if ( mEventType == finishedEvent ||  mEventType == oneEventWasFinished ) {
            CCLayer *pLayer = (CCLayer *)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_BATTLE_LAYER));
            if ( pLayer )
            {
                pLayer->removeFromParentAndCleanup(true);
            }
            
            setIsInBattle(false);
            
            m_bIsWaitingForAction = false;
            
            ((m_target)->*(m_pfnSelector))(this, NULL);
        }
    }
}

void MonsterBattleView::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}


void MonsterBattleView::initLayer(stPage *p_page, CCObject *target, SEL_CallFuncND pfnSelector)
{
    pMonsterSprite = NULL;
    
    pLabDes = NULL;
    
    pLabEffect = NULL;
    pLabSubHp = NULL;
    pPlayerSprite = NULL;
    pMonsterPLine = NULL;
    pPlayerPLine = NULL;
    
    m_LayerDialogBg = NULL;
    m_LabDialog = NULL;
    
    m_bIsWaitingForAction = false;
    
    mEventType = oneEventWasFinished;
    
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    p_pPage = p_page;
    
    if ( p_pPage == NULL )return;
    
    mTalkList.clear();
    mTaskList = TaskDataManager::getShareInstance()->getASeriesOfTask(p_pPage->taskId);
    
    p_CurTask = getCurTask(p_pPage->taskId);
    
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
    
    LuckySprite *_pMonsterSprite = LuckySprite::create(p_CurTask->targetId);
    _pMonsterSprite->setPosition(CCPointMake(screanSize.width*0.5f, 260));
    this->addChild(_pMonsterSprite);
    _pMonsterSprite->setTag(TAG_MONSTER_SPRITE);

    
    CCLabelTTF *dscLabel = CCLabelTTF::create("", CCSizeMake(screanSize.width, 50), kCCTextAlignmentCenter,"Arial", 30);
    //cellLabel->setPosition(ccp(cellSize.width , cellSize.height )); 
    dscLabel->setAnchorPoint(ccp(0.5,0.5));
    dscLabel->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.75f));
    dscLabel->setColor(ccc3(255,55,0));
    this->addChild(dscLabel);
    dscLabel->setTag(TAG_LABEL_DES);
    
    dscLabel->setVisible(false);
    
    showCurentEvent();
    
}

void MonsterBattleView::fightAction()
{

}

CCFiniteTimeAction * MonsterBattleView::createMonsterAction(unsigned int action_id)
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

CCFiniteTimeAction * MonsterBattleView::createBossAction(unsigned int action_id)
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
            
            pAction = CCSequence::create(move1,move2,move3,NULL);
            
            int _subHp = 45;
            p_Boss->setSubHp(_subHp);
            CCProgressTimer *progress = (CCProgressTimer *)this->getChildByTag(TAG_MONSTER_PLINE);
            if ( progress )
                progress->setPercentage( p_Boss->getCurPercentHP() );
            
            
            CCLabelTTF *label = (CCLabelTTF *)this->getChildByTag(TAG_LABEL_SUB_HP);
            if ( label )
            {
                label->setPosition(ccp(220,210));
                char strChar[100];
                memset(strChar, 0, 100);
                sprintf(strChar, "%d",-_subHp);
                label->setString(strChar);
                label->setVisible(true);
                
                CCMoveBy *move = CCMoveBy::create(ACTION_INTERVAL_TIME, ccp(0,30));
                label->runAction(move);
            }
            
            break;
        }
        case 2:
        {
            CCScaleBy *scale1 = CCScaleBy::create(ACTION_INTERVAL_TIME, 1.2f);
            CCScaleBy *scale2 = CCScaleBy::create(ACTION_INTERVAL_TIME, 1 / 1.2f);
            
            pAction = CCSequence::create(scale1,scale2,NULL);
            
            int _subHp = 120;
            p_Boss->setSubHp(_subHp);
            CCProgressTimer *progress = (CCProgressTimer *)this->getChildByTag(TAG_MONSTER_PLINE);
            if ( progress )
                progress->setPercentage( p_Boss->getCurPercentHP() );
            
            CCLabelTTF *label = (CCLabelTTF *)this->getChildByTag(TAG_LABEL_SUB_HP);
            if ( label )
            {
                label->setPosition(ccp(220,210));
                char strChar[100];
                memset(strChar, 0, 100);
                sprintf(strChar, "暴击 %d",-_subHp);
                label->setString(strChar);
                label->setVisible(true);
                
                CCMoveBy *move = CCMoveBy::create(ACTION_INTERVAL_TIME, ccp(0,30));
                label->runAction(move);
            }
            
            break;
        }
        case 3:
        {
            CCFadeIn *fade1 = CCFadeIn::create(ACTION_INTERVAL_TIME*2);
            pAction = CCSequence::create(fade1,CCDelayTime::create(ACTION_INTERVAL_TIME*3),CCCallFunc::create(this, callfunc_selector(MonsterBattleView::playOneActionEnd)),NULL);
            
            break;
        }
        case 4:
        {
            CCScaleBy *scale1 = CCScaleBy::create(ACTION_INTERVAL_TIME, 1.2f);
            CCScaleBy *scale2 = CCScaleBy::create(ACTION_INTERVAL_TIME, 1 / 1.2f);
            
            pAction = CCSequence::create(scale1,scale2,CCCallFunc::create(this, callfunc_selector(MonsterBattleView::playOneActionEnd)),NULL);
            
            GRole *p_player = mPlayerList[0];
            
            int _subHp = 22;
            p_player->setSubHp(_subHp);
            CCProgressTimer *progress = (CCProgressTimer *)this->getChildByTag(TAG_PLAYER_PLINE);
            if ( progress )
                progress->setPercentage( p_player->getCurPercentHP() );
            
            CCLabelTTF *label = (CCLabelTTF *)this->getChildByTag(TAG_LABEL_SUB_HP);
            if ( label )
            {
                label->setPosition(ccp(220,80));
                char strChar[100];
                memset(strChar, 0, 100);
                sprintf(strChar, "%d",-_subHp);
                label->setString(strChar);
                label->setVisible(true);
                
                CCMoveBy *move = CCMoveBy::create(ACTION_INTERVAL_TIME, ccp(0,30));
                label->runAction(move);
            }
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
        CCFiniteTimeAction *pAction = this->createMonsterAction(tAcitonID);
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
        mEventType = oneEventWasFinished;
        //this->showNextTask();
    }
}

void MonsterBattleView::playOneActionEnd()
{
    CCLabelTTF *label = (CCLabelTTF *)this->getChildByTag(TAG_LABEL_SUB_HP);
    if ( label )
    {
        label->setVisible(false);
    }
    CCLabelTTF *pLabel = (CCLabelTTF *)this->getChildByTag(TAG_LABEL_DES);
    {
        pLabel->setVisible(false);
    }
    
    if ( mActionList.empty() == false )
    {
        unsigned int tAcitonID = mActionList[mActionList.size()-1];
        
        CCFiniteTimeAction *pAction = this->createBossAction(tAcitonID);
        mActionList.pop_back();
        
        if ( tAcitonID == 3 )
        {
            if(pAction)
            {
                CCLabelTTF *pLabel = (CCLabelTTF *)this->getChildByTag(TAG_LABEL_DES);
                pLabel->setColor(ccGREEN);
                pLabel->setString("你获得胜利!");
                pLabel->setVisible(true);
                pLabel->runAction(pAction);
            }
        }
        else if ( tAcitonID == 4 ){
            CCSprite *pSprite = (CCSprite *)this->getChildByTag(TAG_PLAYER_SPRITE);
            pSprite->runAction(pAction);
            m_bIsWaitingForAction = true;
        }
        else {
            m_bIsWaitingForAction = true;
            CCSprite *pSprite = (CCSprite *)this->getChildByTag(TAG_MONSTER_SPRITE);
            pSprite->runAction(pAction);
        }
    }
    else {
        mEventType = oneEventWasFinished;
        //this->showNextTask();
    }
}

void MonsterBattleView::showNextTask()
{
    stTask *tmp = this->getNextTask();
    if ( tmp )
    {
        this->showUI();
    }
    else {
        CCLayer *pLayer = (CCLayer *)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_BATTLE_LAYER));
        if ( pLayer )
        {
            pLayer->removeFromParentAndCleanup(true);
        }
        
        setIsInBattle(false);
        
        m_bIsWaitingForAction = false;
        
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
    if ( mTaskList.empty() == false )
    {
        p_CurTask = mTaskList[0];
        
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
                mTalkList.clear();
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
    else {
        p_CurTask = NULL;
    }
    
    return p_CurTask;
}

stTask * MonsterBattleView::getNextTask()
{
//    if ( p_CurTask && p_CurTask->nextTaskId != -1)
//        return this->getCurTask(p_CurTask->nextTaskId);
//    else
//        return NULL;
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
    if ( mTaskList.empty() == false )
    {
        std::vector<stTask *>::iterator _iter = mTaskList.begin();
        mTaskList.erase(_iter);
        
        if ( mTaskList.empty() == false )
        {
            p_CurTask = mTaskList[0];
            
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
                    mTalkList.clear();
                    mTalkList = TaskDataManager::getShareInstance()->getAllTalk(p_pPage->taskId);
                    break;
                }
                case specialBattle:
                {
                    mEventType = bossBattleEvent;
                    m_bIsWaitingForAction = false;
                    p_CurTalk = NULL;
                    break;
                }
                default:
                {
                    mEventType = finishedEvent;
                    p_CurTask = NULL;
                    break;
                }
            }
            return p_CurTask;
        }
        else {
            return NULL;
        }
    }
    else {
        return NULL;
    }
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
    CCLabelTTF *pLabel = (CCLabelTTF *)this->getChildByTag(TAG_LABEL_DES);
    pLabel->setVisible(false);
    if ( mEventType == talkEvent )
    {
        showTalkUI();
    }
    else if ( mEventType == monsterBattleEvent )
    {
        showMonsterBattleUI();
    }
    else {
        showBossBattleUI();
    }
    

}

void MonsterBattleView::showTalkUI()
{
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    if ( !pMonsterSprite )
    {
        pMonsterSprite = LuckySprite::create(p_CurTask->targetId);
        pMonsterSprite->setPosition(CCPointMake(screanSize.width*0.5f, 260));
        this->addChild(pMonsterSprite);
        pMonsterSprite->setTag(TAG_MONSTER_SPRITE);
    }
    else {
        string tempName;
        const stMonster* pMonster = DictDataManager::shareDictDataManager()->getMonsterImageId(p_CurTask->targetId);
        tempName = "image/monster/" + LevelDataManager::shareLevelDataManager()->ConvertToString(pMonster->imageId) + ".png";
        
        CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(tempName.c_str());
        pMonsterSprite->setTexture(pTexture);
    }
    
    pMonsterSprite->setScale(0.5f);
    
    
    //only talk ui have this.
    
    if ( !m_LayerDialogBg )
    {
        m_LayerDialogBg = CCLayerColor::create(ccc4(0, 0, 0, 255));
        m_LayerDialogBg->setAnchorPoint(CCPointZero);
        m_LayerDialogBg->setContentSize(CCSizeMake(screanSize.width * 0.8f, screanSize.height * 0.2f));
        m_LayerDialogBg->setPosition(CCPointMake(screanSize.width * 0.1f, 100));
        this->addChild(m_LayerDialogBg,4);
        
        m_LayerDialogBg->setVisible(false);
        
        m_LabDialog = CCLabelTTF::create("", m_LayerDialogBg->getContentSize(), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter,"Arial", 18);
        m_LabDialog->setColor(ccWHITE);
        m_LabDialog->setAnchorPoint(CCPointZero);
        m_LabDialog->setPosition(CCPointZero);
        m_LabDialog->setTag(TAG_LABEL_TALK);
        m_LayerDialogBg->addChild(m_LabDialog);
    }
    
//    CCRect tDailogRect = CCRectMake(0, 0, m_LayerDialogBg->getContentSize().width, m_LayerDialogBg->getContentSize().height);
//    CCRect tCapRect = CCRectMake(0, 0, 4, 4);
//    CCScale9Sprite *p_dailogImgBg = CCScale9Sprite::create("image/extensions/scale9bg_1.png", tDailogRect,tCapRect);
//    p_dailogImgBg->setAnchorPoint(CCPointZero);
//    p_dailogImgBg->setPosition(CCPointZero);
//    m_LayerDialogBg->addChild(p_dailogImgBg);
    
//    CCFiniteTimeAction *pAction = CCSequence::create(CCScaleTo::create(ACTION_INTERVAL_TIME,1.0f),CCCallFunc::create(this, callfunc_selector(MonsterBattleView::showCurentEvent)),NULL);
//    
//    pMonsterSprite->runAction(pAction);
}

void MonsterBattleView::showMonsterBattleUI()
{
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    if ( !pMonsterSprite )
    {
        pMonsterSprite = LuckySprite::create(p_CurTask->targetId);
        pMonsterSprite->setPosition(CCPointMake(screanSize.width*0.5f, 260));
        this->addChild(pMonsterSprite);
        pMonsterSprite->setTag(TAG_MONSTER_SPRITE);
    }
    else {
        string tempName;
        const stMonster* pMonster = DictDataManager::shareDictDataManager()->getMonsterImageId(p_CurTask->targetId);
        tempName = "image/monster/" + LevelDataManager::shareLevelDataManager()->ConvertToString(pMonster->imageId) + ".png";
        
        CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(tempName.c_str());
        pMonsterSprite->setTexture(pTexture);
    }
    
    pMonsterSprite->setScale(0.5f);
    
    if (pPlayerSprite) 
    {
        pPlayerSprite->setVisible(false);
        pPlayerPLine->setVisible(false);
        pMonsterPLine->setVisible(false);
    }
    if ( m_LayerDialogBg )
    {
        m_LayerDialogBg->setVisible(false);
    }
}

void MonsterBattleView::showBossBattleUI()
{
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    if ( !pMonsterSprite )
    {
        pMonsterSprite = LuckySprite::create(p_CurTask->targetId);
        pMonsterSprite->setPosition(CCPointMake(screanSize.width*0.5f, 260));
        this->addChild(pMonsterSprite);
        pMonsterSprite->setTag(TAG_MONSTER_SPRITE);
    }
    else {
        LuckySprite *pTempSprite = LuckySprite::create(p_CurTask->targetId);
        pMonsterSprite->setTexture(pTempSprite->getTexture());
    }
    
    pMonsterSprite->setScale(0.5f);
    
    if ( !pPlayerSprite )
    {
        pPlayerSprite = LuckySprite::create(37);
        pPlayerSprite->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.20f));
        this->addChild(pPlayerSprite);
        pPlayerSprite->setTag(TAG_PLAYER_SPRITE);
        
        
        pMonsterPLine = CCProgressTimer::create(LuckySprite::create(1001));
        pMonsterPLine->setType(kCCProgressTimerTypeBar);
        pMonsterPLine->setMidpoint(ccp(0.0f, 0.5f));
        pMonsterPLine->setPercentage(100);
        pMonsterPLine->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height- 50));
        //pProgressBoss->setColor(ccGRAY);
        this->addChild(pMonsterPLine,3);
        pMonsterPLine->setTag(TAG_MONSTER_PLINE);
        
        pPlayerPLine = CCProgressTimer::create(LuckySprite::create(1001));
        pPlayerPLine->setType(kCCProgressTimerTypeBar);
        pPlayerPLine->setMidpoint(ccp(0.0f, 0.5f));
        pPlayerPLine->setPercentage(100);
        pPlayerPLine->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.05f));
        this->addChild(pPlayerPLine,3);
        pPlayerPLine->setTag(TAG_PLAYER_PLINE);
        
        pLabEffect = CCLabelTTF::create("", CCSizeMake(100, 25), kCCTextAlignmentCenter,"Arial", 23);
        pLabEffect->setAnchorPoint(ccp(0.5,0.5));
        pLabEffect->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.75f));
        pLabEffect->setColor(ccc3(255,55,0));
        this->addChild(pLabEffect);
        pLabEffect->setTag(TAG_LABEL_EFFECT);
        pLabEffect->setVisible(false);
        
        pLabSubHp = CCLabelTTF::create("", CCSizeMake(100, 25), kCCTextAlignmentCenter,"Arial", 22);
        pLabSubHp->setAnchorPoint(ccp(0.5,0.5));
        pLabSubHp->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.75f));
        pLabSubHp->setColor(ccc3(255,55,0));
        this->addChild(pLabSubHp,3);
        pLabSubHp->setTag(TAG_LABEL_SUB_HP);
        pLabSubHp->setVisible(false);
    }
    else {
        LuckySprite *pTempSprite =LuckySprite::create(p_CurTask->targetId);
        pMonsterSprite->setTexture(pTempSprite->getTexture());
        
        LuckySprite *pTempSprite2 = LuckySprite::create(37);
        pPlayerSprite->setTexture(pTempSprite2->getTexture());
        
        pPlayerPLine->setVisible(true);
        
        pMonsterPLine->setPercentage(100); 
        pPlayerPLine->setPercentage(100);
    }
    if ( m_LayerDialogBg )
    {
        m_LayerDialogBg->setVisible(false);
    }
}

EventType MonsterBattleView::getEventType()
{
    return mEventType;
}

void MonsterBattleView::showCurentEvent()
{
    this->showUI();
    EventType _event =  getEventType();
    if ( talkEvent == _event ) {
        showDialog();
    }
    else
    {
        showfightAnimation();
    }
    
    printf("--------------------------\n");
    if (p_CurTask)p_CurTask->print();
    printf("--------------------------\n");
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
        
        CCLog("%s\n",dialog.c_str());
        
        if (m_LabDialog)m_LabDialog->setString(dialog.c_str());
        
        m_LayerDialogBg->setVisible(true);
        
        this->getNextTalk();
    }
    else
    {
        if (m_LabDialog)  m_LayerDialogBg->setVisible(false);
        mEventType = oneEventWasFinished;
        //this->showNextTask();
    }
}

void MonsterBattleView::showfightAnimation()
{
    if ( mEventType == monsterBattleEvent )
    {
        mActionList.push_back(3);
        mActionList.push_back(1);
        mActionList.push_back(2);
        mActionList.push_back(1);
        
        
//        CCDelayTime *pDelay1 = CCDelayTime::create(TRANSITION_PAGE_INTERVAL_TIME);
//        CCFiniteTimeAction *pAction = CCSequence::create(pDelay1,CCCallFunc::create(this, callfunc_selector(MonsterBattleView::showCurentEvent)),NULL);
//        
//        this->runAction(pAction);
        this->playAction();
    }
    else {
        mActionList.push_back(3);
        mActionList.push_back(1);
        mActionList.push_back(4);
        mActionList.push_back(2);
        mActionList.push_back(4);
        mActionList.push_back(1);
        mActionList.push_back(4);
        mActionList.push_back(1);
        
        mPlayerList.clear();
        
        p_Boss = new GRole();
        p_Boss->roleID = 1;
        p_Boss->setMaxHp(300);
        
        GRole * p_PlayerBoss = new GRole();
        p_PlayerBoss->setMaxHp(200);
        
        mPlayerList.push_back(p_PlayerBoss);
        
        
        this->playOneActionEnd();
    }
}
