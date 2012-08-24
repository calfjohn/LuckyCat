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
    m_EquipListView = NULL;
    m_selectedEquipData = NULL;
    m_selectedEquipListLabel = NULL;
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
bool EquipInfoView::initEquipListData(){
    if(m_vecEquipIds.empty()){
        return false;
    }
    
    int size = m_vecEquipIds.size();

    for (int i = 0; i<size; i++) {
        stActorUserEquipInfo *info = PlayerInfoDataManager::sharedPlayerInfoDataManager()->getUserEquipInfoForId(m_vecEquipIds[i]);
        
        switch (info->userEquipType) {
            case kEquipHead:
                m_EquipHeadInfos.push_back(*info);
                break;
            case kEquipHand:
                m_EquipHandInfos.push_back(*info);
                break;
            case kEquipBody:
                m_EquipBodyInfos.push_back(*info);
                break;
            case kEquipFoot:
                m_EquipFootInfos.push_back(*info);
                break;
            default:
                break;
        }
    }
    return true;
}

bool EquipInfoView::initEquipListView(EquipType type){
    
    CCArray* items = CCArray::create();
    switch (type) {
        case kEquipHead:
            for (int i = 0; i<m_EquipHeadInfos.size(); i++) {
                stActorUserEquipInfo *info = &(m_EquipHeadInfos[i]);
                CCLabelTTF* label;
                if (info->userEquipId == m_iEquipCurHeadId) {
                    info->userPutOn = true;
                    CCString *name = CCString::createWithFormat("%s(当前)",info->equipInfo->equipName.c_str());
                    label = CCLabelTTF::create(name->getCString(), "Arial", 15);
                }else{
                    label = CCLabelTTF::create(info->equipInfo->equipName.c_str(), "Arial", 15);
                }
                CCMenuItemLabel *item = CCMenuItemLabel::create(label, this, menu_selector(EquipInfoView::equipListMenuItemCallBack));
                float x = 150.0f / 2.0f;
                float y = i * 15.0f;
                item->setPosition(CCPointMake(x, y));
                item->setTag(i);
                items->addObject(item);
                if(i == 0){
                    m_selectedEquipData = info;
                    m_selectedEquipListLabel = item;
                    setEquipInfo(info->equipInfo);
                }
            }
            break;
        case kEquipHand:
            for (int i = 0; i<m_EquipHandInfos.size(); i++) {
                stActorUserEquipInfo *info = &(m_EquipHandInfos[i]);
                CCLabelTTF* label;
                if (info->userEquipId == m_iEquipCurHeadId) {
                    info->userPutOn = true;
                    CCString *name = CCString::createWithFormat("%s(当前)",info->equipInfo->equipName.c_str());
                    label = CCLabelTTF::create(name->getCString(), "Arial", 15);
                }else{
                    label = CCLabelTTF::create(info->equipInfo->equipName.c_str(), "Arial", 15);
                }
                CCMenuItemLabel *item = CCMenuItemLabel::create(label, this, menu_selector(EquipInfoView::equipListMenuItemCallBack));
                float x = 150.0f / 2.0f;
                float y = i * 15.0f;
                item->setPosition(CCPointMake(x, y));
                item->setTag(i);
                items->addObject(item);
                if(i == 0){
                    m_selectedEquipData = info;
                    m_selectedEquipListLabel = item;
                    setEquipInfo(info->equipInfo);
                }
            }
            break;
        case kEquipBody:
            for (int i = 0; i<m_EquipBodyInfos.size(); i++) {
                stActorUserEquipInfo *info = &(m_EquipBodyInfos[i]);
                CCLabelTTF* label;
                if (info->userEquipId == m_iEquipCurHeadId) {
                    info->userPutOn = true;
                    CCString *name = CCString::createWithFormat("%s(当前)",info->equipInfo->equipName.c_str());
                    label = CCLabelTTF::create(name->getCString(), "Arial", 15);
                }else{
                    label = CCLabelTTF::create(info->equipInfo->equipName.c_str(), "Arial", 15);
                }
                CCMenuItemLabel *item = CCMenuItemLabel::create(label, this, menu_selector(EquipInfoView::equipListMenuItemCallBack));
                float x = 150.0f / 2.0f;
                float y = i * 15.0f;
                item->setPosition(CCPointMake(x, y));
                item->setTag(i);
                items->addObject(item);
                if(i == 0){
                    m_selectedEquipData = info;
                    m_selectedEquipListLabel = item;
                    setEquipInfo(info->equipInfo);
                }
            }
            break;
        case kEquipFoot:
            for (int i = 0; i<m_EquipFootInfos.size(); i++) {
                stActorUserEquipInfo *info = &(m_EquipFootInfos[i]);
                CCLabelTTF* label;
                if (info->userEquipId == m_iEquipCurHeadId) {
                    info->userPutOn = true;
                    CCString *name = CCString::createWithFormat("%s(当前)",info->equipInfo->equipName.c_str());
                    label = CCLabelTTF::create(name->getCString(), "Arial", 15);
                }else{
                    label = CCLabelTTF::create(info->equipInfo->equipName.c_str(), "Arial", 15);
                }
                CCMenuItemLabel *item = CCMenuItemLabel::create(label, this, menu_selector(EquipInfoView::equipListMenuItemCallBack));
                float x = 150.0f / 2.0f;
                float y = i * 15.0f;
                item->setPosition(CCPointMake(x, y));
                item->setTag(i);
                items->addObject(item);
                if(i == 0){
                    m_selectedEquipData = info;
                    m_selectedEquipListLabel = item;
                    setEquipInfo(info->equipInfo);
                }
            }
            break;
        default:
            break;
    }
    CCMenu *menu = CCMenu::create(items);
    menu->setPosition(CCPointZero);
    
    
    CCLayer* layer = CCLayer::create();
    layer->setAnchorPoint(CCPointZero);
    layer->setPosition(CCPointZero);
    layer->setContentSize(CCSizeMake(150, 150));
    
    layer->addChild(menu);
    
    if (m_EquipListView != NULL) {
        m_EquipListView->removeAllChildrenWithCleanup(true);
        m_EquipListView = CCScrollView::create(CCSizeMake(150, 100),layer);
    }else{
        m_EquipListView = CCScrollView::create(CCSizeMake(150, 100),layer);
    }
    m_EquipListView->setPosition(CCPointMake(107, 137));
    //m_EquipListView->setContentOffset(CCPointMake(0, 137));
    
    //m_EquipListView->setContentSize(CCSizeMake(150, 100));
    //m_EquipListView->setContainer(layer);
    
    // 设置滚屏属性
    m_EquipListView->setDirection(CCScrollViewDirectionVertical);
    m_EquipListView->setDelegate(this);
    m_EquipListView->setTouchEnabled(true);
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
    /*CCMenuItemLabel* item = (CCMenuItemLabel*)pSender;
    CCLabelTTF* label = (CCLabelTTF*)item->getLabel();
    CCString* name = CCString::createWithFormat("%s(当前)",label->getString());
    item->setString(name->getCString());*/
    
    stActorUserEquipInfo *info;
    int index = pSender->getTag();
    m_selectedEquipListLabel = (CCMenuItemLabel*)pSender;
    switch (m_curEquipType) {
        case kEquipHead:
            info = &(m_EquipHeadInfos[index]);
            break;
        case kEquipHand:
            info = &(m_EquipHandInfos[index]);
            break;
        case kEquipBody:
            info = &(m_EquipBodyInfos[index]);
            break;
        case kEquipFoot:
            info = &(m_EquipFootInfos[index]);
            break;
        default:
            break;
    }
    m_selectedEquipData = info;
    setEquipInfo(info->equipInfo);
}

