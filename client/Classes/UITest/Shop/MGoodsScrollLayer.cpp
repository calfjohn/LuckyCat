//
//  MGoodsScrollLayer.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MGoodsScrollLayer.h"
#include "MGoodsCellLayer.h"

void MGoodsScrollLayer::onEnter()
{
    m_ContainerLayer = NULL;
    m_ScrollView = NULL;
    
    
    
    CCLayerColor::onEnter();
    this->initLayer();
}

void MGoodsScrollLayer::initLayer()
{
    //
}

void MGoodsScrollLayer::initScrollView()
{
    if ( m_ScrollView )
    {
        m_ScrollView->removeAllChildrenWithCleanup(true);
        m_ScrollView = NULL;
    }
    
    m_intCellWidth = 104;
    m_intCellHeight = 104;
    
    m_intRowXNum = 3;
    
    m_intRowYNum = 2;
    
    m_intCellCount = 21;
    
    m_intCellIntervalX = m_intCellIntervalY = 12;
    
    m_intCellOfOnePage = m_intRowXNum * m_intRowYNum;
    
    
    if ( m_intCellCount != 0 )
    {
        m_intTotalPages = m_intCellCount / m_intCellOfOnePage;
        
        if ( m_intCellCount % m_intCellOfOnePage != 0  )
        {
            m_intTotalPages++;
        }
    } else {
        m_intTotalPages = 0;
    }
    
    
    
    m_SizeScrollView = CCSizeMake( m_intCellWidth * m_intRowXNum +  m_intCellIntervalX * ( m_intRowXNum  ) ,  m_intCellHeight * m_intRowYNum + m_intCellIntervalY * ( m_intRowYNum   ));
    
    //m_ContainerLayer = CCLayer::create();
    CCSize m_SizeContainer = CCSizeMake(m_SizeScrollView.width * m_intTotalPages, m_SizeScrollView.height);
    CCLayerColor *m_ContainerLayer = CCLayerColor::create( ccc4(251,23,56,46));
    
    m_ContainerLayer->setContentSize(m_SizeContainer);
    
//    m_ScrollView = CCScrollView::create();
//    
//    m_ScrollView->setContainer(m_ContainerLayer);
    
    m_ScrollView = CCScrollView::create(m_SizeScrollView,m_ContainerLayer);
    m_ScrollView->setDirection(CCScrollViewDirectionHorizontal);
    m_ScrollView->setDelegate(this);
    m_ScrollView->setPosition(ccp(50,50));
    m_ScrollView->setPagingEnabled(true);
    m_ScrollView->initNumberOfPage();
    this->addChild(m_ScrollView);
    
    for (int cellIndex = 0; cellIndex < m_intCellCount; cellIndex++)
    {
        //
        MGoodsCellLayer *cell = MGoodsCellLayer::create();
        cell->initWithGoodsID( cellIndex + 1 );
        int _t_page = cellIndex/m_intCellOfOnePage;
        int _t_index_page = cellIndex%m_intCellOfOnePage;
        int _t_index_page_x  = 0;
        if ( _t_index_page != 0 )_t_index_page_x = _t_index_page % m_intRowXNum;
        int _t_index_page_y = 0;
        if ( _t_index_page != 0 )_t_index_page_y = _t_index_page / m_intRowXNum;
        
        _t_index_page_y = m_intRowYNum - _t_index_page_y -1;
        
        int posX = _t_page * m_SizeScrollView.width + ( m_intCellIntervalX + m_intCellWidth ) * _t_index_page_x + m_intCellIntervalX * 0.5f ;
        int posY = ( m_intCellIntervalY + m_intCellHeight ) * _t_index_page_y + m_intCellIntervalY * 0.5f;
        
        CCLog("\nCellIndex : (%d,%d) , Page %d , X : %d , Y : %d \n" , cellIndex, m_intCellCount , _t_page, _t_index_page_x, _t_index_page_y);
        
        
        cell->setPosition(ccp( posX , posY ));
        m_ContainerLayer->addChild( cell );
        //m_ScrollView->addChild( cell );
    }
    
    m_ScrollView->moveToPage(2);
}


void MGoodsScrollLayer::initPage(int _page )
{
    //int cellIndex = _page * m_intCellOfOnePage;
    
}

void MGoodsScrollLayer::scrollViewDidScroll(CCScrollView* view)
{
    CCPoint offset = view->getContentOffset();
    
    //CCLog("scrollViewDidScroll Offsetf X : %d, Y %d \n", (int)offset.x, (int)offset.y);
}

void MGoodsScrollLayer::scrollViewDidZoom(CCScrollView* view)
{
    //CCLog("scrollViewDidZoom \n");
}

void MGoodsScrollLayer::scrollViewDidEndDecelerating(CCScrollView* view)
{
    CCPoint offset = view->getContentOffset();
    
    CCLog("scrollViewDidEndDecelerating Offsetf X : %d, Y %d \n", (int)offset.x, (int)offset.y);
    
//    int offsetX = offset.x;
//    float f_currentPage = offsetX * ( 1.0/ m_SizeScrollView.width );
//    
//    int currentPage = (int)f_currentPage;
//    
//    if ( f_currentPage > 0.5f + currentPage )currentPage ++;
//    
//    f_currentPage = 1;
//    
//    CCPoint newOffset = CCPointMake(  m_SizeScrollView.width * currentPage, offset.y);
//    
//    view->setContentOffset(newOffset,true);
}
