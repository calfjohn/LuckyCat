//
//  BasicInfoView.cpp
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-14.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "BasicInfoView.h"
#include "FuzzyBgView.h"
#include "PlayerInfoView.h"
#include "NetManager.h"
#include "json.h"
#include "CCNetwork.h"
#include "CCCallbackNode.h"
#include "Basic.h"
#include "PlayerInfoDataManager.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
enum BasicInfoTag{
    kNickNameInfo = 0,
    kLevelInfo,
    kHpInfo,
    kAttackInfo,
    kRefenshInfo,
    kSpeedInfo,
    kTitleInfo,
    kScoreInfo,
    
    kInfoCount,
};

BasicInfoView::BasicInfoView()
{
    m_labNickName = NULL;
    m_labLevel = NULL;
    m_labHP = NULL;
    m_labAttack = NULL;
    m_labRefensh = NULL;
    m_labSpeed = NULL;
    m_labTitle = NULL;
    m_labScore = NULL;
}

BasicInfoView::~BasicInfoView()
{
    
}

/*BasicInfoView *BasicInfoView::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("BasicInfoView", BasicInfoViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("FuzzyBgView", FuzzyBgViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("PlayerInfoView", PlayerInfoViewLoader::loader());
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/info.ccbi", pOwner);
    
    BasicInfoView *pInfoView = static_cast<BasicInfoView *>(pNode);
    pInfoView->m_pPlayerEquipInfoView = EquipInfoView::create(pInfoView);
    pInfoView->m_pPlayerEquipInfoView->sendPlayerEquipInfoRequest();
    return pInfoView;
}*/

cocos2d::SEL_MenuHandler BasicInfoView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", BasicInfoView::onMenuItemClicked);
    
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler BasicInfoView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", BasicInfoView::onCCControlButtonClicked);
    return NULL;
}

bool BasicInfoView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode){
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLaberTitle", cocos2d::CCLabelTTF * , this->mLaberTitle);
    return false;
}

void BasicInfoView::onMenuItemClicked(cocos2d::CCObject *pTarget){

}

void BasicInfoView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent){
    CCLog("onCCControlButtonClicked success!!!");
}

void BasicInfoView::showBasicView(){
    this->setVisible(true);
}

void BasicInfoView::hideBasicView(){
    this->setVisible(false);
}

void BasicInfoView::initBasicInfoView(){
    stActorUserInfo* info = PlayerInfoDataManager::sharedPlayerInfoDataManager()->getCurUserInfo();
    if(info == NULL){
        return;
    }
    cocos2d::CCString* strNickname = cocos2d::CCString::createWithFormat("名称：%s",info->userNickName.c_str());
    setBasicInfoLabelForTag(kNickNameInfo,strNickname);
    
    cocos2d::CCString* strLevel = cocos2d::CCString::createWithFormat("等级：%d",info->userLevel);
    setBasicInfoLabelForTag(kLevelInfo, strLevel);
    
    //info->userExp = root["meta"]["out"]["exp"].asInt();
    //setPlayerInfoLabelForTag(kLevelInfo, cocos2d::CCString::createWithFormat("%d",info->userExp));
    cocos2d::CCString* strHp = cocos2d::CCString::createWithFormat("H  P：%d",info->userHp);
    setBasicInfoLabelForTag(kHpInfo, strHp);
    
    cocos2d::CCString* strAttack = cocos2d::CCString::createWithFormat("攻击：%d",(int)info->userAttack);
    setBasicInfoLabelForTag(kAttackInfo, strAttack);
    
    cocos2d::CCString* strDefence = cocos2d::CCString::createWithFormat("防御：%d",(int)info->userReference);
    setBasicInfoLabelForTag(kRefenshInfo, strDefence);
    
    cocos2d::CCString* strSpeed = cocos2d::CCString::createWithFormat("速度：%d",(int)info->userSpeed);
    setBasicInfoLabelForTag(kSpeedInfo, strSpeed);
}

