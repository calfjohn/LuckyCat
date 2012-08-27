//
//  CustomCCScrollView.h
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-27.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef __LuckyCat__CustomCCScrollView__
#define __LuckyCat__CustomCCScrollView__

#include <iostream>
#include "cocos2d.h"

class CustomCCScrollView : public cocos2d::extension::CCScrollView{
public:
    CustomCCScrollView();
    virtual ~CustomCCScrollView();
    
    bool init();
    virtual void registerWithTouchDispatcher();
    
};


#endif /* defined(__LuckyCat__CustomCCScrollView__) */
