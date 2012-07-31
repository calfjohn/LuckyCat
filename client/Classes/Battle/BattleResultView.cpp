//
//  BattleResultView.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "BattleResultView.h"

void BattleResultView::initView(stTask *tTask)
{
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLayerColor *bgColor = CCLayerColor::create(ccc4(0, 0, 0, 255));
    bgColor->setAnchorPoint(CCPointZero);
    bgColor->setContentSize(CCSizeMake(screanSize.width * 0.9f, screanSize.height * 0.7f));
    bgColor->setPosition(CCPointMake(screanSize.width * 0.05f, 100));
    this->addChild(bgColor,4);
        
    CCLabelTTF *labelTitle = CCLabelTTF::create("胜利", CCSizeMake(screanSize.width * 0.9f, screanSize.height * 0.2f ), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter,"Arial", 26);
    labelTitle->setColor(ccRED);
    labelTitle->setAnchorPoint(CCPointZero);
    labelTitle->setPosition(CCPointMake(0, screanSize.height *  0.53f ));
    bgColor->addChild(labelTitle);
    
    CCLabelTTF *labelPrize =  CCLabelTTF::create("获得以下奖励:", CCSizeMake(screanSize.width * 0.8f, screanSize.height * 0.05f ), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter,"Arial", 18);
    labelPrize->setColor(ccRED);
    labelPrize->setAnchorPoint(CCPointZero);
    labelPrize->setPosition(CCPointMake(screanSize.width * 0.05f, screanSize.height *  0.48f ));
    bgColor->addChild(labelPrize);
    
    int i = 0;
    for (std::vector<stGood>::iterator _iter = tTask->bonus.begin(); _iter < tTask->bonus.end(); _iter++,i++) {
        stGood _goods = *_iter;
        
        char strChar[512];
        sprintf(strChar, "GoodsName %d + %d",_goods.id,_goods.num);
        CCLabelTTF *bonusLabel = CCLabelTTF::create(strChar, CCSizeMake(screanSize.width * 0.8f, screanSize.height * 0.15f ), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter,"Arial", 18);
        bonusLabel->setColor(ccGREEN);
        bonusLabel->setAnchorPoint(CCPointZero);
        bonusLabel->setPosition(CCPointMake(screanSize.width * 0.1f, screanSize.height *  ( 0.38f - 0.10f*i ) ));
        bgColor->addChild(bonusLabel);
    }
}
