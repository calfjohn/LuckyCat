//
//  CCPTextFieldTTF.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "CCPTextFieldTTF.h"

//void cocos2d::CCPTextFieldTTF::draw()
//{
//    //
//}

cocos2d::CCPTextFieldTTF::CCPTextFieldTTF() : m_bSecureTextEntry(false)
{
    CCTextFieldTTF::CCTextFieldTTF();
}
cocos2d::CCPTextFieldTTF::~CCPTextFieldTTF()
{
    //Í
}

void cocos2d::CCPTextFieldTTF::setString(const char *text)
{
    CCTextFieldTTF::setString(text);
    if ( m_bSecureTextEntry == false ) return;
    if ( m_pInputText->length())
    {
        CCLabelTTF::setString(std::string(m_pInputText->length(), '*').c_str());
    }
}

//////////////////////////////////////////////////////////////////////////
// static constructor
//////////////////////////////////////////////////////////////////////////

cocos2d::CCPTextFieldTTF * cocos2d::CCPTextFieldTTF::textFieldWithPlaceHolder(const char *placeholder, const CCSize& dimensions, CCTextAlignment alignment, const char *fontName, float fontSize)
{        
    cocos2d::CCPTextFieldTTF *pRet = new cocos2d::CCPTextFieldTTF();
    if(pRet && pRet->initWithPlaceHolder("", dimensions, alignment, fontName, fontSize))
    {
        pRet->autorelease();
        if (placeholder)
        {
            pRet->setPlaceHolder(placeholder);
        }
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

cocos2d::CCPTextFieldTTF * cocos2d::CCPTextFieldTTF::textFieldWithPlaceHolder(const char *placeholder, const char *fontName, float fontSize)
{
    cocos2d::CCPTextFieldTTF *pRet = new cocos2d::CCPTextFieldTTF();
    if(pRet && pRet->initWithString("", fontName, fontSize))
    {
        pRet->autorelease();
        if (placeholder)
        {
            pRet->setPlaceHolder(placeholder);
        }
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}
