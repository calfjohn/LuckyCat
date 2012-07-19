//
//  CCTextFieldDelegateLayer.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_CCTextFieldDelegateLayer_h
#define HelloWorld_CCTextFieldDelegateLayer_h

#include "cocos2d.h"

NS_CC_BEGIN

class CCTextFieldDelegateLayer 
: public cocos2d::CCLayerColor
, public cocos2d::CCTextFieldDelegate
{
public:
    CCTextFieldDelegateLayer();
    virtual ~CCTextFieldDelegateLayer();
    
    static CCTextFieldDelegateLayer *node(void);
    
    virtual void onEnter();
    virtual void onExit();
    
    /**
     @brief    Register a CCTextFieldTTF point. It will be call function when be touch or outside of touch.
     */
    void registerCCTextFieldTTF(cocos2d::CCTextFieldTTF *p);
    
    /**
     @brief    Remove a CCTextFieldTTF point.
     @return    if it return false remove failed, else remove success
     */
    bool removeCCTextFieldTTF(cocos2d::CCTextFieldTTF *p);
    
    virtual void registerWithTouchDispatcher();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    /**
     @brief    If the sender doesn't want to attach with IME, return true;
     */
    virtual bool onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF * sender);
    
    /**
     @brief    If the sender doesn't want to detach with IME, return true;
     */
    virtual bool onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF * sender);
    
    /**
     @brief    If the sender doesn't want to insert the text, return true;
     */
    virtual bool onTextFieldInsertText(cocos2d::CCTextFieldTTF * sender, const char * text, int nLen);
    
    /**
     @brief    If the sender doesn't want to delete the delText, return true;
     */
    virtual bool onTextFieldDeleteBackward(cocos2d::CCTextFieldTTF * sender, const char * delText, int nLen);
    
    /**
     @brief     Posted immediately prior to the display of the keyboard.
     */
    virtual void UIKeyboardWillShow() {};
    
    /**
     @brief    Posted immediately prior to the dismissal of the keyboard.
     */
    virtual void UIKeyboardWillHide() {};
    
    
private:
    std::vector<cocos2d::CCTextFieldTTF *> m_TextFieldList;
    
    bool m_bIsShowKeyboard;
    
    void ShowKeyboard();
    
    void HidenKeyboard();
    
    static cocos2d::CCRect getRect(cocos2d::CCNode * pNode);
    
};

NS_CC_END

#endif
