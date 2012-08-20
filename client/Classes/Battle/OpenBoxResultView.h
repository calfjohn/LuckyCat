//
//  OpenBoxResultView.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_OpenBoxResultView_h
#define HelloWorld_OpenBoxResultView_h

#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCLayerLoader.h"
#include "Basic.h"
#include "EventBasic.h"
#include "BattleDefine.h"
#include "LuckySprite.h"



class OpenBoxResultView : public cocos2d::CCLayer 
{
public:
    
    static OpenBoxResultView *create(cocos2d::CCObject * pOwner);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(OpenBoxResultView, create);
    
    void initView(std::vector<stGood> tGoodsList);
    
    void netCallBack(CCNode* pNode, void* data);
    
    bool haveBox();
    
    void showBoxView();
    
private:
    stEvent *p_CurEvent;
};

class CCBReader;

class OpenBoxResultViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(OpenBoxResultViewLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(OpenBoxResultView);
};

#endif
