//
//  CustomListView.cpp
//  HelloWorld
//
//  Created by Cocos2d-x on 12-8-29.
//
//

#include "CustomListView.h"

//#include "extensions\CCListView\CCListViewCell.h"

using namespace cocos2d::extension;

CustomListView::CustomListView()
{
    m_bFresh = true;
}

CustomListView::~CustomListView()
{
}

bool CustomListView::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        // 初始化List数据
        m_pDataList = new std::list<std::string>;
        for (int i=0; i<15; i++) {
            char info[20];
            sprintf(info, "Cell %d", i);
            m_pDataList->push_back(info);
        }
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        // 初始化控件ListView
        CCListView *listView = CCListView::create(CCListViewModeVertical);
        CCLOG("getAnchorPoint=%f,%f",listView->getAnchorPoint().x,listView->getAnchorPoint().y);
        CCSize listSize = CCSizeMake(winSize.width * 0.5, winSize.height*0.5);
        listView->setContentSize(listSize);
        listView->setDelegate(this);
        listView->setPosition(CCPointZero);
        this->addChild(listView);
        
        m_pListView = listView;
        
        // 初始化控件Label，显示ListView信息
        m_InfoLabel = CCLabelTTF::create("Info", "", 32);
        m_InfoLabel->setPosition(ccp(winSize.width * 3 / 4, winSize.height / 2));
        this->addChild(m_InfoLabel);
        
        CCLOG("listView->getSlideDir=%d",listView->getSlideDir());
        bRet = true;
    } while (0);
    
    return bRet;
}

void CustomListView::registerWithTouchDispatcher(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -900, false);
}

void CustomListView::visit()
{
    CCLayer::visit();
    if (m_bFresh) {
        m_pListView->reload();
        m_bFresh = false;
    }
}

void CustomListView::CCListView_numberOfCells(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    data->nNumberOfRows = m_pDataList->size();
    CCLOG("CustomListView::CCListView_numberOfCells=%u,NumberOfRows=%u,point=%d",m_pDataList->size(),data->nNumberOfRows,data);
}

void CustomListView::CCListView_cellForRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCSize listSize = m_pListView->getContentSize();
    CCSize cellSize = CCSizeMake(listSize.width, listSize.height / 5);
    
    CCListViewCell *cell = CCListViewCell::node();
    cell->setOpacity(0);
    cell->setContentSize(cellSize);
    cell->setSelectionColor(ccc4(255, 0, 0, 255));
    data->cell = cell;
    
    std::list<std::string>::iterator it = m_pDataList->begin();
    CCLOG("CustomListView::CCListView_cellForRow   data->nRow=%u,NumberOfRows=%u,point=%d",data->nRow,data->nNumberOfRows,data);
    for (unsigned int i=0; i<data->nRow; ++i) {
        ++it;
    }
    CCLabelTTF *cellLabel = CCLabelTTF::create(((std::string) *it).c_str(), "Arial", 32);
    cellLabel->setPosition(ccp(cellSize.width / 2, cellSize.height / 2));
    cell->addChild(cellLabel);
}

void CustomListView::CCListView_didClickCellAtRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    char info[100];
    CCLOG("CustomListView::CCListView_didClickCellAtRow nRow=%u,nNumberOfRows=%u,point=%d",data->nRow,data->nNumberOfRows,data);
    sprintf(info, "No. %d Row", data->nRow);
    m_InfoLabel->setString(info);
}

void CustomListView::CCListView_didScrollToRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    m_InfoLabel->setString("Scrolling...");
}