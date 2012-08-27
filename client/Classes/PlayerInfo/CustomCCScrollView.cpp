//
//  CustomCCScrollView.cpp
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-27.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "CustomCCScrollView.h"

USING_NS_CC;
USING_NS_CC_EXT;

CustomCCScrollView::CustomCCScrollView(){

}
CustomCCScrollView::~CustomCCScrollView(){

}

bool CustomCCScrollView::init(){
    CCScrollView::init();
    return true;
}
void CustomCCScrollView::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -200, false);
}
