//
//  CCPTextFieldTTF.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_CCPTextFieldTTF_h
#define HelloWorld_CCPTextFieldTTF_h

#include "text_input_node/CCTextFieldTTF.h"

NS_CC_BEGIN

class CC_DLL CCPTextFieldTTF : public cocos2d::CCTextFieldTTF
{
public:
    CCPTextFieldTTF();
    virtual ~CCPTextFieldTTF();
    
    
    static CCPTextFieldTTF * textFieldWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize);
    /** creates a CCLabelTTF from a fontname and font size */
    static CCPTextFieldTTF * textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize);
    
    CC_SYNTHESIZE(bool, m_bSecureTextEntry, IsSecureTextEntry);
    
    /**
     
     */
    // input text property
public:
    virtual void setString(const char *text);
    
    

    //
//protected:
//    
//    virtual void draw();
    
    

};

NS_CC_END

#endif
