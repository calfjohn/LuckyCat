//
//  Chapter.cpp
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "CCTouchPageTurn.h"

NS_CC_EXT_BEGIN

// on "init" you need to initialize your instance
bool CCTouchPageTurn::init()
{
    CCLayer::init();
    m_action = NULL;

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    int x,y;
    if( s.width > s.height)
    {
        x=16;
        y=12;
    }
    else
    {
        x=12;
        y=16;
    }
    
    m_action =  CCTouchPageTurn3D::create(ccg(x,y), 5);
    m_action->setUpdate(0);
    this->runAction(CCRepeatForever::actionWithAction(m_action));

    this->setTouchEnabled(true);

    return true;
}

bool CCTouchPageTurn::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
    
    CCPoint touchPoint = touch->locationInView();
    
    m_ptTouchBegan = m_ptTouchEnd = CCDirector::sharedDirector()->convertToGL(touchPoint);
      
    return true;
}

void CCTouchPageTurn::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
 
    CCPoint touchPoint = touch->locationInView();
    m_ptTouchEnd = CCDirector::sharedDirector()->convertToGL(touchPoint);   
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    m_fTime = (m_ptTouchBegan.x - m_ptTouchEnd.x) /80;
    CCLOG("%f", m_fTime);
    m_action->setUpdate(m_fTime);
}

void CCTouchPageTurn::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    
    m_action->setUpdate(0);
}

void CCTouchPageTurn::ccTouchCancelled(CCTouch *touch, CCEvent *event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
    ccTouchEnded(touch, event);
}

void CCTouchPageTurn::autoTurnPage()
{
    m_fTime = 0;
    this->setTouchEnabled(false);
    schedule(schedule_selector(CCTouchPageTurn::scheduleTimer), 0.1);
}

void CCTouchPageTurn::scheduleTimer(float dt)
{
    m_action->setUpdate(m_fTime);
    m_fTime += 0.1;
    if (m_fTime >= 1) 
    {
        unscheduleAllSelectors();
        removeFromParentAndCleanup(true);
    }
}

NS_CC_EXT_END

