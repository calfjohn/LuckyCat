#include "LoginTestLayer.h"

#include "extensions/CCBReader/CCBReader.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define FONT_NAME                       "Thonburi"
#define FONT_SIZE                       18

LoginTestLayer::LoginTestLayer()
: mCCControlEventLabel(NULL) ,
m_TextField_Account(NULL) ,
m_TextField_Password(NULL) 
{}

LoginTestLayer::~LoginTestLayer()
{
    CC_SAFE_RELEASE(mCCControlEventLabel);
}

void LoginTestLayer::onEnter()
{
    cocos2d::CCLayer::onEnter();
    this->setTouchEnabled(true);
}

SEL_MenuHandler LoginTestLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    return NULL;    
}

SEL_CCControlHandler LoginTestLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", LoginTestLayer::onCCControlButtonClicked);
    
    return NULL;
}

bool LoginTestLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCCControlEventLabel", CCLabelBMFont *, this->mCCControlEventLabel);
    
    return false;
}

void LoginTestLayer::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    //
    CCNode *p_Node = (CCNode *)pSender;
    if ( p_Node )
    {
        int tag = p_Node->getTag();
        if ( tag == 11 )
        {
            CCLog("Login In Press");
        }
        else if ( tag == 12 )
        {
            CCLog("Press Register.");
        }
        this->UIKeyboardWillHide();
    }
}

void LoginTestLayer::onCCControlButtonClicked(cocos2d::CCObject *pSender) {
    //
}

void LoginTestLayer::initLayer()
{
    if ( NULL == m_TextField_Account )
    {
        //
        
        CCNode *p_Node = (CCNode *)this->getChildByTag(4);
        if ( p_Node )
        {
            cocos2d::CCRect tRect = getRect(p_Node);
            cocos2d::CCSize tSize = CCSizeMake(tRect.size.width - 12, tRect.size.height - 12 );
            cocos2d::CCPoint tPoint = CCPointMake(p_Node->getPosition().x + 6, p_Node->getPosition().y - 6);
            m_TextField_Account = cocos2d::CCTextFieldTTF::textFieldWithPlaceHolder("Please Input...",tSize,cocos2d::kCCTextAlignmentLeft,FONT_NAME,FONT_SIZE);
            m_TextField_Account->setAnchorPoint(p_Node->getAnchorPoint());
            m_TextField_Account->setPosition(tPoint);
            m_TextField_Account->setDelegate(this);
            this->registerCCTextFieldTTF(m_TextField_Account);
            this->addChild(m_TextField_Account);
        }
        p_Node = NULL;
        p_Node = (CCNode *)this->getChildByTag(5);
        if ( p_Node )
        {
            cocos2d::CCRect tRect = getRect(p_Node);
            cocos2d::CCSize tSize = CCSizeMake(tRect.size.width - 12, tRect.size.height - 12 );
            cocos2d::CCPoint tPoint = CCPointMake(p_Node->getPosition().x + 6, p_Node->getPosition().y - 6);
            m_TextField_Password = cocos2d::CCPTextFieldTTF::textFieldWithPlaceHolder("Please Input...",tSize,cocos2d::kCCTextAlignmentLeft,FONT_NAME,FONT_SIZE);
            m_TextField_Password->setAnchorPoint(p_Node->getAnchorPoint());
            m_TextField_Password->setPosition(tPoint);
            m_TextField_Password->setDelegate(this);
            m_TextField_Password->setIsSecureTextEntry(true);
            this->registerCCTextFieldTTF(m_TextField_Password);
            this->addChild(m_TextField_Password);
        }
    }
}

cocos2d::CCRect LoginTestLayer::getRect(cocos2d::CCNode * pNode)
{
    CCRect rc;
    rc.origin = pNode->getPosition();
    rc.size = pNode->getContentSize();
    rc.origin.x -= rc.size.width / 2;
    rc.origin.y -= rc.size.height / 2;
    return rc;
}

void LoginTestLayer::UIKeyboardWillShow()
{
    this->stopAllActions();
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSize tSize = pDirector->getWinSize();
    cocos2d::CCMoveTo *tAction = cocos2d::CCMoveTo::create(0.25f, ccp(0,tSize.height * 0.25f));
    this->runAction(tAction);
}

void LoginTestLayer::UIKeyboardWillHide()
{
    this->stopAllActions();
    cocos2d::CCMoveTo *tAction = cocos2d::CCMoveTo::create(0.25f, ccp(0,0));
    this->runAction(tAction);
}

