//
//  PlayerInfoView.h
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-14.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef __LuckyCat__PlayerInfoView__
#define __LuckyCat__PlayerInfoView__

#include <iostream>
#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "extensions/CCBReader/CCLayerLoader.h"

class PlayerInfoView
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::CCTextFieldDelegate
{
public:
    PlayerInfoView();
    virtual ~PlayerInfoView();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PlayerInfoView, create);
    
    static PlayerInfoView *create(cocos2d::CCObject * pOwner);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onMenuItemClicked(cocos2d::CCObject *pTarget);
    
    void onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    void sendPlayerInfo();
    void responesPlayerInfo(CCNode *pNode, void* data);
    void setPlayerInfoLabelForTag(const int tag, cocos2d::CCString *infomation);
private:
    cocos2d::CCLabelTTF *m_labNickName;
    cocos2d::CCLabelTTF *m_labLevel;
    cocos2d::CCLabelTTF *m_labHP;
    cocos2d::CCLabelTTF *m_labAttack;
    cocos2d::CCLabelTTF *m_labRefensh;
    cocos2d::CCLabelTTF *m_labSpeed;
    cocos2d::CCLabelTTF *m_labTitle;
    cocos2d::CCLabelTTF *m_labScore;
    
};

class CCBReader;

class PlayerInfoViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PlayerInfoViewLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PlayerInfoView);
};



#endif /* defined(__LuckyCat__PlayerInfoView__) */