void EquipInfoView::setEquipInfo(const stActorEquipInfo *info){
    CCPoint point;

    if (!info->equipName.empty()) {
        m_labEquipName = (CCLabelTTF*)this->getChildByTag(11);
        m_labEquipName->setString(info->equipName.c_str());
    }
    if (info->equipAttack != 0) {
        m_labEquipAttack = (CCLabelTTF*)this->getChildByTag(12);
        CCString *attack = CCString::createWithFormat("%d",info->equipAttack);
        m_labEquipAttack->setString(attack->getCString());
    }else if(info->equipDefence != 0 ){
        m_labEquipAttack = (CCLabelTTF*)this->getChildByTag(12);
        CCString *attack = CCString::createWithFormat("%d",info->equipDefence);
        m_labEquipAttack->setString(attack->getCString());
    }else if(info->equipSpeed != 0 ){
        m_labEquipAttack = (CCLabelTTF*)this->getChildByTag(12);
        CCString *attack = CCString::createWithFormat("%d",info->equipSpeed);
        m_labEquipAttack->setString(attack->getCString());
    }else if(info->equipLife != 0) {
        m_labEquipAttack = (CCLabelTTF*)this->getChildByTag(12);
        CCString *attack = CCString::createWithFormat("%d",info->equipLife);
        m_labEquipAttack->setString(attack->getCString());
    }
    CCMenu* menu = (CCMenu*)this->getChildByTag(kEquipMenu);
    if (m_selectedEquipData->userPutOn) {
        CCMenuItemImage *puton = (CCMenuItemImage*)menu->getChildByTag(kEquipPutOn);
        puton->setEnabled(false);
        CCLabelTTF *pstring = (CCLabelTTF*)this->getChildByTag(kEquipFontPutOn);
        pstring->setVisible(false);
        
        CCMenuItemImage *takeoff = (CCMenuItemImage*)menu->getChildByTag(kEquipTakeOff);
        takeoff->setEnabled(true);
        CCLabelTTF *tstring = (CCLabelTTF*)this->getChildByTag(kEquipFontTakeOff);
        tstring->setVisible(true);
    }else{
        CCMenuItemImage *puton = (CCMenuItemImage*)menu->getChildByTag(kEquipPutOn);
        puton->setEnabled(true);
        CCLabelTTF *pstring = (CCLabelTTF*)this->getChildByTag(kEquipFontPutOn);
        pstring->setVisible(true);
        
        CCMenuItemImage *takeoff = (CCMenuItemImage*)menu->getChildByTag(kEquipTakeOff);
        takeoff->setEnabled(false);
        CCLabelTTF *tstring = (CCLabelTTF*)this->getChildByTag(kEquipFontTakeOff);
        tstring->setVisible(false);
    }
    
}


