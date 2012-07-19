#include "GameSettingLayer.h"

#include "extensions/CCBReader/CCBReader.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define FONT_NAME                       "Thonburi"
#define FONT_SIZE                       18

GameSettingLayer::GameSettingLayer()
{}

GameSettingLayer::~GameSettingLayer()
{
}

SEL_MenuHandler GameSettingLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, CCString * pSelectorName) {
    return NULL;    
}

SEL_CCControlHandler GameSettingLayer::onResolveCCBCCControlSelector(CCObject * pTarget, CCString * pSelectorName) {
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", GameSettingLayer::onCCControlButtonClicked);
    
    return NULL;
}

bool GameSettingLayer::onAssignCCBMemberVariable(CCObject * pTarget, CCString * pMemberVariableName, CCNode * pNode) {
    
    return false;
}

void GameSettingLayer::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    //
    CCNode *p_Node = (CCNode *)pSender;
    if ( p_Node )
    {
        int tag = p_Node->getTag();
        if ( tag == 2 )
        {
            CCLog("Press Button Of OK");
        }
        else if ( tag == 3 )
        {
            CCLog("Press Button Of Cancel");
        }
    }
}

void GameSettingLayer::initLayer()
{
    CCLabelTTF *p_label = (CCLabelTTF *)this->getChildByTag(1);
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint tPoint = p_label->getPosition();
    // Add the slider
    CCControlSlider *slider = CCControlSlider::create("extensions/sliderTrack.png","extensions/sliderProgress.png" ,"extensions/sliderThumb.png");
    slider->setAnchorPoint(ccp(0.5f, 1.0f));
    slider->setMinimumValue(0.0f); // Sets the min value of range
    slider->setMaximumValue(5.0f); // Sets the max value of range
    slider->setPosition(ccp(screenSize.width / 2.0f, tPoint.y - 20.0f));
    
    // When the value of the slider will change, the given selector will be call
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(GameSettingLayer::valueChanged), CCControlEventValueChanged);
    
    this->addChild(slider);   
    
    // Create the switch
    CCControlSwitch *switchControl = CCControlSwitch::create
    (
     CCSprite::create("extensions/switch-mask.png"),
     CCSprite::create("extensions/switch-on.png"),
     CCSprite::create("extensions/switch-off.png"),
     CCSprite::create("extensions/switch-thumb.png"),
     CCLabelTTF::create("On", "Thonburi", 16),
     CCLabelTTF::create("Off", "Thonburi", 16)
     );
    switchControl->setPosition(ccp(screenSize.width / 2.0f, tPoint.y - 140.0f));
    this->addChild(switchControl);
    
    switchControl->addTargetWithActionForControlEvents(this, cccontrol_selector(GameSettingLayer::SwitchControlValueChanged), CCControlEventValueChanged);
}

void GameSettingLayer::valueChanged(cocos2d::CCObject *sender, cocos2d::extension::CCControlEvent controlEvent)
{
    CCControlSlider* pSlider = (CCControlSlider*)sender;
    // Change value of label.
    CCLabelTTF *p_label = (CCLabelTTF *)this->getChildByTag(1);
    if ( p_label != NULL )
    {
        p_label->setString(CCString::createWithFormat("Slider value = %.02f", pSlider->getValue())->getCString() );
    }
}

void GameSettingLayer::SwitchControlValueChanged(cocos2d::CCObject *sender, cocos2d::extension::CCControlEvent controlEvent)
{
    // Change value of label.
    CCLabelTTF *p_label = (CCLabelTTF *)this->getChildByTag(1);
    if ( p_label != NULL )
    {
        CCControlSwitch* pSwitch = (CCControlSwitch*)sender;
        if (pSwitch->isOn())
        {
            p_label->setString("On");
        } 
        else
        {
            p_label->setString("Off");
        }
    }
}