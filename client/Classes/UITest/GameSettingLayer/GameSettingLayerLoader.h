//
//  GameSettingLayerLoader.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-11.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_GameSettingLayerLoader_h
#define HelloWorld_GameSettingLayerLoader_h

#include "extensions/CCBReader/CCLayerLoader.h"
#include "GameSettingLayer.h"

/* Forward declaration. */
class CCBReader;

class GameSettingLayerLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameSettingLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameSettingLayer);
};

#endif