void EquipInfoView::showEquipView(){
    this->setVisible(true);
}

void EquipInfoView::hideEquipView(){
    this->setVisible(false);
}


/*
void EquipInfoView::setEquipInfo(cocos2d::CCSprite *equipIcon, cocos2d::CCLabelTTF *equipName, std::vector<cocos2d::CCLabelTTF> &equipProprety){
    
}
*/

void EquipInfoView::sendPlayerEquipInfo(){
    NetManager::shareNetManager()->sendEx(kModeActor, kDoGetAllEquipment, callfuncND_selector(EquipInfoView::responsePlayerEquipInfo), this, "");
}

void EquipInfoView::responsePlayerEquipInfo(CCNode *pNode, void* data){
    if(!m_vecEquipIds.empty()){
        m_vecEquipIds.clear();
    }
    Json::Value root;
    Json::Reader reader;
    
    if(reader.parse(NetManager::shareNetManager()->processResponse(data), root)){
        Json::Value out = root["meta"]["out"];
        for(int i = 0;i<out.size();i++){
            //std::cout << "i = " << i << " " << out[i]["equip_id"].asInt() << std::endl;
            m_vecEquipIds.push_back(out[i]["equip_id"].asInt());
        }
    }
    initEquipListData();
    sendPlayerCurEquipInfo();
}

void EquipInfoView::sendPlayerCurEquipInfo(){
    NetManager::shareNetManager()->sendEx(kModeActor, kDoGetEquippedEquipment, callfuncND_selector(EquipInfoView::responsePlayerCurEquipInfo), this, "");
}

