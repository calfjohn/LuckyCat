//
//  MGoodsCellLayer.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_MGoodsCellLayer_h
#define HelloWorld_MGoodsCellLayer_h

#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class MGoodsCellLayer : public CCLayerColor 
{
public:
    //
    LAYER_CREATE_FUNC(MGoodsCellLayer);
    
    virtual void onEnter();
    
    void initLayer();
    
    void initWithGoodsID(int _goodsID);
    
    void initPage(int _page );
    
    void pressCell();
    
    
    
};

#endif
