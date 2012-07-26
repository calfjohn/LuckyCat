//
//  Cover.cpp
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "CoverScene.h"
#include "ChapterScene.h"
#include "LevelDataManager.h"
USING_NS_CC;

CCScene* Cover::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        Cover *layer = Cover::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Cover::init()
{
    CCTouchPageTurn::init();

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemImage *pDaggerItem  = CCMenuItemImage::create("image/Main/1.png", "image/Main/11.png", "image/Main/111.png", this, menu_selector(Cover::menuDaggerCallback));
    pDaggerItem->setPosition(ccp(size.width - 50, size.height - 80));
    
    CCMenuItemImage *pMagicItem = CCMenuItemImage::create("image/Main/2.png", "image/Main/22.png", "image/Main/222.png", this, menu_selector(Cover::menuMagicCallback));
    pMagicItem->setPosition(ccp(size.width - 80, size.height - 200));
    
    CCMenuItemImage *pBookItem = CCMenuItemImage::create("image/Main/3.png", "image/Main/33.png", "image/Main/333.png", this, menu_selector(Cover::menuBookCallback));
    pBookItem->setPosition(ccp(size.width/2 - 50, size.height/2 - 20));
    
    CCMenuItemFont *pCardItem = CCMenuItemFont::create("card", this, menu_selector(Cover::menuCardCallback));
    pCardItem->setPosition(ccp(size.width - 50, size.height/2 - 120));
    
    CCMenuItemFont *pOptionItem = CCMenuItemFont::create("option", this, menu_selector(Cover::menuOptionCallback));
    pOptionItem->setPosition(ccp(size.width - 50, 20));

    CCMenu* pMenu = CCMenu::create(pDaggerItem, pMagicItem, pBookItem, pCardItem, pOptionItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    CCSprite* pSprite = CCSprite::create("image/common/1.png");
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite, 0);
    
    this->setTouchEnabled(true);

    return true;
}

void Cover::menuDaggerCallback(CCObject* pSender)
{
}

void Cover::menuMagicCallback(CCObject* pSender)
{
}

void Cover::menuBookCallback(CCObject* pSender)
{
    CCScene *pScene = Chapter::scene();
    
    CCDirector::sharedDirector()->setDepthTest(true);
    CCTransitionPageTurn *pTp = CCTransitionPageTurn::create(TRANSITION_PAGE_INTERVAL_TIME, pScene, false);
    
    CCDirector::sharedDirector()->pushScene(pTp);
}

void Cover::menuCardCallback(CCObject* pSender)
{
}

void Cover::menuOptionCallback(CCObject* pSender)
{
    LevelDataManager::shareLevelDataManager()->reload();
}

void Cover::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

