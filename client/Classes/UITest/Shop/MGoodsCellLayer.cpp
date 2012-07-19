//
//  MGoodsCellLayer.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MGoodsCellLayer.h"

void MGoodsCellLayer::onEnter()
{
    CCLayerColor::onEnter();
    
}

void MGoodsCellLayer::initLayer()
{
    //
}

void MGoodsCellLayer::initWithGoodsID(int _goodsID)
{
    //test 
    this->setContentSize(CCSizeMake(104, 104));
    this->setColor(ccBLUE);
    
    
    char strChar[512];
    memset(strChar, 0, 512);
    sprintf(strChar, "shop/prop_%d@2x.png", (_goodsID)%89);
    
    CCLog(strChar);
    
    //CCSprite* p_ImgGoods = CCSprite::create("goods_1.png");
    CCSprite* p_ImgGoods = CCSprite::create(strChar);
//    p_ImgGoods->setPosition(ccp(p_ImgGoods->getPosition().x, -p_ImgGoods->getPosition().y));
//    p_ImgGoods->setFlipX(true);
//    p_ImgGoods->setFlipY(true);
    if ( p_ImgGoods )
    {
        p_ImgGoods->setAnchorPoint(CCPointZero);
        p_ImgGoods->setPosition(CCPointZero);
        addChild(p_ImgGoods);
    }

    
    //test
    memset(strChar, 0, 512);
    sprintf(strChar, "%d", _goodsID);
    CCLabelTTF *cellLabel = CCLabelTTF::create( strChar, CCSizeMake(60, 30),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter,"Arial", 18); 
    //cellLabel->setPosition(ccp(cellSize.width , cellSize.height )); 
    cellLabel->setAnchorPoint(CCPointZero);
    cellLabel->setColor(ccGREEN);
    cellLabel->setPosition(ccp(10,10));
    this->addChild(cellLabel);
}

void MGoodsCellLayer::pressCell()
{
    
}