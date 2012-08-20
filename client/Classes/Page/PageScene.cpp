//
//  Chapter.cpp
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "PageScene.h"
#include "BattleDefine.h"
#include "DictDataManager.h"
#include "LuckySprite.h"
#include "EventDataManager.h"
#include "PlayerInfoView.h"
#include "NetManager.h"
#include "EventListView.h"
#include "ChapterScene.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

USING_NS_CC;

#define TAG_MENU 1000
#define TAG_NEXT 1001
#define TAG_ATTACK 1002

#define TAG_Lab_Title       11
#define TAG_Lab_Content     12
#define TAG_Sprite_Bg       21
#define TAG_Sprite_Monster  22

Page *Page::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("Page", PageLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/page.ccbi", pOwner);
    
    Page *pPage = static_cast<Page *>(pNode);
    return pPage;
}


CCScene* Page::scene(int chapterId, const stPage *pPage)
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        Page *layer = Page::create();
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
        
        layer->turnToPage(chapterId, pPage);
    } while (0);

    return scene;
}

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

void Page::turnToPage(int chapterId, const stPage *pPage)
{
    if (!pPage) 
    {
        return;
    }
    m_nChapterId = chapterId;
    m_pPage = pPage;
    /*
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

    CCMenuItemSprite *pAttackItem  = CCMenuItemSprite::create(LuckySprite::create(29), LuckySprite::create(30), LuckySprite::create(31), this, menu_selector(Page::showBattleView));
    pAttackItem->setPosition(ccp(size.width - 50, 50));
    pMenu->addChild(pAttackItem, 0, TAG_ATTACK);
    
    const stMonster* pMonster = DictDataManager::shareDictDataManager()->getMonsterImageId(m_pPage->eventId);
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

     */
    
    m_title = (CCLabelTTF *)this->getChildByTag(TAG_Lab_Title);
    m_content = (CCLabelTTF *)this->getChildByTag(TAG_Lab_Content);
    
    m_SpriteMonster = (CCSprite *)this->getChildByTag(TAG_Sprite_Monster);
    m_SpriteBg = (CCSprite *)this->getChildByTag(TAG_Sprite_Bg);
    
    m_title->setString(m_pPage->name.c_str());
    m_content->setString(m_pPage->content.c_str());
}

void Page::showBattleView(CCObject *pSender)
{
    if ( EventListView::getIsInEvent() == false )
    {
        EventListView *pEventListView = EventListView::create();
        pEventListView->initLayer(m_pPage, this, callfuncND_selector(Page::fightCallback));
        CCDirector::sharedDirector()->getRunningScene()->addChild(pEventListView, 0, TAG_EVENT_LIST_LAYER);
    }
}

void Page::fightCallback(CCNode* pNode, void* data)
{   
    NetManager::shareNetManager()->sendEx(kModeBattle, kDoFight1, callfuncND_selector(Page::nextPageCallback), this, "\"chapterId\": %d, \"pageId\": %d", m_nChapterId, m_pPage->id);
}

void Page::nextPageCallback(CCNode* pNode, void* data)
{       
    Json::Value root;
    Json::Reader reader;
    
    if(!reader.parse(NetManager::shareNetManager()->processResponse(data), root) 
       && !root["meta"]["out"]["result"]["state"].asInt())
    {
        return;
    }
    
    LevelDataManager::shareLevelDataManager()->changePageState(m_nChapterId, m_pPage->id);
    //todo marcus m_tips->setString(m_pPage->state && m_pPage->end ? "End of Chapter" : "");
    
    const stPage *pPage = LevelDataManager::shareLevelDataManager()->getNewPage(m_nChapterId);
    if (m_pPage == pPage) 
    {
        CCDirector::sharedDirector()->popScene();
        return;
    }
    
    //CCScene *pScene = Page::scene(m_nChapterId, pPage);
    CCScene *pScene = CCScene::create();
    Page *pPageLayer = Page::create(pScene);
    pPageLayer->turnToPage(m_nChapterId,pPage);
    pScene->addChild(pPageLayer);
    
    CCTransitionPageTurn *pTp = CCTransitionPageTurn::create(TRANSITION_PAGE_INTERVAL_TIME, pScene, false);
    CCDirector::sharedDirector()->replaceScene(pTp);
}

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
        this->showBattleView(NULL);
    }
}

void Page::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}
