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
#include "LuckySprite.h"
#include "NetManager.h"
#include "PageScene.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

#define TAG_BUTTON_BOOK 1

USING_NS_CC;
USING_NS_CC_EXT;

Cover *Cover::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("Cover", CoverLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/cover.ccbi", pOwner);
    
    Cover *pCover = static_cast<Cover *>(pNode);
    return pCover;
}

cocos2d::SEL_MenuHandler Cover::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", Cover::onMenuItemClicked);
    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler Cover::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", Cover::onCCControlButtonClicked );
    return NULL;
}
bool Cover::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode)
{
    return false;
}

void Cover::onMenuItemClicked(cocos2d::CCObject *pTarget)
{
    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pTarget);
    printf("tag %d\n",p->getTag());
}

void Cover::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pSender);
    printf("tag %d\n",p->getTag());
    
    unsigned int tag = p->getTag();
    
    if ( tag == TAG_BUTTON_BOOK )
    {
        this->menuBookCallback(NULL);
    }
}

CCScene* Cover::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        Cover *layer = Cover::create(scene);
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

    /*
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemSprite *pDaggerItem = CCMenuItemSprite::create(LuckySprite::create(4), LuckySprite::create(4, 1.1), LuckySprite::create(6), this, menu_selector(Cover::menuDaggerCallback));
    pDaggerItem->setPosition(ccp(size.width - 50, size.height - 80));
    
    CCMenuItemSprite *pMagicItem = CCMenuItemSprite::create(LuckySprite::create(7), LuckySprite::create(7, 1.1), LuckySprite::create(9), this, menu_selector(Cover::menuMagicCallback));
    pMagicItem->setPosition(ccp(size.width - 80, size.height - 200));
    
    CCMenuItemSprite *pBookItem = CCMenuItemSprite::create(LuckySprite::create(10), LuckySprite::create(10, 1.1), LuckySprite::create(12), this, menu_selector(Cover::menuBookCallback));
    pBookItem->setPosition(ccp(size.width/2 - 50, size.height/2 - 20));
    
    CCMenuItemFont *pCardItem = CCMenuItemFont::create("card", this, menu_selector(Cover::menuCardCallback));
    pCardItem->setPosition(ccp(size.width - 50, size.height/2 - 120));
    
    CCMenuItemFont *pOptionItem = CCMenuItemFont::create("option", this, menu_selector(Cover::menuOptionCallback));
    pOptionItem->setPosition(ccp(size.width - 50, 20));

    CCMenu* pMenu = CCMenu::create(pDaggerItem, pMagicItem, pBookItem, pCardItem, pOptionItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    LuckySprite* pSprite = LuckySprite::create(1);
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite, 0);
    
    this->setTouchEnabled(true);
    
    //this->addChild(Page::create(this),99);
     */

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

