//
//  PageMapScene.h
//  HelloWorld
//
//  Created by Cocos2d on 12-7-19.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef _PageMapScene_h
#define _PageMapScene_h

#include "cocos2d.h"
#include "LevelDataManager.h"

class PageMap : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene(int chapterId);
    
    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(PageMap);
    
    void turnToChapter(int chapterId);
    
    virtual void onEnter();
    
    virtual void onExit();
    
protected:
    // a selector callback
    void menuBackCallback(CCObject* pSender);
    
    void menuPageCallback(CCObject* pSender);

    void callback(CCNode* sender, void* data);

    int m_nChapterId;
    
    cocos2d::CCSprite *m_pKnight;
};

#endif
