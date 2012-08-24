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
#include "LuckySprite.h"

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
    
    //    m_SpriteBg->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("monster_1.png"));
    //    
    //    m_SpriteMonster->setTexture(CCTextureCache::sharedTextureCache()->addImage("pub/image/hero/monster_1002.png"));
    char strChar[100];
    memset(strChar, 0, 100);
    sprintf(strChar, "scene_100%d.png",m_pPage->id);
    m_SpriteBg->setDisplayFrame(LuckySprite::getSpriteFrame(strChar));
    
    stEvent *tStEvent = EventDataManager::getShareInstance()->getEvent(m_pPage->eventId);
    memset(strChar, 0, 100);
    sprintf(strChar, "pub/image/hero/monster_100%d.png",tStEvent->targetId[0]);
    m_SpriteMonster->setTexture(LuckySprite::getTextrue2D(strChar));
    
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
    
    CCScene *pScene = Page::scene(m_nChapterId, pPage);
    CCTransitionPageTurn *pTp = CCTransitionPageTurn::create(TRANSITION_PAGE_INTERVAL_TIME, pScene, false);
    CCDirector::sharedDirector()->replaceScene(pTp);
    
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
    
    if ( pBeginPoint.x != 0 && pBeginPoint.y != 0 )
    {
        this->showBattleView(NULL);
    }
    pBeginPoint = CCPointZero;
    
}

void Page::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority + 20, true);
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
