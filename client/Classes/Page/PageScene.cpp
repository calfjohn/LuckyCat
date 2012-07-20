//
//  Chapter.cpp
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "PageScene.h"
#include "MonsterBattleView.h"
#include "BossBattleView.h"
#include "BattleDefine.h"
#include "DictDataManager.h"

USING_NS_CC;

#define TAG_MENU 1000
#define TAG_NEXT 1001
#define TAG_ATTACK 1002

CCScene* Page::scene(int chapterId, stPage *pPage)
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        Page *layer = Page::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
        
        layer->turnToPage(chapterId, pPage);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Page::init()
{
    CCLayer::init();

    m_pPage = NULL;
    return true;
}

void Page::menuBackCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void Page::turnToPage(int chapterId, stPage *pPage)
{
    if (!pPage) 
    {
        return;
    }
    m_nChapterId = chapterId;
    m_pPage = pPage;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pSprite = CCSprite::create("image/common/1.png");
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite, 0);
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1, TAG_MENU);
    
    CCMenuItemImage *pBackItem = CCMenuItemImage::create("image/common/2.png", "image/common/22.png", "image/common/22.png", this, menu_selector(Page::menuBackCallback)); 
    pBackItem->setScale(0.5);
    pBackItem->setPosition(ccp(size.width - 30, size.height - 20));
    pMenu->addChild(pBackItem);
    
    m_tips = CCLabelTTF::create(m_pPage->state && LevelDataManager::shareLevelDataManager()->isLastPageOfChapter(m_nChapterId, m_pPage->id) ? "End of Chapter" : "", "Arial", 28);
    m_tips->setPosition(ccp(size.width/2, size.height/2 + 150));
    m_tips->setColor(ccRED);
    this->addChild(m_tips, 1);
    
    m_title = CCLabelTTF::create(pPage->name.c_str(), "Arial", 28);
    m_title->setPosition(ccp(size.width/2, size.height - 100));
    m_title->setColor(ccBLACK);
    this->addChild(m_title, 1);
    
    m_content = CCLabelTTF::create(pPage->content.c_str(), "Arial", 28);
    m_content->setPosition(ccp(size.width/2, size.height/2));
    m_content->setColor(ccBLACK);
    this->addChild(m_content, 1);
    
//    m_state = CCLabelTTF::create(m_pPage->state ? "success": "", "Arial", 28);
//    m_state->setPosition(ccp(size.width/2, 50));
//    m_state->setColor(ccBLACK);
//    this->addChild(m_state, 1);
    
    CCMenuItemImage *pAttackItem  = CCMenuItemImage::create("image/Page/4.png", "image/Page/44.png", "image/Page/444.png", this, menu_selector(Page::menuAttackCallback));
    pAttackItem->setPosition(ccp(size.width - 50, 50));
    pMenu->addChild(pAttackItem, 0, TAG_ATTACK);
    
    //    CCMenuItemFont *pNextItem = CCMenuItemFont::create("Next", this, menu_selector(Page::menuNextCallback));
    //    pMenu->addChild(pNextItem, 0, TAG_NEXT);
    
    const stMonster* pMonster = DictDataManager::shareDictDataManager()->getMonsterImageId(pPage->monsterId);
    if (pMonster) 
    {
        string tempName = "image/monster/" + LevelDataManager::shareLevelDataManager()->ConvertToString(pMonster->image_id) + ".png";
        CCSprite *tempSprite = CCSprite::create(tempName.c_str());
        tempSprite->setPosition(ccp(size.width/2, size.height/2 - 150));
        this->addChild(tempSprite, 1);
        
        m_monster = CCLabelTTF::create(pMonster->name.c_str(), "Arial", 28);
        m_monster->setColor(ccBLACK);
        m_monster->setPosition(ccp(size.width/2, 50));
        this->addChild(m_monster, 1);
    }

//    adjustPageItem();
}

void Page::menuAttackCallback(CCObject* pSender)
{    
    showBattleView(pSender);

    m_pPage->state = 1;
//    m_state->setString(m_pPage->state ? "success": "");
    m_tips->setString(m_pPage->state && LevelDataManager::shareLevelDataManager()->isLastPageOfChapter(m_nChapterId, m_pPage->id) ? "End of Chapter" : "");
    //    adjustPageItem();
}

void Page::showBattleView(CCObject *pSender)
{
    if ( MonsterBattleView::getIsInBattle() == false )
    {
        MonsterBattleView *pMonter = MonsterBattleView::create();
        pMonter->initLayer(m_pPage->monsterId, this, callfuncND_selector(Page::fightCallback));
        CCDirector::sharedDirector()->getRunningScene()->addChild(pMonter, 0, TAG_BATTLE_LAYER);
    }
    
//    if ( BossBattleView::getIsInBattle() == false )
//    {
//        BossBattleView *pBoss = BossBattleView::create();
//        pBoss->initLayer(m_pPage->monsterId, this, callfuncND_selector(Page::fightCallback));
//        CCDirector::sharedDirector()->getRunningScene()->addChild(pBoss, 0, TAG_BATTLE_LAYER);
//    }
}

void Page::fightCallback(CCNode* pNode, void* data)
{   
    stPage *pPage = LevelDataManager::shareLevelDataManager()->getNewPage(m_nChapterId);
    if (m_pPage == pPage) 
    {
        return;
    }
    
   // turnToPage(m_nChapterId, pPage);
    CCScene *pScene = Page::scene(m_nChapterId, pPage);
    CCTransitionPageTurn *pTp = CCTransitionPageTurn::create(TRANSITION_PAGE_INTERVAL_TIME, pScene, false);
    CCDirector::sharedDirector()->replaceScene(pTp);
}

//void Page::adjustPageItem()
//{
//    CCSize size = CCDirector::sharedDirector()->getWinSize();
//
//    CCMenuItemImage *pAttackItem = (CCMenuItemImage *)getChildByTag(TAG_MENU)->getChildByTag(TAG_ATTACK);
//    CCMenuItemFont *pNextItem = (CCMenuItemFont *)getChildByTag(TAG_MENU)->getChildByTag(TAG_NEXT);
//    
//    if (m_pPage->state != 1) 
//    {
//        pNextItem->setPosition(ccp(size.width - 50, 50));
//        pAttackItem->setPosition(ccp(size.width - 50, 50));
//        
//        pNextItem->setEnabled(true);
//        pNextItem->setVisible(false);
//    }
//    else 
//    {
//        pNextItem->setPosition(ccp(size.width - 50, 50));
//        pAttackItem->setPosition(ccp(size.width - 150, 50));
//        
//        pNextItem->setVisible(true);
//        pNextItem->setEnabled(!LevelDataManager::shareLevelDataManager()->isLastPageOfChapter(m_nChapterId, m_pPage->id));
//    }
//}
