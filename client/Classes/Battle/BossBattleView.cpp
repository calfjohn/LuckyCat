//
//  BossBattleView.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "BossBattleView.h"
#include "BattleDefine.h"
#include "LevelDataManager.h"
#include "DictDataManager.h"

static bool m_bIsInBattle = false;

void BossBattleView::onEnter()
{
    CCLayer::onEnter();
    
    pMonsterSprite = NULL;
    
    m_bIsWaitingForAction = false;
    
}

void BossBattleView::initLayer(stPage *page, CCObject *target, SEL_CallFuncND pfnSelector)
{
    p_pPage = page;
    
    this->setTouchEnabled(true);
    
    p_Boss = new GRole();
    p_Boss->roleID = p_pPage->monsterId;
    p_Boss->setMaxHp(300);
    
    mPlayerList.clear();
    
    GRole * p_PlayerBoss = new GRole();
    p_PlayerBoss->setMaxHp(200);
    
    mPlayerList.push_back(p_PlayerBoss);
    
    
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    setIsInBattle(true);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *titleLabel = CCLabelTTF::create(p_pPage->name.c_str(), CCSizeMake(screanSize.width, 50), kCCTextAlignmentCenter,"Arial", 30);
    titleLabel->setAnchorPoint(ccp(0.5,0.5));
    titleLabel->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height- 30));
    titleLabel->setColor(ccc3(255,55,0));
    this->addChild(titleLabel);
    
    string tempName;
    const stMonster* pMonster = DictDataManager::shareDictDataManager()->getMonsterImageId(p_pPage->monsterId);
    tempName = "image/monster/" + LevelDataManager::shareLevelDataManager()->ConvertToString(pMonster->image_id) + ".png";
    CCSprite *_pMonsterSprite = CCSprite::create(tempName.c_str());
    _pMonsterSprite->setPosition(CCPointMake(screanSize.width*0.5f, 260));
    this->addChild(_pMonsterSprite);
    _pMonsterSprite->setTag(TAG_MONSTER_SPRITE);
    
    CCLabelTTF *dscLabel = CCLabelTTF::create("", CCSizeMake(screanSize.width, 50), kCCTextAlignmentCenter,"Arial", 30);
    dscLabel->setAnchorPoint(ccp(0.5,0.5));
    dscLabel->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.82f));
    dscLabel->setColor(ccc3(255,55,0));
    this->addChild(dscLabel);
    dscLabel->setTag(TAG_LABEL_DES);
    
    dscLabel->setVisible(false);
    
    
    CCProgressTimer *pProgressBoss = CCProgressTimer::create(CCSprite::create("extensions/sliderProgress.png"));
    pProgressBoss->setType(kCCProgressTimerTypeBar);
    pProgressBoss->setMidpoint(ccp(0.0f, 0.5f));
    pProgressBoss->setPercentage(100);
    pProgressBoss->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height- 50));
    pProgressBoss->setColor(ccGRAY);
    this->addChild(pProgressBoss,3);
    pProgressBoss->setTag(TAG_MONSTER_PLINE);
    
    char strChar[512];
    memset(strChar, 0, 512);
    sprintf(strChar, "image/icon/hero_%d.png",1);
    
    CCSprite *_pPlayerSprite = CCSprite::create(strChar);
    _pPlayerSprite->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.20f));
    this->addChild(_pPlayerSprite);
    _pPlayerSprite->setTag(TAG_PLAYER_SPRITE);
    
    CCProgressTimer *pProgressPlayer = CCProgressTimer::create(CCSprite::create("extensions/sliderProgress.png"));
    pProgressPlayer->setType(kCCProgressTimerTypeBar);
    pProgressPlayer->setMidpoint(ccp(0.0f, 0.5f));
    pProgressPlayer->setPercentage(100);
    pProgressPlayer->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.05f));
    this->addChild(pProgressPlayer,3);
    pProgressPlayer->setTag(TAG_PLAYER_PLINE);
    
    CCLabelTTF *effectLabel = CCLabelTTF::create("", CCSizeMake(100, 25), kCCTextAlignmentCenter,"Arial", 23);
    effectLabel->setAnchorPoint(ccp(0.5,0.5));
    effectLabel->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.75f));
    effectLabel->setColor(ccc3(255,55,0));
    this->addChild(effectLabel);
    effectLabel->setTag(TAG_LABEL_EFFECT);
    effectLabel->setVisible(false);
    
    CCLabelTTF *subHP = CCLabelTTF::create("", CCSizeMake(100, 25), kCCTextAlignmentCenter,"Arial", 22);
    subHP->setAnchorPoint(ccp(0.5,0.5));
    subHP->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.75f));
    subHP->setColor(ccc3(255,55,0));
    this->addChild(subHP,3);
    subHP->setTag(TAG_LABEL_SUB_HP);
    subHP->setVisible(false);
    
    
    _pMonsterSprite->setScale(0.5f);
    CCFiniteTimeAction *pAction = CCSequence::create(CCScaleTo::create(ACTION_INTERVAL_TIME,1.0f),CCCallFunc::create(this, callfunc_selector(BossBattleView::fightAction)),NULL);
    
    _pMonsterSprite->runAction(pAction);
}

