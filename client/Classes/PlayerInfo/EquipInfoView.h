//
//  EquipInfoView.h
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-16.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef __LuckyCat__EquipInfoView__
#define __LuckyCat__EquipInfoView__

#include <iostream>
#include "cocos2d.h"
#include "Basic.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "extensions/CCBReader/CCLayerLoader.h"

typedef enum{
    kEquipHelmet      = 0,  //equip head;
    kEquipArms,             //equip arms;
    kEquipArmor,            //equip armor;
    kEquipShoes,            //equip shoes;
}EquipType;

class EquipInfoView
: public cocos2d::CCLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::CCTextFieldDelegate
{
public:
    EquipInfoView();
    ~EquipInfoView();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(EquipInfoView, create);
    
    //static EquipInfoView *create(cocos2d::CCObject * pOwner);
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void EquipViewBtnCallback(cocos2d::CCObject *pTarget);
    
    void onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    void showEquipView();
    
    void hideEquipView();
    
    void setEquipInfoForType(EquipType type);
    
    void setPlayerEquipInfoForType(EquipType type);

    void sendPlayerEquipInfo();

    void responsePlayerEquipInfo(CCNode *pNode, void* data);
private:
    cocos2d::CCLabelTTF *m_labEquipName;
    cocos2d::CCSprite *m_sprEquipIcon;
    std::vector<cocos2d::CCLabelTTF> m_labsEquipProprety;
    std::vector<cocos2d::CCLabelTTF> m_labsPlayerEquipInfo;

    std::vector<stActorUserEquipInfo> m_EquipData;

    //void setEquipInfo(cocos2d::CCSprite *equipIcon, cocos2d::CCLabelTTF *equipName, std::vector<cocos2d::CCLabelTTF> &equipProprety);
    
    void setPlayerEquipInfo();

};

class CCBReader;

class EquipInfoViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipInfoViewLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(EquipInfoView);
};

#endif /* defined(__LuckyCat__EquipInfoView__) */
