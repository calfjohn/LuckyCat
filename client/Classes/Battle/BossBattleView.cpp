//
//  BossBattleView.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "BossBattleView.h"
#include "BattleDefine.h"

static bool m_bIsInBattle = false;

void BossBattleView::onEnter()
{
    CCLayer::onEnter();
    
    pMonsterSprite = NULL;
    
}

void BossBattleView::initLayer(int monsterId, CCObject *target, SEL_CallFuncND pfnSelector)
{
    mBossList.clear();
    
    GRole *p_Monster = new GRole();
    p_Monster->roleID = monsterId;
    p_Monster->curHP = 100;
    p_Monster->maxHp = 100;
    mBossList.push_back(p_Monster);
    
    
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    setIsInBattle(true);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    //    cocos2d::CCLabelTTF *titleLabel = cocos2d::CCLabelTTF::create( "Monster Fight!", CCSizeMake(screanSize.width, 50),kCCVerticalTextAlignmentCenter,kCCVerticalTextAlignmentCenter,"Arial", 24); 
    //    titleLabel = CCLabelTTF::initWithString("Monster Fight!", "Arial", 50);
    
    CCLabelTTF *titleLabel = CCLabelTTF::create("Lord Voldemort", CCSizeMake(screanSize.width, 50), kCCTextAlignmentCenter,"Arial", 30);
    //cellLabel->setPosition(ccp(cellSize.width , cellSize.height )); 
    titleLabel->setAnchorPoint(ccp(0.5,0.5));
    titleLabel->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height- 30));
    titleLabel->setColor(ccc3(255,55,0));
    this->addChild(titleLabel);
    
    CCSprite *_pMonsterSprite = CCSprite::create("bottom_1_7_1.png");
    _pMonsterSprite->setPosition(CCPointMake(screanSize.width*0.5f, 240));
//    _pMonsterSprite->setScaleY(5);
//    _pMonsterSprite->setScaleX(2.6);
    this->addChild(_pMonsterSprite);
    _pMonsterSprite->setTag(TAG_MONSTER_SPRITE);
    
    CCLabelTTF *dscLabel = CCLabelTTF::create("", CCSizeMake(screanSize.width, 50), kCCTextAlignmentCenter,"Arial", 30);
    //cellLabel->setPosition(ccp(cellSize.width , cellSize.height )); 
    dscLabel->setAnchorPoint(ccp(0.5,0.5));
    dscLabel->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.82f));
    dscLabel->setColor(ccc3(255,55,0));
    this->addChild(dscLabel);
    dscLabel->setTag(TAG_LABEL_DES);
    
    dscLabel->setVisible(false);
    
    
    CCProgressTimer *pProgressBoss = CCProgressTimer::create(CCSprite::create("extensions/sliderProgress.png"));
    pProgressBoss->setType(kCCProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    pProgressBoss->setMidpoint(ccp(0.0f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    //pProgressBoss->setBarChangeRate(ccp(1, 1));
    pProgressBoss->setPercentage(66);
    pProgressBoss->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height- 50));
    this->addChild(pProgressBoss,3);
    pProgressBoss->setTag(TAG_MONSTER_PLINE);
    
    CCSprite *_pPlayerSprite = CCSprite::create("bottom_1_7_1.png");
    _pPlayerSprite->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.20f));
//    _pPlayerSprite->setScaleY(2);
//    _pPlayerSprite->setScaleX(1.4);
    this->addChild(_pPlayerSprite);
    _pPlayerSprite->setTag(TAG_PLAYER_SPRITE);
    
    CCProgressTimer *pProgressPlayer = CCProgressTimer::create(CCSprite::create("extensions/sliderProgress.png"));
    pProgressPlayer->setType(kCCProgressTimerTypeBar);
    //    Setup for a bar starting from the bottom since the midpoint is 0 for the y
    //pProgressBoss->setMidpoint(ccp(0.5f, 0.5f));
    //    Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    //pProgressBoss->setBarChangeRate(ccp(1, 1));
    pProgressPlayer->setPercentage(100);
    pProgressPlayer->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height*0.05f));
    this->addChild(pProgressPlayer,3);
    pProgressPlayer->setTag(TAG_PLAYER_PLINE);
    
    
    fightAction();
}

void BossBattleView::fightAction()
{
    mActionList.push_back(3);
    mActionList.push_back(1);
    mActionList.push_back(2);
    mActionList.push_back(1);
    
    
    this->playAction();
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
            
            break;
        }
        case 2:
        {
            CCScaleBy *scale1 = CCScaleBy::create(ACTION_INTERVAL_TIME, 1.2f);
            CCScaleBy *scale2 = CCScaleBy::create(ACTION_INTERVAL_TIME, 1 / 1.2f);
            
            pAction = CCSequence::create(scale1,scale2,CCCallFunc::create(this, callfunc_selector(BossBattleView::playAction)),NULL);
            
        }
        case 3:
        {
            CCFadeIn *fade1 = CCFadeIn::create(ACTION_INTERVAL_TIME);
            pAction = CCSequence::create(fade1,CCCallFunc::create(this, callfunc_selector(BossBattleView::playAction)),NULL);
            
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

bool BossBattleView::getIsInBattle()
{
    return m_bIsInBattle;
}

void BossBattleView::setIsInBattle(bool _b_state)
{
    m_bIsInBattle = _b_state;
}
