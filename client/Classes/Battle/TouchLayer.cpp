//
//  TouchLayer.cpp
//  LuckyCat
//
//  Created by XiaoZhong Zhu on 12-8-23.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "TouchLayer.h"

USING_NS_CC;

TouchLayer::TouchLayer():m_bTouchForbidden(false)
{
    
}

TouchLayer::~TouchLayer()
{
    
}

bool TouchLayer::init()
{
    return CCLayer::init();
}

void TouchLayer::onEnter()
{
    CCLayer::onEnter();
    
    this->setTouchEnabled(true);
}

void TouchLayer::onExit()
{
    CCLayer::onExit();
}

bool TouchLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if ( !pTouch ) return false;
    
    if ( getIsTouchForbidden() )
    {
        pBeginPoint = CCPointZero;
        return false;
    }
    
    pBeginPoint = this->convertTouchToNodeSpace(pTouch);
    
    return true;

}

void TouchLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void TouchLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if ( !pTouch ) return;
    
    if ( pBeginPoint.x != 0 && pBeginPoint.y != 0 )
    {
        this->notificationTouchEvent(kLTouchEventSingleClick);
    }
    pBeginPoint = CCPointZero;
}

void TouchLayer::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority , true);
}
