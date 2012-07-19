//
//  Chapter.cpp
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "ChapterScene.h"
#include "PageScene.h"
#include "LevelDataManager.h"

USING_NS_CC;

#define TAG_MENU 1000

CCScene* Chapter::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        Chapter *layer = Chapter::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Chapter::init()
{
    CCLayer::init();

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF *pTitleLabel = CCLabelTTF::create(LevelDataManager::shareLevelDataManager()->m_stBible.name.c_str(), "Arial", 28);
    pTitleLabel->setPosition(ccp(size.width/2, size.height - 20));
    this->addChild(pTitleLabel, 1);
    
    CCSprite* pSprite = CCSprite::create("Default.png");
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite, 0);
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pMenu, 1, TAG_MENU);
    
    bool bEnable = true;
    CCMenuItemFont *pChapterItem;
    vector<stChapter>::iterator iterTemp;
    for (iterTemp = LevelDataManager::shareLevelDataManager()->m_stBible.listChapter.begin();
         iterTemp != LevelDataManager::shareLevelDataManager()->m_stBible.listChapter.end();
         iterTemp++) 
    {
        pChapterItem = CCMenuItemFont::create((*iterTemp).name.c_str(), this, menu_selector(Chapter::menuChapterCallback));
        pChapterItem->setEnabled(bEnable);
        pMenu->addChild(pChapterItem, 0, (*iterTemp).id);
        bEnable = LevelDataManager::shareLevelDataManager()->isChapterEnd((*iterTemp).id);
    }
    
    pMenu->alignItemsVerticallyWithPadding(20);
    
    CCMenuItemFont *pBackItem = CCMenuItemFont::create("返回", this, menu_selector(Chapter::menuBackCallback));
    pBackItem->setPosition(ccp(size.width/2 - 30,-size.height/2 + 20));
    pMenu->addChild(pBackItem);
    
    return true;
}

void Chapter::menuBackCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void Chapter::menuChapterCallback(CCObject* pSender)
{
    CCNode *pNode = (CCNode *)pSender;
    
    stPage *pPage = LevelDataManager::shareLevelDataManager()->getNewPage(pNode->getTag());
    if (!pPage) 
    {
        return;
    }
    
    CCScene *pScene = Page::scene(pNode->getTag(), pPage);
    CCDirector::sharedDirector()->pushScene(pScene);
}

void Chapter::onEnter()
{
    CCLayer::onEnter();

    bool bEnable = true;
    vector<stChapter>::iterator iterTemp;
    for (iterTemp = LevelDataManager::shareLevelDataManager()->m_stBible.listChapter.begin();
         iterTemp != LevelDataManager::shareLevelDataManager()->m_stBible.listChapter.end();
         iterTemp++) 
    {
        CCMenuItemFont *pAttackItem = (CCMenuItemFont *)getChildByTag(TAG_MENU)->getChildByTag((*iterTemp).id);
        pAttackItem->setEnabled(bEnable);
        bEnable = LevelDataManager::shareLevelDataManager()->isChapterEnd((*iterTemp).id);
    }
}

void Chapter::onExit()
{
    CCLayer::onExit();
}
