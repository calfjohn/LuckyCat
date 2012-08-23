/*
 * =====================================================================================
 *
 *       Filename:  PlayerInfoView.h
 *
 *    Description:  UI controller, Display player info 
 *
 *        Version:  1.0
 *        Created:  2012/7/30 17:13:29
 *       Revision:  none
 *
 *         Author:  lihex (lhx), hexuan.li@cocos2d-x.org
 *
 *    Copyright (c) 2012 厦门雅基软件有限公司. All rights reserved.
 *
 * =====================================================================================
 */


#ifndef  PlayerInfoView_INC
#define  PlayerInfoView_INC

#include "TouchLayer.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "extensions/CCBReader/CCLayerLoader.h"


enum PlayerInfoTag {
	kPlayerInfoTagPlayerBtn = 0,
	kPlayerInfoTagHeadBtn,
    kPlayerInfoTagHandBtn,
    kPlayerInfoTagBodyBtn,
    kPlayerInfoTagFootBtn,
    kPlayerInfoTagBasicLayer,
    kPlayerInfoTagEquipLayer,
};

class BasicInfoView;
class EquipInfoView;

class PlayerInfoView
: public TouchLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver
, public cocos2d::CCTextFieldDelegate
{
    public:
        PlayerInfoView();
        ~PlayerInfoView();
        
        
        CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(PlayerInfoView, create);
    
        static PlayerInfoView *create(cocos2d::CCObject * pOwner);
    
        virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
        virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
        virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    virtual void notificationTouchEvent(LTouchEvent tLTouchEvent);
    
    virtual void registerWithTouchDispatcher(void);
    
        CCNode* createNodeForCCBI(const char *pCCBFileName , const char *pCCNodeName , cocos2d::extension::CCNodeLoader *pCCNodeLoader);
    
        void onMenuItemClicked(cocos2d::CCObject *pTarget);
    
        void playerInfoBarBtnCallback(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
        
        void showViewForType();

        BasicInfoView *m_pBasicInfoView;
        EquipInfoView *m_pEquipInfoView;
    private:
        int m_iType;
}; /* -----  end of class PlayerInfoView  ----- */

class CCBReader;

class PlayerInfoViewLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PlayerInfoViewLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(PlayerInfoView);
};

#endif   /* ----- #ifndef PlayerInfoView_INC  ----- */
