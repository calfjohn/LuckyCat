//
//  Cover.cpp
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "CoverScene.h"
#include "ChapterScene.h"

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
    CCLayer::init();

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemFont *pDaggerItem = CCMenuItemFont::create("Dagger", this, menu_selector(Cover::menuDaggerCallback));
    pDaggerItem->setPosition(ccp(size.width - 50, size.height - 20));
    
    CCMenuItemFont *pMagicItem = CCMenuItemFont::create("Crystal ball", this, menu_selector(Cover::menuMagicCallback));
    pMagicItem->setPosition(ccp(size.width - 80, size.height - 120));
    
    CCMenuItemFont *pBookItem = CCMenuItemFont::create("Bible", this, menu_selector(Cover::menuBookCallback));
    pBookItem->setPosition(ccp(size.width - 50, size.height/2 - 20));
    
    CCMenuItemFont *pCardItem = CCMenuItemFont::create("card", this, menu_selector(Cover::menuCardCallback));
    pCardItem->setPosition(ccp(size.width - 50, size.height/2 - 120));
    
    CCMenuItemFont *pOptionItem = CCMenuItemFont::create("option", this, menu_selector(Cover::menuOptionCallback));
    pOptionItem->setPosition(ccp(size.width - 50, 20));

    CCMenu* pMenu = CCMenu::create(pDaggerItem, pMagicItem, pBookItem, pCardItem, pOptionItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    CCSprite* pSprite = CCSprite::create("Default.png");
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite, 0);

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
    CCTransitionPageTurn *pTp = CCTransitionPageTurn::create(1.2f, pScene, false);
    
    CCDirector::sharedDirector()->pushScene(pTp);
}

void Cover::menuCardCallback(CCObject* pSender)
{
}

void Cover::menuOptionCallback(CCObject* pSender)
{
}

