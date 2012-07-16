//
//  MTabLayerLoader.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_MTabLayerLoader_h
#define HelloWorld_MTabLayerLoader_h

#include "extensions/CCBReader/CCLayerLoader.h"
#include "MTabLayer.h"

/* Forward declaration. */
class CCBReader;

class MTabLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MTabLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MTabLayer);
};

#endif
