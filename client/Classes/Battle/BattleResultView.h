//
//  BattleResultView.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_BattleResultView_h
#define HelloWorld_BattleResultView_h

#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCLayerLoader.h"
#include "Basic.h"
#include "TaskBasic.h"
#include "BattleDefine.h"
#include "LuckySprite.h"



class BattleResultView : public cocos2d::CCLayer 
{
public:
    
    static BattleResultView *create(cocos2d::CCObject * pOwner);
    
    static BattleResultView *createBoxResultView(cocos2d::CCObject *pOwner);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BattleResultView, create);
    
    void initView(stTask *tTask);
    
    void initView(std::vector<stGood> tGoodsList);
    
    void netCallBack(CCNode* pNode, void* data);
    
    bool haveBox();
    
    void showBoxView();
    
private:
    stTask *p_CurTask;
};

class CCBReader;

class BattleResultViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BattleResultViewLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(BattleResultView);
};

#endif
