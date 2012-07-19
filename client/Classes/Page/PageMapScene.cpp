//
//  PageMapScene.cpp
//  HelloWorld
//
//  Created by Cocos2d on 12-7-19.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "PageMapScene.h"
#include "PageScene.h"

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
    
    CCSprite* pSprite = CCSprite::create("image/common/1.png");
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite, 0);
    
    CCSprite* pSprite1 = CCSprite::create("image/Page/1.png");
    pSprite1->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite1, 0);    
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pMenu, 1, TAG_MENU);
    
    m_pKnight = CCSprite::create("image/Page/3.png");
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
    
    stChapter *pChapter = LevelDataManager::shareLevelDataManager()->getChapter(m_nChapterId);
    stPage * pPage = LevelDataManager::shareLevelDataManager()->getNewPage(m_nChapterId);
    if (!pChapter)
    {
        return;
    }

    bool bEnable = true;
    vector<stPage>::iterator iterTemp;
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

    stChapter *pChapter = LevelDataManager::shareLevelDataManager()->getChapter(chapterId);
    if (!pChapter)
    {
        return;
    }
    m_nChapterId = chapterId;
    
    CCLabelTTF *pTitleLabel = CCLabelTTF::create(pChapter->name.c_str(), "Arial", 28);
    pTitleLabel->setPosition(ccp(size.width/2, size.height - 20));
    this->addChild(pTitleLabel, 1);

    CCMenuItemImage *pPageItem;
    vector<stPage>::iterator iterTemp;
    CCMenu *pMenu = (CCMenu *)getChildByTag(TAG_MENU);
    for (iterTemp = pChapter->listPage.begin();
         iterTemp != pChapter->listPage.end();
         iterTemp++) 
    {
        pPageItem = CCMenuItemImage::create("image/Page/2.png", "image/Page/22.png", "image/Page/222.png", this, menu_selector(PageMap::menuPageCallback));
        pMenu->addChild(pPageItem, 0, (*iterTemp).id);
    }
    pMenu->alignItemsVerticallyWithPadding(20);
    
    CCMenuItemFont *pBackItem = CCMenuItemFont::create("返回", this, menu_selector(PageMap::menuBackCallback));
    pBackItem->setPosition(ccp(size.width/2 - 30,-size.height/2 + 20));
    pMenu->addChild(pBackItem);
}

void PageMap::menuPageCallback(CCObject* pSender)
{
    CCNode *pNode = (CCNode *)pSender;
    stPage *pPage = LevelDataManager::shareLevelDataManager()->getNewPage(pNode->getTag());
    if (!pPage) 
    {
        return;
    }
    
    m_pKnight->stopAllActions();
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPoint postion = pNode->getPosition();
    m_pKnight->runAction(CCSequence::actions(
                                CCMoveTo::actionWithDuration(0.5, ccp(postion.x + size.width/2 + 20, postion.y + size.height/2 + 20)), 
                                CCCallFuncND::create(this, callfuncND_selector(PageMap::callback2), pPage),
                                NULL));
}
                                             
void PageMap::callback2(CCNode* sender, void* data)
{
    stPage *pPage = (stPage *)data;
    
    CCScene *pScene = Page::scene(m_nChapterId, pPage);
    CCDirector::sharedDirector()->pushScene(pScene);
}

                                             
                                             
