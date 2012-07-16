//
//  MGoodsScrollLayer.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_MGoodsScrollLayer_h
#define HelloWorld_MGoodsScrollLayer_h

#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class MGoodsScrollLayer : public CCLayerColor , public CCScrollViewDelegate 
{
public:
    //
    LAYER_CREATE_FUNC(MGoodsScrollLayer);
    
    virtual void onEnter();
    
    void initLayer();
    
    void initScrollView();
    
    void initPage(int _page );
    
    virtual void scrollViewDidScroll(CCScrollView* view);
    
    virtual void scrollViewDidZoom(CCScrollView* view);
    
    virtual void scrollViewDidEndDecelerating(CCScrollView* view);
    
private:
    //
    CCLayer *m_ContainerLayer;
    
    //
    CCScrollView *m_ScrollView;
    
    int m_intCellWidth;
    int m_intCellHeight;
    
    int m_intRowXNum;
    
    int m_intRowYNum;
    
    int m_intTotalPages;
    int m_intCurrentPage;
    
    int m_intCellCount;
    
    int m_intCellOfOnePage;
    
    int m_intCellIntervalX;
    int m_intCellIntervalY;
    
    CCSize m_SizeContainer;
    CCSize m_SizeScrollView;
    
};

#endif
