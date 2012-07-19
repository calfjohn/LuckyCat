//
//  MTabLayer.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "MTabLayer.h"

#include "extensions/CCBReader/CCBReader.h"

#include "CCTextFieldDelegateLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define FONT_NAME                       "Thonburi"
#define FONT_SIZE                       18

#define TagDistance 3

MTabLayer::MTabLayer()
:m_LongText(NULL)
{}

MTabLayer::~MTabLayer()
{
}

SEL_MenuHandler MTabLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    return NULL;    
}

SEL_CCControlHandler MTabLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", MTabLayer::onCCControlButtonClicked);
    
    return NULL;
}

bool MTabLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    
    return false;
}

void MTabLayer::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    //
    CCControlButton *p_Node = (CCControlButton *)pSender;
    if ( p_Node )
    {
        int tag = p_Node->getTag();
        if ( tag == 1 )
        {
            p_CurButton->setEnabled(true);
            p_CurButton = p_Node;
            p_CurButton->setEnabled(false);
            
            m_intCurTab = 1;
            
            p_CurLayer->setTouchEnabled(false);
            p_CurLayer->setVisible(false);
            p_CurLayer  = (CCLayer *)this->getChildByTag(m_intCurTab + TagDistance);
            p_CurLayer->setTouchEnabled(true);
            p_CurLayer->setVisible(true);
            
            CCLog("Press Button Of Tab 1");
        }
        else if ( tag == 2 )
        {
            p_CurButton->setEnabled(true);
            p_CurButton = p_Node;
            p_CurButton->setEnabled(false);
            
            m_intCurTab = 2;
            
            p_CurLayer->setTouchEnabled(false);
            p_CurLayer->setVisible(false);
            p_CurLayer  = (CCLayer *)this->getChildByTag(m_intCurTab + TagDistance);
            p_CurLayer->setTouchEnabled(true);
            p_CurLayer->setVisible(true);
            
            initLongCCTextFieldTTF(p_CurLayer);
            
            CCLog("Press Button Of Tab 2");
        }
        else if ( tag == 3 )
        {
            p_CurButton->setEnabled(true);
            p_CurButton = p_Node;
            p_CurButton->setEnabled(false);
            
            m_intCurTab = 3;
            
            p_CurLayer->setTouchEnabled(false);
            p_CurLayer->setVisible(false);
            p_CurLayer  = (CCLayer *)this->getChildByTag(m_intCurTab + TagDistance);
            p_CurLayer->setTouchEnabled(true);
            p_CurLayer->setVisible(true);
            
            CCLog("Press Button Of Tab 3");
        }else if ( tag == 9 )
        {
            CCLog("Press Button In Tab 3 ... ... ...");
        }
    }
}

void MTabLayer::initLayer()
{
    p_CurButton = (CCControlButton *)this->getChildByTag(1);
    p_CurButton->setEnabled(false);
    
    m_intCurTab = 1;
    
    p_CurLayer  = (CCLayer *)this->getChildByTag(m_intCurTab + TagDistance);
    p_CurLayer->setTouchEnabled(true);
    p_CurLayer->setVisible(true);
}

void MTabLayer::initLongCCTextFieldTTF(cocos2d::CCLayer *p_parent)
{
    if ( m_LongText == NULL )
    {
        CCSize m_SizeContainer = CCSizeMake(400, 400);
        
        //CCLayerColor *m_ContainerLayer = CCLayerColor::create( ccc4(99,99,99,46));
        
        cocos2d::CCTextFieldDelegateLayer *m_ContainerLayer = cocos2d::CCTextFieldDelegateLayer::node();
        m_ContainerLayer->setColor(ccGRAY);
        
        m_ContainerLayer->setContentSize(m_SizeContainer);
        
        
        cocos2d::CCPoint tPoint = CCPointMake(0,0);
        m_LongText = cocos2d::CCPTextFieldTTF::textFieldWithPlaceHolder("Please Input...",m_SizeContainer,cocos2d::kCCTextAlignmentLeft,FONT_NAME,FONT_SIZE);
        m_LongText->setAnchorPoint(CCPointZero);
        m_LongText->setPosition(tPoint);
        m_LongText->setDelegate(this);
        //m_LongText->setIsSecureTextEntry(true);
        m_ContainerLayer->addChild(m_LongText);
        
        //m_ContainerLayer->registerCCTextFieldTTF(m_LongText);
        
        m_LongText->setString("今日，三星公司宣布他们将在这个月在其智能电视机平台推出“手动版”《愤怒的小鸟》。三星自上年年底就开始与Rovio合作开发这款全新的游戏。据生产商表示，这个版本的《愤怒的小鸟》将整合了三星电视机动作识别的功能。玩家只需使用自己的双手就能操控屏幕里的弹弓。");
        
        CCSize tSize = CCSizeMake(400, 200);
        CCScrollView *p_scroll = CCScrollView::create(tSize,m_ContainerLayer);
        p_scroll->setDirection(CCScrollViewDirectionVertical);
        p_scroll->setPosition(ccp(20,20));
//        p_scroll->setContentOffset(ccp(0,-200));
        p_scroll->scrollsToTop();
        p_parent->addChild(p_scroll);
        
    }
}