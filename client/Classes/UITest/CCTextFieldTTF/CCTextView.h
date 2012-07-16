////
////  CCTextView.h
////  HelloWorld
////
////  Created by XiaoZhong Zhu on 12-7-13.
////  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
////
//
//#ifndef HelloWorld_CCTextView_h
//#define HelloWorld_CCTextView_h
//
//#include "label_nodes/CCLabelTTF.h"
//#include "text_input_node/CCIMEDelegate.h"
//#include "touch_dispatcher/CCTouchDelegateProtocol.h"
//#include "extensions/CCScrollView/CCScrollView.h"
//#include "text_input_node/CCTextFieldTTF.h"
//
//NS_CC_BEGIN
//
//
//class CCTextView : public cocos2d::extension::CCScrollView , public CCIMEDelegate
//{
//    CCTextView();
//    virtual ~CCTextView();
//    
//    //char * description();
//    
//    /** creates a CCTextFieldTTF from a fontname, alignment, CCScrollView dimension, label dimension and font size */
//    static CCTextView * textFieldWithPlaceHolder(const char *placeholder, const CCSize & scrollViewDimensions, const CCSize& labelDimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
//    
//    /** initializes the CCTextFieldTTF with a font name, alignment, dimension and font size */
//    bool initWithPlaceHolder(const char *placeholder,  const CCSize & scrollViewDimensions, const CCSize& labelDimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
//    
//    /**
//     @brief    Open keyboard and receive input text.
//     */
//    virtual bool attachWithIME();
//    
//    /**
//     @brief    End text input  and close keyboard.
//     */
//    virtual bool detachWithIME();
//    
//    //////////////////////////////////////////////////////////////////////////
//    // properties
//    //////////////////////////////////////////////////////////////////////////
//    
//    CC_SYNTHESIZE(CCTextFieldDelegate *, m_pDelegate, Delegate);
//    CC_SYNTHESIZE_READONLY(int, m_nCharCount, CharCount);
//    CC_SYNTHESIZE_PASS_BY_REF(ccColor3B, m_ColorSpaceHolder, ColorSpaceHolder);
//    //A Boolean value indicating whether the receiver is editable.
//    CC_SYNTHESIZE(bool, m_bEditable, Editable);
//    
//    // input text property
//public:
//    virtual void setString(const char *text);
//    virtual const char* getString(void);
//protected:
//    std::string * m_pInputText;
//    
//    // place holder text property
//    // place holder text displayed when there is no text in the text field.
//public:
//    virtual void setPlaceHolder(const char * text);
//    virtual const char * getPlaceHolder(void);
//protected:
//    std::string * m_pPlaceHolder;
//protected:
//    
//    virtual void draw();
//    
//    //////////////////////////////////////////////////////////////////////////
//    // CCIMEDelegate interface
//    //////////////////////////////////////////////////////////////////////////
//    
//    virtual bool canAttachWithIME();
//    virtual bool canDetachWithIME();
//    virtual void insertText(const char * text, int len);
//    virtual void deleteBackward();
//    virtual const char * getContentText();
//private:
//    class LengthStack;
//    LengthStack * m_pLens;
//};
//
//NS_CC_END
//
//#endif
