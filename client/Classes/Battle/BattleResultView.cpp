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
#include "DictDataManager.h"

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

void BattleResultView::initView(LEventData *tEvent)
{
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *resultOfBattle = static_cast<CCLabelTTF *>(this->getChildByTag(10));
    
    if (resultOfBattle)
    {
        resultOfBattle->setString("战斗胜利");
    }
    
    CCLabelTTF *labtip = static_cast<CCLabelTTF *>(this->getChildByTag(11));
    
    CCPoint basePosition = labtip->getPosition();
    
    CCLabelTTF *bonusLabel = CCLabelTTF::create("过关奖励", CCSizeMake(screanSize.width * 0.8f, screanSize.height * 0.15f ), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter,"Arial", 18);
    bonusLabel->setColor(ccORANGE);
    bonusLabel->setAnchorPoint(CCPointZero);
    bonusLabel->setPosition(CCPointMake(basePosition.x, basePosition.y - 40));
    this->addChild(bonusLabel);
    
    basePosition = bonusLabel->getPosition();
    for (std::vector<stGood>::iterator _iter = tEvent->bonus.begin(); _iter < tEvent->bonus.end(); _iter++) 
    {
        stGood _goods = *_iter;
        
        char strChar[64];
        
        if (_goods.type == 1) {
            sprintf(strChar, "获得金币 ：%d",_goods.count);
        }
        else if (_goods.type == 2)
        {
            sprintf(strChar, "获得经验 ：%d",_goods.count);
        }
        else if (_goods.type == 3){
            sprintf(strChar, "获得物品 ：%d",_goods.count);
        }
        else if (_goods.type == 4){
            const stActorEquipInfo *pTempEquip = DictDataManager::shareDictDataManager()->getEquipment(_goods.id);
            if (pTempEquip) {
                sprintf(strChar, "获得装备 ：%s %d件",pTempEquip->equipName.c_str(),_goods.count);
            }
            else {
                sprintf(strChar, "获得装备 ：错误id %d",_goods.id);
            }
        }
        bonusLabel = CCLabelTTF::create(strChar, CCSizeMake(screanSize.width * 0.8f, screanSize.height * 0.15f ), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter,"Arial", 18);
        bonusLabel->setColor(ccWHITE);
        bonusLabel->setAnchorPoint(CCPointZero);
        bonusLabel->setPosition(CCPointMake(basePosition.x, basePosition.y  - 18));
        this->addChild(bonusLabel);
        basePosition = bonusLabel->getPosition();
    }
    
    bonusLabel = CCLabelTTF::create("战斗奖励", CCSizeMake(screanSize.width * 0.8f, screanSize.height * 0.15f ), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter,"Arial", 18);
    bonusLabel->setColor(ccORANGE);
    bonusLabel->setAnchorPoint(CCPointZero);
    bonusLabel->setPosition(CCPointMake(basePosition.x, basePosition.y - 18));
    this->addChild(bonusLabel);  
    
    basePosition = bonusLabel->getPosition();
    for (std::vector<stGood>::iterator _iter = tEvent->awardArray.begin(); _iter < tEvent->awardArray.end(); _iter++) 
    {
        stGood _goods = *_iter;
        
        char strChar[64];
        
        if (_goods.type == 1) {
            sprintf(strChar, "获得金币 ：%d",_goods.count);
        }
        else if (_goods.type == 2)
        {
            sprintf(strChar, "获得经验 ：%d",_goods.count);
        }
        else if (_goods.type == 3){
            sprintf(strChar, "获得物品 ：%d",_goods.count);
        }
        else if (_goods.type == 4){
            sprintf(strChar, "获得装备 ：%d",_goods.count);
        }
        bonusLabel = CCLabelTTF::create(strChar, CCSizeMake(screanSize.width * 0.8f, screanSize.height * 0.15f ), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter,"Arial", 18);
        bonusLabel->setColor(ccWHITE);
        bonusLabel->setAnchorPoint(CCPointZero);
        bonusLabel->setPosition(CCPointMake(basePosition.x, basePosition.y  - 18));
        this->addChild(bonusLabel);
        basePosition = bonusLabel->getPosition();
    }
}

void BattleResultView::setSelector(cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector)
{
    pBeginPoint = CCPointZero;
    this->setTouchEnabled(true);
    
    m_target = target;
    m_pfnSelector = pfnSelector;
}

void BattleResultView::initView(std::vector<stGood> tGoodsList)
{
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *resultOfBattle = static_cast<CCLabelTTF *>(this->getChildByTag(10));
    
    if (resultOfBattle)
    {
        resultOfBattle->setString("开箱结果:");
    }
    
    CCLabelTTF *labtip = static_cast<CCLabelTTF *>(this->getChildByTag(11));
    
    CCPoint labtip_pos = labtip->getPosition();
    
    int i = 0;
    for (std::vector<stGood>::iterator _iter = tGoodsList.begin(); _iter < tGoodsList.end(); _iter++,i++) {
        stGood _goods = *_iter;
        
        char strChar[512];
        sprintf(strChar, "获得%d ：%d",_goods.id,_goods.count);
        CCLabelTTF *bonusLabel = CCLabelTTF::create(strChar, CCSizeMake(screanSize.width * 0.8f, screanSize.height * 0.15f ), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter,"Arial", 18);
        bonusLabel->setColor(ccWHITE);
        bonusLabel->setAnchorPoint(CCPointZero);
        bonusLabel->setPosition(CCPointMake(labtip_pos.x, labtip_pos.y - 25*i - 40));
        this->addChild(bonusLabel);
    }
}

void BattleResultView::netCallBack(CCNode* pNode, void* data)
{    
    
}

void BattleResultView::notificationTouchEvent(LTouchEvent tLTouchEvent)
{
    if (tLTouchEvent == kLTouchEventSingleClick)
    {
        if ( m_target && m_pfnSelector )
            ((m_target)->*(m_pfnSelector))(this, NULL);
    }
}