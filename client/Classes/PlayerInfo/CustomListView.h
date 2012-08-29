//
//  CustomListView.h
//  HelloWorld
//
//  Created by Cocos2d-x on 12-8-29.
//
//

#ifndef __LuckyCat__CustomListView__
#define __LuckyCat__CustomListView__

#include <iostream>
#include <list>
#include <string.h>
#include "cocos2d.h"

//#include "extensions\CCListView\CCListView.h"


USING_NS_CC;
USING_NS_CC_EXT;

class CustomListView: public CCLayer, public CCListViewDelegate
{
private:
    CCLabelTTF *m_InfoLabel;
    
private:
    // 存放的List数据
    std::list<std::string> *m_pDataList;
    CCListView *m_pListView;
    bool m_bFresh;
    
public:
    CustomListView();
    ~CustomListView();
    
    virtual bool init();
    
    LAYER_CREATE_FUNC(CustomListView);
    
    virtual void visit();
    
    virtual void registerWithTouchDispatcher();
    
public:
    // 继承自CCListViewDelegate所需要实现的方法
    virtual void CCListView_numberOfCells(CCListView *listView, CCListViewProtrolData *data);
    virtual void CCListView_cellForRow(CCListView *listView, CCListViewProtrolData *data);
    virtual void CCListView_didClickCellAtRow(CCListView *listView, CCListViewProtrolData *data);
    virtual void CCListView_didScrollToRow(CCListView *listView, CCListViewProtrolData *data);
};

#endif /* defined(__HelloWorld__CustomListView__) */
