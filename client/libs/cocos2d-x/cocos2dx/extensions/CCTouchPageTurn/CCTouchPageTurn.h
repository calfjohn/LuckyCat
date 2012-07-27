//
//  Chapter.h
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef __CCTouchPageTurn_SCENE_H__
#define __CCTouchPageTurn_SCENE_H__

#include "cocos2d.h"
#include "CCTouchPageTurn3D.h"

NS_CC_EXT_BEGIN

class CC_DLL CCTouchPageTurn : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(CCTouchPageTurn);
  
    /** override functions */
    // optional
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
    CCPoint                m_ptTouchBegan;
    CCPoint                m_ptTouchEnd;
    float                  m_fTime;
    CCTouchPageTurn3D *m_action;
};

NS_CC_EXT_END


#endif  // __CCTouchPageTurn_SCENE_H__