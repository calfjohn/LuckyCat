//
//  EquipInfoView.cpp
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-16.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "EquipInfoView.h"
#include "FuzzyBgView.h"
#include "NetManager.h"
#include "PlayerInfoView.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"


EquipInfoView::EquipInfoView(){
    
}

EquipInfoView::~EquipInfoView(){

}

/*EquipInfoView * EquipInfoView::create(cocos2d::CCObject * pOwner){
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("EquipInfoView", EquipInfoViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("FuzzyBgView", FuzzyBgViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("PlayerInfoView", PlayerInfoViewLoader::loader());
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/equip.ccbi", pOwner);
    
    EquipInfoView *pEquipView = static_cast<EquipInfoView *>(pNode);
    return pEquipView;
}*/

cocos2d::SEL_MenuHandler EquipInfoView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "EquipViewBtnCallback", EquipInfoView::EquipViewBtnCallback);
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler EquipInfoView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", EquipInfoView::onCCControlButtonClicked);
    return NULL;
}

bool EquipInfoView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode){
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLaberTitle", cocos2d::CCLabelTTF * , this->mLaberTitle);
    return false;
}

void EquipInfoView::EquipViewBtnCallback(cocos2d::CCObject *pTarget){
    CCNode* node = (CCNode*)pTarget;
    cout << node->getTag() << endl;
}

void EquipInfoView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent){

}

void EquipInfoView::showEquipView(){
    this->setVisible(true);
}

void EquipInfoView::hideEquipView(){
    this->setVisible(false);
}

void EquipInfoView::setEquipInfoForType(EquipType type){
    if(type < 0 ){
        return;
    }
    switch (type) {
        case kEquipHelmet:
            
            break;
        case kEquipArms:
            
            break;
        case kEquipArmor:
            
            break;
        case kEquipShoes:
            
            break;
        default:
            break;
    }
}

/*
void EquipInfoView::setEquipInfo(cocos2d::CCSprite *equipIcon, cocos2d::CCLabelTTF *equipName, std::vector<cocos2d::CCLabelTTF> &equipProprety){
    
}
*/

void EquipInfoView::setPlayerEquipInfoForType(EquipType type){
    
}

void EquipInfoView::sendPlayerEquipInfo(){
    NetManager::shareNetManager()->sendEx(kModeActor, kDoGetEquipmentInfo, callfuncND_selector(EquipInfoView::responsePlayerEquipInfo), this, "\"part\":%d",0);
}

void EquipInfoView::responsePlayerEquipInfo(CCNode *pNode, void* data){
    Json::Value root;
    Json::Reader reader;
    
    if(reader.parse(NetManager::shareNetManager()->processResponse(data), root)){
        Json::Value out = root["meta"]["out"];
        for(int i = 0;i<out.size();i++){
            //std::cout << "i = " << i << " " << out[i]["equip_id"].asInt() << std::endl;
        }
    }
}


