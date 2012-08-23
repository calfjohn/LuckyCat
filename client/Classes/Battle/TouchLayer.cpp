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
,m_bTouchAreaEnabled(false)
{
    m_TouchNodeList.clear();
}

TouchLayer::~TouchLayer()
{
    m_TouchNodeList.clear();
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
    
    if ( getIsTouchAreaEnabled() ) {
        CCPoint tPoint = this->convertTouchToNodeSpace(pTouch);
        if ( this->TouchAreaContainsPoint(tPoint) == false )
        {
            this->notificationTouchEvent(kLTouchEventOutsideTouchArea);
            
            return false;
        }
        else {
            this->notificationTouchEvent(kLTouchEventInsideTouchArea);
        }
    }
    else if ( getIsTouchForbidden() )
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

bool TouchLayer::registerTouchNode(cocos2d::CCNode * pNode)
{
    if ( pNode )
    {
        std::vector<cocos2d::CCNode *>::iterator _iter = m_TouchNodeList.begin();
        for (; _iter != m_TouchNodeList.end(); _iter++) {
            CCNode *pN = *_iter;
            if ( pN == pNode )
            {
                return false;
            }
        }
        m_TouchNodeList.push_back(pNode);
        return true;
    }
    return false;
}

bool TouchLayer::removeTouchNode(cocos2d::CCNode * pNode)
{
    if ( pNode )
    {
        std::vector<cocos2d::CCNode *>::iterator _iter = m_TouchNodeList.begin();
        for (; _iter != m_TouchNodeList.end(); _iter++) {
            CCNode *pN = *_iter;
            if ( pN == pNode )
            {
                m_TouchNodeList.erase(_iter);
                return true;
            }
        }
    }
    return false;
}

bool TouchLayer::TouchAreaContainsPoint(cocos2d::CCPoint _point)
{
    std::vector<cocos2d::CCNode *>::iterator _iter = m_TouchNodeList.begin();
    for (; _iter != m_TouchNodeList.end(); _iter++) {
        CCNode *pN = *_iter;
        if ( pN )
        {
            CCRect tRect = getRect(pN);
            
            if ( CCRect::CCRectContainsPoint(tRect, _point) )
            {
                return true;
            }
        }
    }
    return false;
}

cocos2d::CCRect TouchLayer::getRect(cocos2d::CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    
    if (pNode->isIgnoreAnchorPointForPosition() == false)
    {
        CCPoint tPoint = pNode->getAnchorPoint();
        
        rc.origin.x -= rc.size.width * tPoint.x;
        rc.origin.y -= rc.size.height * tPoint.y;
    }
    return rc;
}
