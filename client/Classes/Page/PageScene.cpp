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
#include "LuckySprite.h"
#include "TaskDataManager.h"
#include "PlayerInfoBar.h"

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

    this->setTouchEnabled(true);
    
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
    
//    stTask *tTask = TaskDataManager::getShareInstance()->getTask(pPage->taskId);
//    
//    stTalk *tTalk = TaskDataManager::getShareInstance()->getTalk(tTask->npcTalkId);
    
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    LuckySprite* pSprite = LuckySprite::create(1);
    pSprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(pSprite, 0);
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1, TAG_MENU);
    
    CCMenuItemSprite *pBackItem = CCMenuItemSprite::create(LuckySprite::create(2), LuckySprite::create(3), LuckySprite::create(3), this, menu_selector(Page::menuBackCallback)); 
    pBackItem->setScale(0.5);
    pBackItem->setPosition(ccp(size.width - 30, size.height - 20));
    pMenu->addChild(pBackItem);
    
    m_tips = CCLabelTTF::create(m_pPage->state && m_pPage->end ? "End of Chapter" : "", "Arial", 28);
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
    
    CCMenuItemSprite *pAttackItem  = CCMenuItemSprite::create(LuckySprite::create(29), LuckySprite::create(30), LuckySprite::create(31), this, menu_selector(Page::menuAttackCallback));
    pAttackItem->setPosition(ccp(size.width - 50, 50));
    pMenu->addChild(pAttackItem, 0, TAG_ATTACK);
    
    //    CCMenuItemFont *pNextItem = CCMenuItemFont::create("Next", this, menu_selector(Page::menuNextCallback));
    //    pMenu->addChild(pNextItem, 0, TAG_NEXT);
    
    const stMonster* pMonster = DictDataManager::shareDictDataManager()->getMonsterImageId(m_pPage->taskId);
    if (pMonster) 
    {
        LuckySprite *tempSprite = LuckySprite::create(pMonster->imageId);
        tempSprite->setPosition(ccp(size.width/2, size.height/2 - 150));
        tempSprite->setScale(0.35f);
        this->addChild(tempSprite, 1);
        
        m_monster = CCLabelTTF::create(pMonster->name.c_str(), "Arial", 28);
        m_monster->setColor(ccBLACK);
        m_monster->setPosition(ccp(size.width/2, 50));
        this->addChild(m_monster, 1);
    }

	PlayerInfoBar* playerInfoBar = PlayerInfoBar::create();
	this->addChild(playerInfoBar);

//    adjustPageItem();
}

void Page::menuAttackCallback(CCObject* pSender)
{    
    showBattleView(pSender);

    m_pPage->state = 1;
//    m_state->setString(m_pPage->state ? "success": "");
    m_tips->setString(m_pPage->state && m_pPage->end ? "End of Chapter" : "");
    //    adjustPageItem();
}

void Page::showBattleView(CCObject *pSender)
{
    if ( MonsterBattleView::getIsInBattle() == false )
    {
        MonsterBattleView *pMonter = MonsterBattleView::create();
        pMonter->initLayer(m_pPage, this, callfuncND_selector(Page::fightCallback));
        CCDirector::sharedDirector()->getRunningScene()->addChild(pMonter, 0, TAG_BATTLE_LAYER);
    }
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
//        pNextItem->setEnabled(!m_pPage->end);
//    }
//}

bool Page::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent *pEvent)
{
    if ( !touch) return false;
    
    pBeginPoint = this->convertTouchToNodeSpace(touch);
    
    return true;
}

void Page::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent *pEvent)
{
    
}

void Page::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent *pEvent)
{
    if ( !touch ) return;
    CCPoint endPoint = this->convertTouchToNodeSpace(touch);
    
    CCFloat distance_ = ccpDistanceSQ(endPoint, pBeginPoint);
    
    if (distance_ > 2.0f)
    {
        //触发随机事件
        this->menuAttackCallback(NULL);
    }
}

void Page::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
