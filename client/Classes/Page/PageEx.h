//
//  PageEx.h
//  cocos2dx
//
//  Created by Cocos2d on 12-8-21.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef __PAGEEX_SCENE_H__
#define __PAGEEX_SCENE_H__

#include "cocos2d.h"
#include "extensions/CCBReader/CCLayerLoader.h"

class PageEx : public cocos2d::CCLayer
{
public:
    static PageEx *create(cocos2d::CCObject * pOwner);
    
    virtual bool init();  

    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(PageEx);
};

class CCBReader;

class PageExLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PageExLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PageEx);
};

#endif  // __PAGEEX_SCENE_H__