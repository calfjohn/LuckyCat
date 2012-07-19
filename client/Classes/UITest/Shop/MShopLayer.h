//
//  MShopLayer.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_MShopLayer_h
#define HelloWorld_MShopLayer_h

#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class MShopLayer : public CCLayerColor 
{
public:
    //
    LAYER_CREATE_FUNC(MShopLayer);
    
    virtual void onEnter();
    
    void initLayer();
    
    

};

#endif
