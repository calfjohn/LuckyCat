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

void MonsterBattleView::onEnter()
{
    CCLayer::onEnter();
    
    pMonsterSprite = NULL;
    
}

void MonsterBattleView::initLayer(int monsterId, CCObject *target, SEL_CallFuncND pfnSelector)
{
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    //    cocos2d::CCLabelTTF *titleLabel = cocos2d::CCLabelTTF::create( "Monster Fight!", CCSizeMake(screanSize.width, 50),kCCVerticalTextAlignmentCenter,kCCVerticalTextAlignmentCenter,"Arial", 24); 
    //    titleLabel = CCLabelTTF::initWithString("Monster Fight!", "Arial", 50);
    
    CCLabelTTF *titleLabel = CCLabelTTF::create("Monster Fight!", CCSizeMake(screanSize.width, 50), kCCTextAlignmentCenter,"Arial", 30);
    //cellLabel->setPosition(ccp(cellSize.width , cellSize.height )); 
    titleLabel->setAnchorPoint(ccp(0.5,0.5));
    titleLabel->setPosition(CCPointMake(screanSize.width*0.5f, screanSize.height- 60));
    titleLabel->setColor(ccc3(255,55,0));
    this->addChild(titleLabel);
    
    string tempName;
    tempName = "image/monster/" + LevelDataManager::shareLevelDataManager()->ConvertToString(monsterId) + ".png";
    CCSprite *_pMonsterSprite = CCSprite::create(tempName.c_str());
    _pMonsterSprite->setPosition(CCPointMake(screanSize.width*0.5f, 200));
    _pMonsterSprite->setScaleY(5);
    _pMonsterSprite->setScaleX(2.6);
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
    
    fightAction();
}

void MonsterBattleView::fightAction()
{
    mActionList.push_back(3);
    mActionList.push_back(1);
    mActionList.push_back(2);
    mActionList.push_back(1);
    
    
    CCDelayTime *pDelay1 = CCDelayTime::create(TRANSITION_PAGE_INTERVAL_TIME);
    CCFiniteTimeAction *pAction = CCSequence::create(pDelay1,CCCallFunc::create(this, callfunc_selector(MonsterBattleView::playAction)),NULL);
    
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
            
        }
        case 3:
        {
            CCFadeIn *fade1 = CCFadeIn::create(ACTION_INTERVAL_TIME*3);
            pAction = CCSequence::create(fade1,CCCallFunc::create(this, callfunc_selector(MonsterBattleView::playAction)),NULL);
            
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
        
        
        ((m_target)->*(m_pfnSelector))(this, NULL);
    }
}



