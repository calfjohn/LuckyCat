//
//  OpenBoxView.cpp
//  LuckyCat
//
//  Created by XiaoZhong Zhu on 12-8-10.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "OpenBoxView.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"
#include "TaskDataManager.h"
#include "TaskBasic.h"
#include "LuckySprite.h"
#include "BattleResultView.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

OpenBoxView::OpenBoxView()
{
    
}

OpenBoxView::~OpenBoxView()
{
    
}

OpenBoxView *OpenBoxView::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("OpenBoxView", OpenBoxViewLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("", "ccb/openbox.ccbi", pOwner);
    
    OpenBoxView *pOpenBoxView = static_cast<OpenBoxView *>(pNode);
    return pOpenBoxView;
}

cocos2d::SEL_MenuHandler OpenBoxView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", OpenBoxView::onMenuItemClicked);
    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler OpenBoxView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", OpenBoxView::onCCControlButtonClicked );
    return NULL;
}
bool OpenBoxView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode)
{
    return false;
}

void OpenBoxView::onMenuItemClicked(cocos2d::CCObject *pTarget)
{
    
}

void OpenBoxView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    
}

void OpenBoxView::setTask(stTask *t)
{
    p_CurTask = t;
}

void OpenBoxView::showResultView()
{
    vector<stGood> tGoodsList;
    for (int i = 0; i < 3; i++) {
        stGood good_;
        good_.id = 100 + i;
        good_.num = 1000 * i;
    }
    BattleResultView *pOpenBoxResult = BattleResultView::create(this);
    pOpenBoxResult->initView(tGoodsList);
}