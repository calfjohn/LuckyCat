#ifndef test_LoginTestLayer_h
#define test_LoginTestLayer_h

#include "cocos2d.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBMemberVariableAssigner.h"
#include "CCPTextFieldTTF.h"
#include "CCTextFieldDelegateLayer.h"


class LoginTestLayer 
: public cocos2d::CCTextFieldDelegateLayer
, public cocos2d::extension::CCBMemberVariableAssigner
, public cocos2d::extension::CCBSelectorResolver

{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LoginTestLayer, create);
    
    LoginTestLayer();
    virtual ~LoginTestLayer();
    
    void onEnter();
    
    void initLayer();
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName);
    virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode);
    
    void onCCControlButtonClicked(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
    
    void onCCControlButtonClicked(cocos2d::CCObject *pSender) ;
    
    
private:
    cocos2d::CCLabelBMFont * mCCControlEventLabel;
    
    cocos2d::CCTextFieldTTF * m_TextField_Account;
    
    cocos2d::CCPTextFieldTTF * m_TextField_Password;
    
    static cocos2d::CCRect getRect(cocos2d::CCNode * pNode);
        
    /**
     @brief     Posted immediately prior to the display of the keyboard.
     */
    virtual void UIKeyboardWillShow();
    
    /**
     @brief    Posted immediately prior to the dismissal of the keyboard.
     */
    virtual void UIKeyboardWillHide();
};

#endif
