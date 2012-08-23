//
//  PageMapScene.cpp
//  HelloWorld
//
//  Created by Cocos2d on 12-7-19.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "PageMapScene.h"
#include "PageScene.h"
#include "LuckySprite.h"

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
        
        layer->turnToChapter(chapterId);
    } while (0);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PageMap::init()
{
    CCLayer::init();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    LuckySprite* pSprite = LuckySprite::create(1);
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite, 0);
    
    LuckySprite* pSprite1 = LuckySprite::create(22);
    pSprite1->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite1, 0);    
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pMenu, 1, TAG_MENU);
    
    m_pKnight = LuckySprite::create(26);
    this->addChild(m_pKnight, 1);
    
    return true;
}

void PageMap::menuBackCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void PageMap::onEnter()
{
    CCLayer::onEnter();
    
    const stChapter *pChapter = LevelDataManager::shareLevelDataManager()->getChapter(m_nChapterId);
    const stPage * pPage = LevelDataManager::shareLevelDataManager()->getNewPage(m_nChapterId);
    if (!pChapter)
    {
        return;
    }

    bool bEnable = true;
    vector<stPage>::const_iterator iterTemp;
    CCMenuItemImage *pPageItem = NULL;
    for (iterTemp = pChapter->listPage.begin();
         iterTemp != pChapter->listPage.end();
         iterTemp++) 
    {
        pPageItem = (CCMenuItemImage *)getChildByTag(TAG_MENU)->getChildByTag((*iterTemp).id);
        if (pPage && (*iterTemp).id > pPage->id) 
        {
            bEnable = false;
        }
        pPageItem->setEnabled(bEnable);
    }
    
    if (pPage)
    {
        pPageItem = (CCMenuItemImage *)getChildByTag(TAG_MENU)->getChildByTag(pPage->id);
    }
    else
    {
        pPageItem = (CCMenuItemImage *)getChildByTag(TAG_MENU)->getChildByTag(pChapter->listPage.front().id);
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    m_pKnight->setPosition(ccp(pPageItem->getPosition().x + size.width/2 + 20, pPageItem->getPosition().y + size.height/2 + 20));
}

void PageMap::onExit()
{
    CCLayer::onExit();
}

void PageMap::turnToChapter(int chapterId)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    const stChapter *pChapter = LevelDataManager::shareLevelDataManager()->getChapter(chapterId);
    if (!pChapter)
    {
        return;
    }
    m_nChapterId = chapterId;
    
    CCLabelTTF *pTitleLabel = CCLabelTTF::create(pChapter->name.c_str(), "Arial", 28);
    pTitleLabel->setPosition(ccp(size.width/2, size.height - 20));
    this->addChild(pTitleLabel, 1);

    CCMenuItemSprite *pPageItem;
    vector<stPage>::const_iterator iterTemp;
    CCMenu *pMenu = (CCMenu *)getChildByTag(TAG_MENU);
    for (iterTemp = pChapter->listPage.begin();
         iterTemp != pChapter->listPage.end();
         iterTemp++) 
    {
        pPageItem = CCMenuItemSprite::create(LuckySprite::create(23), LuckySprite::create(24), LuckySprite::create(25), this, menu_selector(PageMap::menuPageCallback));
        pMenu->addChild(pPageItem, 0, (*iterTemp).id);
    }
    pMenu->alignItemsVerticallyWithPadding(20);
    
    CCMenuItemSprite *pBackItem = CCMenuItemSprite::create(LuckySprite::create(2), LuckySprite::create(3), LuckySprite::create(3), this, menu_selector(PageMap::menuBackCallback));
    pBackItem->setScale(0.5);
    pBackItem->setPosition(ccp(size.width/2 - 30, size.height/2 - 20));
    pMenu->addChild(pBackItem);
}

void PageMap::menuPageCallback(CCObject* pSender)
{
    CCNode *pNode = (CCNode *)pSender;
    const stPage *pPage = LevelDataManager::shareLevelDataManager()->getPage(m_nChapterId, pNode->getTag());
    if (!pPage) 
    {
        return;
    }
    
    m_pKnight->stopAllActions();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPoint postion = pNode->getPosition();
    m_pKnight->runAction(CCSequence::create(
                                CCMoveTo::create(0.5, ccp(postion.x + size.width/2 + 20, postion.y + size.height/2 + 20)), 
                                CCCallFuncND::create(this, callfuncND_selector(PageMap::callback), (void *)pPage),
                                NULL));
}
                                             
void PageMap::callback(CCNode* sender, void* data)
{
    const stPage *pPage = (stPage *)data;
    
    CCScene *pScene = Page::scene(m_nChapterId, pPage);
    CCTransitionPageTurn *pTp = CCTransitionPageTurn::create(TRANSITION_PAGE_INTERVAL_TIME, pScene, false);
    CCDirector::sharedDirector()->replaceScene(pTp);
}

                                             
                                             
