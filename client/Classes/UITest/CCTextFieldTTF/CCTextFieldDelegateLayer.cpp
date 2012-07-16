//
//  CCTextFieldDelegateLayer.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "CCTextFieldDelegateLayer.h"

cocos2d::CCTextFieldDelegateLayer::CCTextFieldDelegateLayer()
: m_bIsShowKeyboard(false)
{
    m_TextFieldList.clear();
}

cocos2d::CCTextFieldDelegateLayer::~CCTextFieldDelegateLayer()
{
    m_TextFieldList.clear();
}

cocos2d::CCTextFieldDelegateLayer *cocos2d::CCTextFieldDelegateLayer::node(void)
{
    CCTextFieldDelegateLayer *pRet = new CCTextFieldDelegateLayer();
    pRet->CCLayerColor::initWithColor(ccc4(255, 255, 255, 255), 0, 0);
    pRet->autorelease();
    return pRet;
}

void cocos2d::CCTextFieldDelegateLayer::onEnter()
{
    CCLayerColor::onEnter();
    
    setTouchEnabled(true);
}
void cocos2d::CCTextFieldDelegateLayer::onExit()
{
    CCLayerColor::onExit();
}

void cocos2d::CCTextFieldDelegateLayer::registerCCTextFieldTTF(cocos2d::CCTextFieldTTF *p)
{
    if ( p )m_TextFieldList.push_back(p);
}

bool cocos2d::CCTextFieldDelegateLayer::removeCCTextFieldTTF(cocos2d::CCTextFieldTTF *p)
{
    if ( p )
    {
        std::vector<cocos2d::CCTextFieldTTF *>::iterator iterFlag = m_TextFieldList.begin();
        std::vector<cocos2d::CCTextFieldTTF *>::iterator iterEnd = m_TextFieldList.end();
        for (; iterEnd != iterFlag; iterFlag++)
        {
            cocos2d::CCTextFieldTTF *t_pTextField = *iterFlag;
            if ( t_pTextField == p )
            {
                m_TextFieldList.erase(iterFlag);
                
                return true;
            }
        }
    }
    
    return false;
}

void cocos2d::CCTextFieldDelegateLayer::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool cocos2d::CCTextFieldDelegateLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}

void cocos2d::CCTextFieldDelegateLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    // decide the trackNode is clicked.
    CCPoint point = convertTouchToNodeSpace(pTouch);
    
    bool t_bIsAttachIME = false;
    
    std::vector<cocos2d::CCTextFieldTTF *>::iterator iterFlag = m_TextFieldList.begin();
    std::vector<cocos2d::CCTextFieldTTF *>::iterator iterEnd = m_TextFieldList.end();
    for (; iterEnd != iterFlag; iterFlag++)
    {
        cocos2d::CCTextFieldTTF * p_TextField = *iterFlag;
        
        CCRect tRect = getRect(p_TextField);
        
        if ( CCRect::CCRectContainsPoint(tRect, point) )
        {
            p_TextField->attachWithIME();
            
            this->ShowKeyboard();
            
            t_bIsAttachIME = true;
            
            break;
        }
    }
    
    if ( false == t_bIsAttachIME )
    {
        iterFlag = m_TextFieldList.begin();
        iterEnd = m_TextFieldList.end();
        for (; iterEnd != iterFlag; iterFlag++)
        {
            cocos2d::CCTextFieldTTF * p_TextField = *iterFlag;
            
            p_TextField->detachWithIME();
        }
        
        this->HidenKeyboard();
    }
}

bool cocos2d::CCTextFieldDelegateLayer::onTextFieldAttachWithIME(cocos2d::CCTextFieldTTF * sender)
{ 
    CC_UNUSED_PARAM(sender);
    return false;
}

bool cocos2d::CCTextFieldDelegateLayer::onTextFieldDetachWithIME(cocos2d::CCTextFieldTTF * sender)
{
    CC_UNUSED_PARAM(sender);
    
    this->HidenKeyboard();
    
    return false;
}

bool cocos2d::CCTextFieldDelegateLayer::onTextFieldInsertText(cocos2d::CCTextFieldTTF * sender, const char * text, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(text);
    CC_UNUSED_PARAM(nLen);
    return false;
}

bool cocos2d::CCTextFieldDelegateLayer::onTextFieldDeleteBackward(cocos2d::CCTextFieldTTF * sender, const char * delText, int nLen)
{
    CC_UNUSED_PARAM(sender);
    CC_UNUSED_PARAM(delText);
    CC_UNUSED_PARAM(nLen);
    return false;
}

void cocos2d::CCTextFieldDelegateLayer::ShowKeyboard()
{
    if ( false == m_bIsShowKeyboard )
    {
        UIKeyboardWillShow();
        
        m_bIsShowKeyboard = true;
        
        CCLOG("Show Keyboard...");
    }
}

void cocos2d::CCTextFieldDelegateLayer::HidenKeyboard()
{
    if ( true == m_bIsShowKeyboard )
    {
        UIKeyboardWillHide();
        
        m_bIsShowKeyboard = false;
        
        CCLOG("Hiden Keyboard...");
    }
}

cocos2d::CCRect cocos2d::CCTextFieldDelegateLayer::getRect(cocos2d::CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    
    CCPoint tPoint = pNode->getAnchorPoint();
    
    rc.origin.x -= rc.size.width * tPoint.x;
    rc.origin.y -= rc.size.height * tPoint.y;
    return rc;
}
