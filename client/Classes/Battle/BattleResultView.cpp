//
//  BattleResultView.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "BattleResultView.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"
#include "NetManager.h"
#include "OpenBoxView.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

BattleResultView *BattleResultView::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("BattleResultView", BattleResultViewLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/fullscreen_tips.ccbi", pOwner);
    
    BattleResultView *pBattleResultView = static_cast<BattleResultView *>(pNode);
    return pBattleResultView;
}

BattleResultView *BattleResultView::createBoxResultView(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("BattleResultView", BattleResultViewLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("", "ccb/box_tips.ccbi", pOwner);
    
    BattleResultView *pBattleResultView = static_cast<BattleResultView *>(pNode);
    return pBattleResultView;
}


void BattleResultView::initView(stEvent *tEvent)
{
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *resultOfBattle = static_cast<CCLabelTTF *>(this->getChildByTag(10));
    
    if (resultOfBattle)
    {
        resultOfBattle->setString("战斗失败");
    }
    
    CCLabelTTF *labtip = static_cast<CCLabelTTF *>(this->getChildByTag(11));
    
    CCPoint labtip_pos = labtip->getPosition();
    
    int i = 0;
    for (std::vector<stGood>::iterator _iter = tEvent->bonus.begin(); _iter < tEvent->bonus.end(); _iter++,i++) {
        stGood _goods = *_iter;
        
        char strChar[512];
        sprintf(strChar, "获得%d ：%d",_goods.id,_goods.num);
        CCLabelTTF *bonusLabel = CCLabelTTF::create(strChar, CCSizeMake(screanSize.width * 0.8f, screanSize.height * 0.15f ), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter,"Arial", 18);
        bonusLabel->setColor(ccWHITE);
        bonusLabel->setAnchorPoint(CCPointZero);
        bonusLabel->setPosition(CCPointMake(labtip_pos.x, labtip_pos.y - 25*i - 40));
        this->addChild(bonusLabel);
    }
    
//    NetManager::shareNetManager()->send(kModeGame, kDoGetUserInfo, "\"category\": \"basic\"",                                      callfuncND_selector(BattleResultView::netCallBack), this);
}

void BattleResultView::initView(std::vector<stGood> tGoodsList)
{
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *resultOfBattle = static_cast<CCLabelTTF *>(this->getChildByTag(10));
    
    if (resultOfBattle)
    {
        resultOfBattle->setString("开箱结果");
    }
    
    CCLabelTTF *labtip = static_cast<CCLabelTTF *>(this->getChildByTag(11));
    
    CCPoint labtip_pos = labtip->getPosition();
    
    int i = 0;
    for (std::vector<stGood>::iterator _iter = tGoodsList.begin(); _iter < tGoodsList.end(); _iter++,i++) {
        stGood _goods = *_iter;
        
        char strChar[512];
        sprintf(strChar, "获得%d ：%d",_goods.id,_goods.num);
        CCLabelTTF *bonusLabel = CCLabelTTF::create(strChar, CCSizeMake(screanSize.width * 0.8f, screanSize.height * 0.15f ), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter,"Arial", 18);
        bonusLabel->setColor(ccWHITE);
        bonusLabel->setAnchorPoint(CCPointZero);
        bonusLabel->setPosition(CCPointMake(labtip_pos.x, labtip_pos.y - 25*i - 40));
        this->addChild(bonusLabel);
    }
}

bool BattleResultView::haveBox()
{
    if ( p_CurEvent->box_id == -1  )
    {
        return false;
    }
    else {
        return true;
    }
}

void BattleResultView::showBoxView()
{
    OpenBoxView *pOpenBoxView = OpenBoxView::create(this);
    pOpenBoxView->setEvent(p_CurEvent);
    this->addChild(pOpenBoxView);
}



void BattleResultView::netCallBack(CCNode* pNode, void* data)
{    
    
}
