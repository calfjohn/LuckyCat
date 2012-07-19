//
//  PageMapScene.cpp
//  HelloWorld
//
//  Created by Cocos2d on 12-7-19.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "PageMapScene.h"

USING_NS_CC;

#define TAG_MENU 1000
#define TAG_NEXT 1001
#define TAG_ATTACK 1002

CCScene* PageMap::scene(int chapterId)
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);
        
        // 'layer' is an autorelease object
        PageMap *layer = PageMap::create();
        CC_BREAK_IF(! layer);
        
        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PageMap::init()
{
    CCLayer::init();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pSprite = CCSprite::create("Default.png");
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite, 0);
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1, TAG_MENU);
    
    CCMenuItemFont *pBackItem = CCMenuItemFont::create("返回", this, menu_selector(PageMap::menuBackCallback));
    pBackItem->setPosition(ccp(size.width - 30, 20));
    pMenu->addChild(pBackItem);

    return true;
}

void PageMap::menuBackCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}