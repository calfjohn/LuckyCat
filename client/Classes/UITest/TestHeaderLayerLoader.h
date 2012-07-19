//
//  TestHeaderLayerLoader.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_TestHeaderLayerLoader_h
#define HelloWorld_TestHeaderLayerLoader_h

#include "extensions/CCBReader/CCLayerLoader.h"
#include "LoginLayer.h"

/* Forward declaration. */
class CCBReader;

class TestHeaderLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(TestHeaderLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LoginLayer);
};

#endif
