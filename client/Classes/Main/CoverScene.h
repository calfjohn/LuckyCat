//
//  Cover.h
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef __Cover_SCENE_H__
#define __Cover_SCENE_H__

#include "cocos2d.h"

class Cover : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuDaggerCallback(CCObject* pSender);
    void menuMagicCallback(CCObject* pSender);
    void menuBookCallback(CCObject* pSender);
    void menuCardCallback(CCObject* pSender);
    void menuOptionCallback(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(Cover);
};

#endif  // __Cover_SCENE_H__