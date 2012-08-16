//
//  PlayerInfoView.cpp
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-14.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "PlayerInfoView.h"
#include "EquipInfoView.h"
#include "FuzzyBgView.h"
#include "NetManager.h"
#include "json.h"
#include "CCNetwork.h"
#include "CCCallbackNode.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;
enum PlayerInfoTag{
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

PlayerInfoView::PlayerInfoView()
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

PlayerInfoView::~PlayerInfoView()
{
    
}

PlayerInfoView *PlayerInfoView::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("PlayerInfoView", PlayerInfoViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("FuzzyBgView", FuzzyBgViewLoader::loader());
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/info.ccbi", pOwner);
    
    PlayerInfoView *pInfoView = static_cast<PlayerInfoView *>(pNode);
    
    return pInfoView;
}

cocos2d::SEL_MenuHandler PlayerInfoView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", PlayerInfoView::onMenuItemClicked);
    
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler PlayerInfoView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", PlayerInfoView::onCCControlButtonClicked);
    return NULL;
}

bool PlayerInfoView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode){
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLaberTitle", cocos2d::CCLabelTTF * , this->mLaberTitle);
    return false;
}

void PlayerInfoView::onMenuItemClicked(cocos2d::CCObject *pTarget){

}

void PlayerInfoView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent){
    CCLog("onCCControlButtonClicked success!!!");
}

void PlayerInfoView::setPlayerInfoLabelForTag(const int tag, cocos2d::CCString *infomation){
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
void PlayerInfoView::sendPlayerInfo(){
    NetManager::shareNetManager()->send(kModeActor, kDoGetBasicInfo, callfuncND_selector(PlayerInfoView::responesPlayerInfo), this, NULL);
}

void PlayerInfoView::responesPlayerInfo(CCNode *pNode, void* data){
    if (data != NULL) {
        Json::Value root;
        Json::Reader reader;
        
        ccnetwork::RequestInfo *info = (ccnetwork::RequestInfo *)data;
        //std::string strData = info->strResponseData;
        if(reader.parse(info->strResponseData, root)){
            std::string nickname = root["meta"]["out"]["nickname"].asCString();
            cocos2d::CCString* strNickname = cocos2d::CCString::createWithFormat("名称：%s",nickname.c_str());
            setPlayerInfoLabelForTag(kNickNameInfo,strNickname);
            int level = root["meta"]["out"]["level"].asInt();
            cocos2d::CCString* strLevel = cocos2d::CCString::createWithFormat("等级：%d",level);
            setPlayerInfoLabelForTag(kLevelInfo, strLevel);
            //int exp = root["meta"]["out"]["exp"].asInt();
            //setPlayerInfoLabelForTag(kLevelInfo, cocos2d::CCString::createWithFormat("%d",exp));
            int hp = root["meta"]["out"]["hp"].asInt();
            cocos2d::CCString* strHp = cocos2d::CCString::createWithFormat("H  P：%d",hp);
            setPlayerInfoLabelForTag(kHpInfo, strHp);
        }
    }
}


