//
//  PKListViewCell.h
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-31.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef __LuckyCat__PKListViewCell__
#define __LuckyCat__PKListViewCell__

#include <iostream>
#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "extensions/CCBReader/CCLayerLoader.h"
#include "Basic.h"

#define kPKListNickName 0
#define kPKListLevel 1
#define kPKListMenu 10

USING_NS_CC;
USING_NS_CC_EXT;


class PKListViewCell
: public CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::CCTextFieldDelegate
{
    
public:
    PKListViewCell();
    ~PKListViewCell();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PKListViewCell, create);
    
    static PKListViewCell *create(cocos2d::CCObject * pOwner);
    
    CCNode* createNodeForCCBI(const char *pCCBFileName , const char *pCCNodeName , cocos2d::extension::CCNodeLoader *pCCNodeLoader);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onMenuItemClicked(cocos2d::CCObject *pTarget);
    
    void onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    void setCellUserNickName(const char *pUserName);
    void setCellUserLevel(int level);
    void setCellUserId(int userId);
    
private:
    cocos2d::CCLabelTTF *m_userName;
    cocos2d::CCLabelTTF *m_userLevel;
    
    cocos2d::CCMenu *m_pkMenu;
    
    int m_userId;
    
    void pkCellMenuCallback(CCObject *pSender);
    
};

class CCBReader;

class PKListViewCellLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PKListViewCellLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PKListViewCell);
};

#endif /* defined(__LuckyCat__PKListViewCell__) */
