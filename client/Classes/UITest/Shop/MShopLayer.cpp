//
//  MShopLayer.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MShopLayer.h"
#include "MGoodsScrollLayer.h"

void MShopLayer::onEnter()
{
    CCLayerColor::onEnter();
}

void MShopLayer::initLayer()
{
    MGoodsScrollLayer *p_ScrollLayer = MGoodsScrollLayer::create();
    p_ScrollLayer->initScrollView();
    this->addChild(p_ScrollLayer);
}