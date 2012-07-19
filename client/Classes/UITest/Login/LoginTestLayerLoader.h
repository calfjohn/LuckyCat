//
//  LoginTestLayerLoader.h
//  test
//
//  Created by XiaoZhong Zhu on 12-7-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef test_LoginTestLayerLoader_h
#define test_LoginTestLayerLoader_h

#include "extensions/CCBReader/CCLayerLoader.h"
#include "LoginTestLayer.h"

/* Forward declaration. */
class CCBReader;

class LoginTestLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LoginTestLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LoginTestLayer);
};

#endif
