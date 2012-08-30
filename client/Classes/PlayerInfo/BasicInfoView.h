//
//  BasicInfoView.h
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-14.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef __LuckyCat__BasicInfoView__
#define __LuckyCat__BasicInfoView__

#include <iostream>
#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "extensions/CCBReader/CCLayerLoader.h"

class PlayerInfoView;

class BasicInfoView
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::CCTextFieldDelegate
{
public:
    PlayerInfoView *m_playerInfoView;
    
    BasicInfoView();
    virtual ~BasicInfoView();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BasicInfoView, create);
    
    static BasicInfoView *create(cocos2d::CCObject * pOwner);
    
    CCNode* createNodeForCCBI(const char *pCCBFileName , const char *pCCNodeName , cocos2d::extension::CCNodeLoader *pCCNodeLoader);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onMenuItemClicked(cocos2d::CCObject *pTarget);
    
    void onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    void showBasicView();
    
    void hideBasicView();
    
    void initBasicInfoView();
    
    void initBasicMenuTargetAndSel(CCObject *target, SEL_CallFuncND selector);
    
    void basicViewBtnCallback(CCObject *pSender);
    
    void sendBasicInfo();
    void responesBasicInfo(CCNode *pNode, void* data);
    void setBasicInfoLabelForTag(const int tag, cocos2d::CCString *infomation);
private:
    cocos2d::CCLabelTTF *m_labNickName;
    cocos2d::CCLabelTTF *m_labLevel;
    cocos2d::CCLabelTTF *m_labHP;
    cocos2d::CCLabelTTF *m_labAttack;
    cocos2d::CCLabelTTF *m_labRefensh;
    cocos2d::CCLabelTTF *m_labSpeed;
    cocos2d::CCLabelTTF *m_labTitle;
    cocos2d::CCLabelTTF *m_labScore;
    
    cocos2d::CCMenu *m_equipMenu;
    cocos2d::CCMenu *m_settingMenu;

    cocos2d::CCObject* m_pMenuTarget;
    cocos2d::SEL_CallFuncND m_MenuSelector;
};

class CCBReader;

class BasicInfoViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BasicInfoViewLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(BasicInfoView);
};



#endif /* defined(__LuckyCat__BasicInfoView__) */
