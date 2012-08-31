//
//  PKListView.h
//  HelloWorld
//
//  Created by Cocos2d-x on 12-8-29.
//
//

#ifndef __LuckyCat__PKListView__
#define __LuckyCat__PKListView__

#include <iostream>
#include <list>
#include <string.h>
#include "cocos2d.h"
#include "Basic.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "extensions/CCBReader/CCLayerLoader.h"

//#include "extensions\CCListView\CCListView.h"


USING_NS_CC;
USING_NS_CC_EXT;

class PKListView
: public CCLayer
, public CCListViewDelegate
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::CCTextFieldDelegate
{
private:
    CCLabelTTF *m_InfoLabel;
    
private:
    // 存放的List数据
    std::list<stPKInfo> m_pDataList;
    CCListView *m_pListView;
    bool m_bFresh;
    
public:
    PKListView();
    ~PKListView();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PKListView, create);
    
    static PKListView *create(cocos2d::CCObject * pOwner);
    
    CCNode* createNodeForCCBI(const char *pCCBFileName , const char *pCCNodeName , cocos2d::extension::CCNodeLoader *pCCNodeLoader);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onMenuItemClicked(cocos2d::CCObject *pTarget);
    
    void onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    //virtual bool init();
    
    //LAYER_CREATE_FUNC(PKListView);
    
    virtual void visit();
    
    virtual void registerWithTouchDispatcher();
    
    void sendPKListInfo();
    void responesPKListInfo(CCNode *pNode, void* data);
    
public:
    // 继承自CCListViewDelegate所需要实现的方法
    virtual void CCListView_numberOfCells(CCListView *listView, CCListViewProtrolData *data);
    virtual void CCListView_cellForRow(CCListView *listView, CCListViewProtrolData *data);
    virtual void CCListView_didClickCellAtRow(CCListView *listView, CCListViewProtrolData *data);
    virtual void CCListView_didScrollToRow(CCListView *listView, CCListViewProtrolData *data);
};

class CCBReader;

class PKListViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PKListViewLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PKListView);
};

#endif /* defined(__HelloWorld__PKListView__) */
