//
//  OpenBoxResultView.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "OpenBoxResultView.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"
#include "NetManager.h"
#include "DictDataManager.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

OpenBoxResultView *OpenBoxResultView::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("OpenBoxResultView", OpenBoxResultViewLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/box_tips.ccbi", pOwner);
    
    OpenBoxResultView *pOpenBoxResultView = static_cast<OpenBoxResultView *>(pNode);
    return pOpenBoxResultView;
}

void OpenBoxResultView::initView(std::vector<stGood> tGoodsList)
{
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *labtip = static_cast<CCLabelTTF *>(this->getChildByTag(11));
    
    CCPoint labtip_pos = labtip->getPosition();
    
    int i = 0;
    for (std::vector<stGood>::iterator _iter = tGoodsList.begin(); _iter < tGoodsList.end(); _iter++,i++) {
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
        
        CCLabelTTF *bonusLabel = CCLabelTTF::create(strChar, CCSizeMake(screanSize.width * 0.8f, screanSize.height * 0.15f ), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter,"Arial", 18);
        bonusLabel->setColor(ccWHITE);
        bonusLabel->setAnchorPoint(CCPointZero);
        bonusLabel->setPosition(CCPointMake(labtip_pos.x, labtip_pos.y - 25*i - 40));
        this->addChild(bonusLabel);
    }
}

void OpenBoxResultView::netCallBack(CCNode* pNode, void* data)
{    
    
}