void BasicInfoView::setBasicInfoLabelForTag(const int tag, cocos2d::CCString *infomation){
    switch (tag) {
        case kNickNameInfo:
            m_labNickName = (cocos2d::CCLabelTTF*)this->getChildByTag(kNickNameInfo);
            m_labNickName->setString(infomation->getCString());
            break;
        case kLevelInfo:
            m_labLevel = (cocos2d::CCLabelTTF*)this->getChildByTag(kLevelInfo);
            m_labLevel->setString(infomation->getCString());
            break;
        case kHpInfo:
            m_labHP = (cocos2d::CCLabelTTF*)this->getChildByTag(kHpInfo);
            m_labHP->setString(infomation->getCString());
            break;
        case kAttackInfo:
            m_labAttack = (cocos2d::CCLabelTTF*)this->getChildByTag(kAttackInfo);
            m_labAttack->setString(infomation->getCString());
            break;
        case kRefenshInfo:
            m_labRefensh = (cocos2d::CCLabelTTF*)this->getChildByTag(kRefenshInfo);
            m_labRefensh->setString(infomation->getCString());
            break;
        case kSpeedInfo:
            m_labSpeed = (cocos2d::CCLabelTTF*)this->getChildByTag(kSpeedInfo);
            m_labSpeed->setString(infomation->getCString());
            break;
        case kTitleInfo:
            m_labTitle = (cocos2d::CCLabelTTF*)this->getChildByTag(kTitleInfo);
            m_labTitle->setString(infomation->getCString());
            break;
        case kScoreInfo:
            m_labScore = (cocos2d::CCLabelTTF*)this->getChildByTag(kScoreInfo);
            m_labScore->setString(infomation->getCString());
            break;
        default:
            break;
    }
}

//Send basic player information request
void BasicInfoView::sendBasicInfo(){
    NetManager::shareNetManager()->sendEx(kModeActor, kDoGetBasicInfo, callfuncND_selector(BasicInfoView::responesBasicInfo), this, "");
}

void BasicInfoView::responesBasicInfo(CCNode *pNode, void* data){
    if (data != NULL) {
        Json::Value root;
        Json::Reader reader;
        
        if(reader.parse(NetManager::shareNetManager()->processResponse(data), root)){
            stActorUserInfo* info = PlayerInfoDataManager::sharedPlayerInfoDataManager()->getCurUserInfo();
            if(info == NULL){
                return;
            }
            info->userNickName = root["meta"]["out"]["nickname"].asCString();
            //cocos2d::CCString* strNickname = cocos2d::CCString::createWithFormat("名称：%s",info->userNickName.c_str());
            //setBasicInfoLabelForTag(kNickNameInfo,strNickname);
            
            info->userLevel = root["meta"]["out"]["level"].asInt();
            //cocos2d::CCString* strLevel = cocos2d::CCString::createWithFormat("等级：%d",info->userLevel);
            //setBasicInfoLabelForTag(kLevelInfo, strLevel);
            
            //info->userExp = root["meta"]["out"]["exp"].asInt();
            //setPlayerInfoLabelForTag(kLevelInfo, cocos2d::CCString::createWithFormat("%d",info->userExp));
            info->userHp = root["meta"]["out"]["hp"].asInt();
            //cocos2d::CCString* strHp = cocos2d::CCString::createWithFormat("H  P：%d",info->userHp);
            //setBasicInfoLabelForTag(kHpInfo, strHp);
            
            info->userAttack = root["meta"]["out"]["attack"].asDouble();
            //cocos2d::CCString* strAttack = cocos2d::CCString::createWithFormat("攻击：%d",(int)info->userAttack);
            //setBasicInfoLabelForTag(kAttackInfo, strAttack);
            
            info->userReference = root["meta"]["out"]["defence"].asDouble();
            //cocos2d::CCString* strDefence = cocos2d::CCString::createWithFormat("防御：%d",(int)info->userReference);
            //setBasicInfoLabelForTag(kRefenshInfo, strDefence);
            
            info->userSpeed = root["meta"]["out"]["speed"].asDouble();
            //cocos2d::CCString* strSpeed = cocos2d::CCString::createWithFormat("速度：%d",(int)info->userSpeed);
            //setBasicInfoLabelForTag(kSpeedInfo, strSpeed);
            initBasicInfoView();
        }
    }
}


