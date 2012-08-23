//
//  HeroHeadView.cpp
//  LuckyCat
//
//  Created by XiaoZhong Zhu on 12-8-20.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "HeroHeadView.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"
#include "PlayerInfoView.h"

#define TAG_BUTTON_OPEN_BOX 11

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

HeroHeadView::HeroHeadView()
{
    
}

HeroHeadView::~HeroHeadView()
{
    
}

HeroHeadView *HeroHeadView::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("HeroHeadView", HeroHeadViewLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/hero_head.ccbi", pOwner);
    
    HeroHeadView *pHeroHeadView = static_cast<HeroHeadView *>(pNode);
    return pHeroHeadView;
}

cocos2d::SEL_MenuHandler HeroHeadView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", HeroHeadView::onMenuItemClicked);
    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler HeroHeadView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", HeroHeadView::onCCControlButtonClicked );
    return NULL;
}
bool HeroHeadView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode)
{
    return false;
}

void HeroHeadView::onMenuItemClicked(cocos2d::CCObject *pTarget)
{
    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pTarget);
    printf("tag %d\n",p->getTag());
    
    if(p->getTag() == 1){
        PlayerInfoView *pInfo = PlayerInfoView::create(this);
        this->addChild(pInfo);
    }
}

void HeroHeadView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pSender);
    printf("tag %d\n",p->getTag());
}