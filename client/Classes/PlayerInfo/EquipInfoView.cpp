//
//  EquipInfoView.cpp
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-16.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "Basic.h"
#include "EquipInfoView.h"
#include "FuzzyBgView.h"
#include "NetManager.h"
#include "PlayerInfoView.h"
#include "PlayerInfoDataManager.h"
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

void EquipInfoView::scrollViewDidScroll(CCScrollView* view){

}

void EquipInfoView::scrollViewDidZoom(CCScrollView* view){

}

void EquipInfoView::onEnter(){
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

void EquipInfoView::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

bool EquipInfoView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    return true;
}

void EquipInfoView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    cout << "move" << endl;
}

void EquipInfoView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){

}

void EquipInfoView::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){

}

bool EquipInfoView::initEquipListView(){
    
    int size = PlayerInfoDataManager::sharedPlayerInfoDataManager()->getUserEquipInfoCount();
    
    CCArray* items = CCArray::create();
    for (int i = 0; i<size; i++) {
        stActorUserEquipInfo *info = PlayerInfoDataManager::sharedPlayerInfoDataManager()->getUserEquipInfo(i);
        CCMenuItemFont *item = CCMenuItemFont::create(info->equipInfo->equipName.c_str(), this, menu_selector(EquipInfoView::equipListMenuItemCallBack));
        float x = 150.0f / 2.0f;
        float y = i * 15.0f;
        item->setPosition(CCPointMake(x, y));
        item->setFontSizeObj(15);
        item->setTag(100+i);
        items->addObject(item);
    }
    CCMenu *menu = CCMenu::menuWithArray(items);
    menu->setPosition(CCPointZero);
    
    m_EquipListView = CCScrollView::create();
    CCLayer* layer = CCLayer::create();
    layer->setAnchorPoint(CCPointZero);
    layer->setPosition(CCPointZero);
    
    layer->addChild(menu);
    
    m_EquipListView->setPosition(CCPointMake(107, 137));
    m_EquipListView->setContentOffset(CCPointZero);
    layer->setContentSize(CCSizeMake(150, 150));
    m_EquipListView->setContentSize(CCSizeMake(150, 100));
    m_EquipListView->setContainer(layer);
    
    // 设置滚屏属性
    m_EquipListView->setDirection(CCScrollViewDirectionVertical);
    m_EquipListView->setDelegate(this);
    //m_EquipListView->scrollsToTop();
    
    this->addChild(m_EquipListView);
    
    return true;
}

void EquipInfoView::EquipViewBtnCallback(cocos2d::CCObject *pTarget){
    CCNode* node = (CCNode*)pTarget;
    cout << node->getTag() << endl;
    switch (node->getTag()) {
        case kEquipPutOn:
            sendResetCurEquip();
            break;
        case kEquipTakeOff:
            sendResetCurEquip();
            break;
        default:
            break;
    }
}

void EquipInfoView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent){

}

void EquipInfoView::equipListMenuItemCallBack(CCNode *pSender){
    /*CCMenuItemFont* item = (CCMenuItemFont*)pSender;
    CCString* name = CCString::createWithFormat("%s\"(当前)\"",item->fontNameObj());
    CCLog("%s",name->getCString());
    item->setFontNameObj(name->getCString());*/
    int index = pSender->getTag();
    stActorUserEquipInfo* info = PlayerInfoDataManager::sharedPlayerInfoDataManager()->getUserEquipInfo(index-100);
    m_selectedEquipData = info;
    setEquipInfo(info->equipInfo);
}

