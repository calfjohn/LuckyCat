//
//  GeneralBattleView.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-8-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "GeneralBattleView.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

#include "EventDataManager.h"
#include "BattleResultView.h"
#include "LuckySprite.h"
#include "FuzzyBgView.h"

#include "PlayerInfoView.h"

#define TAG_EFFECT_NODE 3
#define TAG_MONSTER 91

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

GeneralBattleView::GeneralBattleView()
{
    CCAnimationCache *cache = CCAnimationCache::sharedAnimationCache();
    CCAnimation *animation= cache->animationByName("purpleBomb");
    m_action = CCAnimate::create(animation);
    CC_SAFE_RETAIN(m_action);
}

GeneralBattleView::~GeneralBattleView()
{
    CC_SAFE_RELEASE(m_action);
}

GeneralBattleView *GeneralBattleView::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("GeneralBattleView", GeneralBattleViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("FuzzyBgView", FuzzyBgViewLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/battle.ccbi", pOwner);
    
    GeneralBattleView *pGeneralBattleView = static_cast<GeneralBattleView *>(pNode);
    
    pGeneralBattleView->getChildByTag(3)->setVisible(false);
    
    return pGeneralBattleView;
}

cocos2d::SEL_MenuHandler GeneralBattleView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", GeneralBattleView::onMenuItemClicked);
    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler GeneralBattleView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", GeneralBattleView::onCCControlButtonClicked );
    return NULL;
}
bool GeneralBattleView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode)
{
    
    return false;
}

void GeneralBattleView::onMenuItemClicked(cocos2d::CCObject *pTarget)
{
    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pTarget);
    printf("tag %d\n",p->getTag());
}

void GeneralBattleView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    
}

void GeneralBattleView::notificationTouchEvent(LTouchEvent tLTouchEvent)
{
    if (tLTouchEvent == kLTouchEventSingleClick)
    {
        getChildByTag(TAG_EFFECT_NODE)->runAction(CCSequence::create(
                                                                     CCShow::create(),
                                                                     m_action,
                                                                     CCHide::create(),
                                                                     CCCallFuncND::create(m_target, m_pfnSelector, NULL),
                                                                     NULL));
        
        this->setIsTouchForbidden(true);
    }
}

void GeneralBattleView::setData(LEventData *tEvent, cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector)
{
    p_CurEvent = tEvent;
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    pBeginPoint = CCPointZero;
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 100, 1000);
    
    CCMenuItemSprite *pBackItem = CCMenuItemSprite::create(LuckySprite::create(2), LuckySprite::create(3), LuckySprite::create(3), this, menu_selector(GeneralBattleView::menuBackCallback)); 
    pBackItem->setScale(0.5);
    pBackItem->setPosition(ccp(screanSize.width - 30, screanSize.height - 20));
    pMenu->addChild(pBackItem,5);
    
    CCSprite *pMonster = static_cast<CCSprite *>(this->getChildByTag(TAG_MONSTER));
    if (pMonster)
    {
        stEvent *tStEvent = tEvent->pStEvent;
        char strChar[100];
        memset(strChar, 0, 100);
        sprintf(strChar, "pub/image/hero/monster_100%d.png",tStEvent->targetId[0]);
        pMonster->setTexture(LuckySprite::getTextrue2D(strChar));
    }
    
    this->setTouchEnabled(true);
}

void GeneralBattleView::removeAndCleanSelf(float dt)
{
    ((m_target)->*(m_pfnSelector))(this, NULL);
}

void GeneralBattleView::menuBackCallback(CCObject* pSender)
{
    this->removeAndCleanSelf(0);
}