void BossBattleView::fightAction()
{
    mActionList.push_back(3);
    mActionList.push_back(1);
    mActionList.push_back(4);
    mActionList.push_back(2);
    mActionList.push_back(4);
    mActionList.push_back(1);
    mActionList.push_back(4);
    mActionList.push_back(1);
    
    
    this->playOneActionEnd();
}

CCFiniteTimeAction * BossBattleView::createSequece(unsigned int action_id)
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
            
            pAction = CCSequence::create(move1,move2,move3,CCCallFunc::create(this, callfunc_selector(BossBattleView::playAction)),NULL);
            
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
            
            pAction = CCSequence::create(scale1,scale2,CCCallFunc::create(this, callfunc_selector(BossBattleView::playAction)),NULL);
            
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
            pAction = CCSequence::create(fade1,CCDelayTime::create(ACTION_INTERVAL_TIME*3),CCCallFunc::create(this, callfunc_selector(BossBattleView::playAction)),NULL);
            
            break;
        }
        case 4:
        {
            CCScaleBy *scale1 = CCScaleBy::create(ACTION_INTERVAL_TIME, 1.2f);
            CCScaleBy *scale2 = CCScaleBy::create(ACTION_INTERVAL_TIME, 1 / 1.2f);
            
            pAction = CCSequence::create(scale1,scale2,CCCallFunc::create(this, callfunc_selector(BossBattleView::playOneActionEnd)),NULL);
            
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

void BossBattleView::playAction()
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
                if ( tAcitonID == 4 )
                {
                    CCSprite *pSprite = (CCSprite *)this->getChildByTag(TAG_PLAYER_SPRITE);
                    pSprite->runAction(pAction);
                }
                else
                {
                    CCSprite *pSprite = (CCSprite *)this->getChildByTag(TAG_MONSTER_SPRITE);
                    pSprite->runAction(pAction);
                }
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
        
        m_bIsWaitingForAction = false;
        
        this->removeFromParentAndCleanup(true);
        
        ((m_target)->*(m_pfnSelector))(this, NULL);
    }
}

void BossBattleView::playOneActionEnd()
{
    CCLabelTTF *label = (CCLabelTTF *)this->getChildByTag(TAG_LABEL_SUB_HP);
    if ( label )
    {
        label->setVisible(false);
    }
    
    if ( mActionList.empty() == false )
    {
        unsigned int tAcitonID = mActionList[mActionList.size()-1];
        

        if ( tAcitonID == 3 )
        {
            CCFiniteTimeAction *pAction = this->createSequece(tAcitonID);
            mActionList.pop_back();
            
            if(pAction)
            {
                CCLabelTTF *pLabel = (CCLabelTTF *)this->getChildByTag(TAG_LABEL_DES);
                pLabel->setColor(ccGREEN);
                pLabel->setString("你获得胜利!");
                pLabel->setVisible(true);
                pLabel->runAction(pAction);
            }
        }
        else {
            m_bIsWaitingForAction = true;
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
        
        m_bIsWaitingForAction = false;
        
        ((m_target)->*(m_pfnSelector))(this, NULL);
    }
}

bool BossBattleView::getIsInBattle()
{
    return m_bIsInBattle;
}

void BossBattleView::setIsInBattle(bool _b_state)
{
    m_bIsInBattle = _b_state;
}

bool BossBattleView::ccTouchBegan(CCTouch* touch, CCEvent *pEvent)
{
    if ( m_bIsWaitingForAction == false && !touch) return false;
    
    pBeginPoint = this->convertTouchToNodeSpace(touch);
        
    return true;
}

void BossBattleView::ccTouchMoved(CCTouch* touch, CCEvent *pEvent)
{
    
}

void BossBattleView::ccTouchEnded(CCTouch* touch, CCEvent *pEvent)
{
    if ( !touch ) return;
    CCPoint endPoint = this->convertTouchToNodeSpace(touch);
    
    CCFloat distance_ = ccpDistanceSQ(endPoint, pBeginPoint);
    
    if (distance_ > 2.0f)
    {
        //触发随机事件
        this->playAction();
    }
}

void BossBattleView::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