void EquipInfoView::responsePlayerCurEquipInfo(CCNode *pNode, void* data){
    Json::Value root;
    Json::Reader reader;
    
    if(reader.parse(NetManager::shareNetManager()->processResponse(data), root)){
        Json::Value out = root["meta"]["out"];
        m_iEquipCurHeadId = out["eq_head_id"]["id"].asInt();
        if (m_iEquipCurHeadId != -1) {
            m_iEquipCurHeadId = out["eq_head_id"]["equip_id"].asInt();
        }
        m_iEquipCurBodyId = out["eq_body_id"]["id"].asInt();
        if (m_iEquipCurBodyId != -1) {
            m_iEquipCurBodyId = out["eq_head_id"]["equip_id"].asInt();
        }
        m_iEquipCurHandId = out["eq_hand_id"]["id"].asInt();
        if (m_iEquipCurHandId != -1) {
            m_iEquipCurHandId = out["eq_head_id"]["equip_id"].asInt();
        }
        m_iEquipCurFootId = out["eq_foot_id"]["id"].asInt();
        if (m_iEquipCurFootId != -1) {
            m_iEquipCurFootId = out["eq_head_id"]["equip_id"].asInt();
        }
    }
    initEquipListView(kEquipHead);
}

void EquipInfoView::sendResetCurEquip(){
    if (m_selectedEquipData == NULL)
        return;
    if (m_selectedEquipData->userPutOn) {
        NetManager::shareNetManager()->sendEx(kModeActor, kDoChangeEquipmentInfo, callfuncND_selector(EquipInfoView::responseTakeOffCurEquip), this, "\"part\":%d,\"id\":%d",m_selectedEquipData->userEquipType,-1);
    }else{
        cout << m_selectedEquipData->userEquipType << " " << m_selectedEquipData->userEquipId << endl;
        NetManager::shareNetManager()->sendEx(kModeActor, kDoChangeEquipmentInfo, callfuncND_selector(EquipInfoView::responsePutOnCurEquip), this, "\"part\":%d,\"id\":%d",m_selectedEquipData->userEquipType,m_selectedEquipData->userEquipId);
    }
}

void EquipInfoView::responsePutOnCurEquip(CCNode *pNode, void* data){
    m_selectedEquipData->userPutOn = true;
    
    CCMenu *menu = (CCMenu*)this->getChildByTag(kEquipMenu);
    
    CCMenuItemImage *puton = (CCMenuItemImage*)menu->getChildByTag(kEquipPutOn);
    puton->setEnabled(false);
    CCLabelTTF *pstring = (CCLabelTTF*)this->getChildByTag(kEquipFontPutOn);
    pstring->setVisible(false);
    
    CCMenuItemImage *takeoff = (CCMenuItemImage*)menu->getChildByTag(kEquipTakeOff);
    takeoff->setEnabled(true);
    CCLabelTTF *tstring = (CCLabelTTF*)this->getChildByTag(kEquipFontTakeOff);
    tstring->setVisible(true);
    
    
    CCLabelTTF *label = (CCLabelTTF*)m_selectedEquipListLabel->getLabel();
    CCString *name = CCString::createWithFormat("%s(当前)",label->getString());
    m_selectedEquipListLabel->setString(name->getCString());
}

void EquipInfoView::responseTakeOffCurEquip(CCNode *pNode, void* data){
    m_selectedEquipData->userPutOn = false;
    
    CCMenu *menu = (CCMenu*)this->getChildByTag(kEquipMenu);
    
    CCMenuItemImage *puton = (CCMenuItemImage*)menu->getChildByTag(kEquipPutOn);
    puton->setEnabled(true);
    CCLabelTTF *pstring = (CCLabelTTF*)this->getChildByTag(kEquipFontPutOn);
    pstring->setVisible(true);
    
    CCMenuItemImage *takeoff = (CCMenuItemImage*)menu->getChildByTag(kEquipTakeOff);
    takeoff->setEnabled(false);
    CCLabelTTF *tstring = (CCLabelTTF*)this->getChildByTag(kEquipFontTakeOff);
    tstring->setVisible(false);
    
    //CCString *name =
    CCLabelTTF *label = CCLabelTTF::create(m_selectedEquipData->equipInfo->equipName.c_str(), "Arial", 15);
    m_selectedEquipListLabel->setLabel(label);
}




