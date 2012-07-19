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

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pSprite = CCSprite::create("Default.png");
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite, 0);
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1, TAG_MENU);
    
    CCMenuItemFont *pBackItem = CCMenuItemFont::create("返回", this, menu_selector(Page::menuBackCallback));
    pBackItem->setPosition(ccp(size.width - 30, 20));
    pMenu->addChild(pBackItem);
    
    m_title = CCLabelTTF::create("小节", "Arial", 28);
    m_title->setPosition(ccp(size.width/2, size.height/2 + 50));
    this->addChild(m_title, 1);

    m_content = CCLabelTTF::create("内容", "Arial", 28);
    m_content->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(m_content, 1);

    m_monster = CCLabelTTF::create("怪物", "Arial", 28);
    m_monster->setPosition(ccp(size.width/2, size.height/2 - 50));
    this->addChild(m_monster, 1);
    
    m_state = CCLabelTTF::create("状态", "Arial", 28);
    m_state->setPosition(ccp(size.width/2, size.height/2 - 80));
    this->addChild(m_state, 1);
    
    CCMenuItemFont *pAttackItem = CCMenuItemFont::create("Attack", this, menu_selector(Page::menuAttackCallback));
    pMenu->addChild(pAttackItem, 0, TAG_ATTACK);
    
    CCMenuItemFont *pNextItem = CCMenuItemFont::create("Next", this, menu_selector(Page::menuNextCallback));
    pMenu->addChild(pNextItem, 0, TAG_NEXT);
    
    m_pPage = NULL;
    return true;
}

void Page::menuBackCallback(CCObject* pSender)
{
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    //CCTransitionPageTurn *pTp = CCTransitionPageTurn::create(TRANSITION_PAGE_INTERVAL_TIME, pScene, false);
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
    
    m_title->setString(pPage->name.c_str());
    m_content->setString(pPage->content.c_str());
    m_monster->setString(LevelDataManager::shareLevelDataManager()->ConvertToString(pPage->monsterId).c_str());
    m_monster->setString(LevelDataManager::shareLevelDataManager()->ConvertToString(pPage->monsterId).c_str());
    m_state->setString(m_pPage->state ? "success": "");
    
    adjustPageItem();
}

void Page::menuNextCallback(CCObject* pSender)
{   
    stPage *pPage = LevelDataManager::shareLevelDataManager()->getNewPage(m_nChapterId);
    if (m_pPage == pPage) 
    {
        return;
    }
    
    turnToPage(m_nChapterId, pPage);
}

void Page::menuAttackCallback(CCObject* pSender)
{
    this->runAction(CCSequence::create(CCMoveBy::create(0.1, ccp(50, 0)), 
                                        CCMoveBy::create(0.1, ccp(-100, 0)), 
                                        CCMoveBy::create(0.1, ccp(100, 0)), 
                                        CCMoveBy::create(0.1, ccp(-50, 0)), 
                                        CCCallFunc::create(this, callfunc_selector(Page::showBattleView)),
                                        NULL));                                        
    m_pPage->state = 1;
    m_state->setString(m_pPage->state ? "success": "");

    adjustPageItem();
}

void Page::showBattleView(CCObject *pSender)
{
//    CCScene *pScene = CCScene::create();
//    CCTransitionPageTurn *pTp = CCTransitionPageTurn::create(TRANSITION_PAGE_INTERVAL_TIME, pScene, false);
//    
//    CCDirector::sharedDirector()->pushScene(pTp);
//    
//    CCSize s = CCDirector::sharedDirector()->getWinSize();
//    int x,y;
//    if( s.width > s.height)
//    {
//        x=16;
//        y=12;
//    }
//    else
//    {
//        x=12;
//        y=16;
//    }
//    
//    CCActionInterval *action  = pTp->actionWithSize(ccg(x,y));
    
    MonsterBattleView *pMonter = MonsterBattleView::create();
    pMonter->initLayer();
    
    CCDirector::sharedDirector()->getRunningScene()->addChild(pMonter);
    
    pMonter->setTag(TAG_BATTLE_LAYER);
    
    //pMonter->runAction(action);
    //this->addChild(pMonter);
    
}

void Page::adjustPageItem()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemFont *pAttackItem = (CCMenuItemFont *)getChildByTag(TAG_MENU)->getChildByTag(TAG_ATTACK);
    CCMenuItemFont *pNextItem = (CCMenuItemFont *)getChildByTag(TAG_MENU)->getChildByTag(TAG_NEXT);
    
    if (m_pPage->state != 1) 
    {
        pNextItem->setPosition(ccp(size.width - 50, 50));
        pAttackItem->setPosition(ccp(size.width - 50, 50));
        
        pNextItem->setEnabled(true);
        pNextItem->setVisible(false);
        pAttackItem->setVisible(true);
    }
    else 
    {
        pNextItem->setEnabled(!LevelDataManager::shareLevelDataManager()->isChapterEnd(m_nChapterId));

        pNextItem->setPosition(ccp(size.width - 50, 50));
        pAttackItem->setPosition(ccp(size.width - 150, 50));
        
        pNextItem->setVisible(true);
        pAttackItem->setVisible(true);
    }
}
