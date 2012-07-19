//
//  Chapter.h
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef __CHPATER_SCENE_H__
#define __CHPATER_SCENE_H__

#include "cocos2d.h"

class Chapter : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuBackCallback(CCObject* pSender);

    void menuChapterCallback(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(Chapter);
};

#endif  // __Cover_SCENE_H__