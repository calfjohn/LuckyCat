//
//  TouchLayer.h
//  LuckyCat
//
//  Created by XiaoZhong Zhu on 12-8-23.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef LuckyCat_TouchLayer_h
#define LuckyCat_TouchLayer_h

#include "cocos2d.h"

enum LTouchEvent {
    kLTouchEventSingleClick             =   1,          //Single click
    kLTouchEventDoubleClick             =   2,          //Double click
    kLTouchEventSliding                 =   3,          //Finger sliding
};

class TouchLayer : public cocos2d::CCLayer 
{
public:
    TouchLayer();
    virtual ~TouchLayer();
    
    bool init();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher(void);
    
    /*
     *@brief This method is notification touch event is happen. you can override it to receive touch event;
     */
    virtual void notificationTouchEvent(LTouchEvent tLTouchEvent) = 0;
    
    /*
     *@brief if m_bTouchForbidden is false, It cannot receive touch event.
     */
    CC_SYNTHESIZE(bool, m_bTouchForbidden, IsTouchForbidden);
private:
    cocos2d::CCPoint pBeginPoint;

};

#endif
