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
#include "PageEx.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"
#include "HeroHeadView.h"

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
        
        PageEx *layer2 = PageEx::create(scene);
        CC_BREAK_IF(! layer2);
        scene->addChild(layer2, -1000);
        
        Page *layer = Page::create(scene);
        CC_BREAK_IF(! layer);
        scene->addChild(layer);
        layer->turnToPage(chapterId, pPage);

    } while (0);

    return scene;
}

bool Page::init()
{
    CCTouchPageTurn::init();
    
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
    
    m_title = (CCLabelTTF *)this->getChildByTag(TAG_Lab_Title);
    m_content = (CCLabelTTF *)this->getChildByTag(TAG_Lab_Content);
    
    m_SpriteMonster = (CCSprite *)this->getChildByTag(TAG_Sprite_Monster);
    m_SpriteBg = (CCSprite *)this->getChildByTag(TAG_Sprite_Bg);
    
    m_title->setString(m_pPage->name.c_str());
    m_content->setString(m_pPage->content.c_str());
    
    this->showHeroHeadView();
}

void Page::showBattleView(CCObject *pSender)
{
    //load battle animation first
    CCAnimationCache *cache = CCAnimationCache::sharedAnimationCache();
    cache->addAnimationsWithFile("image/battle/animationsBomb.plist");
    
    if ( EventListView::getIsInEvent() == false )
    {
        EventListView *pEventListView = EventListView::create();
        pEventListView->initLayer(m_nChapterId,m_pPage, this, callfuncND_selector(Page::fightCallback));
        //CCDirector::sharedDirector()->getRunningScene()->addChild(pEventListView, 0, TAG_EVENT_LIST_LAYER);
        this->addChild(pEventListView,1);
        
        if (p_HeroHeadView)
        {
            p_HeroHeadView->removeFromParentAndCleanup(true);
            p_HeroHeadView= NULL;
        }
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
    
    CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
    Page *pPageLayer = Page::create(pScene);
    pPageLayer->turnToPage(m_nChapterId,pPage);
    pScene->addChild(pPageLayer, this->getZOrder()-1);
  
    this->autoTurnPage();
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

void Page::showHeroHeadView()
{
    if (p_HeroHeadView)
    {
        p_HeroHeadView->removeFromParentAndCleanup(true);
        p_HeroHeadView = NULL;
    }
    else {
        p_HeroHeadView = HeroHeadView::create(this);
        this->addChild(p_HeroHeadView,2);
    }
}
