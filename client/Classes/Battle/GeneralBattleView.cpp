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

bool GeneralBattleView::ccTouchBegan(CCTouch* touch, CCEvent *pEvent)
{
    if ( !touch ) return false;
    
    pBeginPoint = this->convertTouchToNodeSpace(touch);
    
    return true;
}

void GeneralBattleView::ccTouchMoved(CCTouch* touch, CCEvent *pEvent)
{
    
}

void GeneralBattleView::ccTouchEnded(CCTouch* touch, CCEvent *pEvent)
{
    if ( !touch ) return;
    CCPoint endPoint = this->convertTouchToNodeSpace(touch);
    
    if ( pBeginPoint.x != 0 && pBeginPoint.y != 0 )
    {
        getChildByTag(TAG_EFFECT_NODE)->runAction(CCSequence::create(
                                            CCShow::action(),
                                            m_action,
                                            CCHide::action(),
                                            CCCallFuncND::create(m_target, m_pfnSelector, NULL),
                                            NULL));
    }
    pBeginPoint = CCPointZero;
}

void GeneralBattleView::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority , true);
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
    
    this->setTouchEnabled(true);
    
    //this->showBattleResultView();
}

void GeneralBattleView::removeAndCleanSelf(float dt)
{
    ((m_target)->*(m_pfnSelector))(this, NULL);
}

void GeneralBattleView::menuBackCallback(CCObject* pSender)
{
    this->removeAndCleanSelf(0);
}

void GeneralBattleView::showBattleResultView()
{
    BattleResultView *retView = BattleResultView::create(this);
    retView->initView(p_CurEvent);
    this->addChild(retView,88);
}


