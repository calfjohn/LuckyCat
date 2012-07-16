//
//  TestController.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_TestController_h
#define HelloWorld_TestController_h

#include "cocos2d.h"
//#include "CCListView.h"

#include <string>
#include <vector>

#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCNodeLoaderListener.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"

USING_NS_CC;  
using namespace cocos2d::extension;

class TestScene;

class TestController : public CCLayerColor , CCListViewDelegate 
{
public:
    TestController();
    
    ~TestController();
    
    virtual void onEnter();
    
    void CellButtonCallback(CCObject * pSender);
    
    CCLayer * CreateLayer( int index );
    
    //设置有ListView中有多少列
    virtual void CCListView_numberOfCells(CCListView *listView, CCListViewProtrolData *data);
    //初始化单个cell
    virtual void CCListView_cellForRow(CCListView *listView, CCListViewProtrolData *data);
    //点中其中一行时回调
    virtual void CCListView_didClickCellAtRow(CCListView *listView, CCListViewProtrolData *data);
    //ListView滚动停止时回调
    virtual void CCListView_didScrollToRow(CCListView *listView, CCListViewProtrolData *data);
    
    void onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
private:
    
    CCListView *m_ListView;
    std::vector< std::string > m_TitleVector;
    
    void InitLayer();
    
    static TestScene* CreateTestScene(int nIdx);

    CCNode *openTest(const char * pCCBFileName, const char * pCCNodeName, CCNodeLoader * pCCNodeLoader);
    
    
};

#endif