void EquipInfoView::setEquipInfo(const stActorEquipInfo *info){
    CCPoint point;

    if (!info->equipName.empty()) {
        m_labEquipName = (CCLabelTTF*)this->getChildByTag(7);
        m_labEquipName->setString(info->equipName.c_str());
    }
    if (info->equipAttack != 0) {
        m_labEquipAttack = (CCLabelTTF*)this->getChildByTag(8);
        CCString *attack = CCString::createWithFormat("%d",info->equipAttack);
        m_labEquipAttack->setString(attack->getCString());
    }else if(info->equipDefence != 0 ){
        m_labEquipAttack = (CCLabelTTF*)this->getChildByTag(8);
        CCString *attack = CCString::createWithFormat("%d",info->equipDefence);
        m_labEquipAttack->setString(attack->getCString());
    }else if(info->equipSpeed != 0 ){
        m_labEquipAttack = (CCLabelTTF*)this->getChildByTag(8);
        CCString *attack = CCString::createWithFormat("%d",info->equipSpeed);
        m_labEquipAttack->setString(attack->getCString());
    }else if(info->equipLife != 0) {
        m_labEquipAttack = (CCLabelTTF*)this->getChildByTag(8);
        CCString *attack = CCString::createWithFormat("%d",info->equipLife);
        m_labEquipAttack->setString(attack->getCString());
    }
    
    if (m_selectedEquipData->userPutOn) {
        CCMenuItemImage *puton = (CCMenuItemImage*)this->getChildByTag(1);
        puton->setEnabled(false);
        CCLabelTTF *pstring = (CCLabelTTF*)this->getChildByTag(12);
        pstring->setVisible(false);
        
        CCMenuItemImage *takeoff = (CCMenuItemImage*)this->getChildByTag(1);
        takeoff->setEnabled(true);
        CCLabelTTF *tstring = (CCLabelTTF*)this->getChildByTag(12);
        tstring->setVisible(true);
    }else{
        CCMenuItemImage *puton = (CCMenuItemImage*)this->getChildByTag(1);
        puton->setEnabled(true);
        CCLabelTTF *pstring = (CCLabelTTF*)this->getChildByTag(12);
        pstring->setVisible(true);
        
        CCMenuItemImage *takeoff = (CCMenuItemImage*)this->getChildByTag(1);
        takeoff->setEnabled(false);
        CCLabelTTF *tstring = (CCLabelTTF*)this->getChildByTag(12);
        tstring->setVisible(false);
    }
    
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

void EquipInfoView::sendResetCurEquip(){
    if (m_selectedEquipData == NULL)
        return;
    if (m_selectedEquipData->userPutOn) {
        NetManager::shareNetManager()->sendEx(kModeActor, kDoChangeEquipmentInfo, callfuncND_selector(EquipInfoView::responseTakeOffCurEquip), this, "\"part\":%d,\"id\":%d",m_selectedEquipData->userEquipType,-1);
    }else{
        NetManager::shareNetManager()->sendEx(kModeActor, kDoChangeEquipmentInfo, callfuncND_selector(EquipInfoView::responsePutOnCurEquip), this, "\"part\":%d,\"id\":%d",m_selectedEquipData->userEquipType,m_selectedEquipData->userEquipId);
    }
}

void EquipInfoView::responsePutOnCurEquip(CCNode *pNode, void* data){
    m_selectedEquipData->userPutOn = true;
    
    CCMenuItemImage *puton = (CCMenuItemImage*)this->getChildByTag(1);
    puton->setEnabled(false);
    CCLabelTTF *pstring = (CCLabelTTF*)this->getChildByTag(12);
    pstring->setVisible(false);
    
    CCMenuItemImage *takeoff = (CCMenuItemImage*)this->getChildByTag(1);
    takeoff->setEnabled(true);
    CCLabelTTF *tstring = (CCLabelTTF*)this->getChildByTag(12);
    tstring->setVisible(true);
}

void EquipInfoView::responseTakeOffCurEquip(CCNode *pNode, void* data){
    m_selectedEquipData->userPutOn = false;
    
    CCMenuItemImage *puton = (CCMenuItemImage*)this->getChildByTag(1);
    puton->setEnabled(true);
    CCLabelTTF *pstring = (CCLabelTTF*)this->getChildByTag(12);
    pstring->setVisible(true);
    
    CCMenuItemImage *takeoff = (CCMenuItemImage*)this->getChildByTag(1);
    takeoff->setEnabled(false);
    CCLabelTTF *tstring = (CCLabelTTF*)this->getChildByTag(12);
    tstring->setVisible(false);
}




