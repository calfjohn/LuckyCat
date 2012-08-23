/*
 * =====================================================================================
 *
 *       Filename:  PlayerInfoView.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/7/30 17:13:50
 *       Revision:  none
 *
 *         Author:  lihex (lhx), hexuan.li@cocos2d-x.org
 *
 *    Copyright (c) 2012 厦门雅基软件有限公司. All rights reserved.
 *
 * =====================================================================================
 */

#include "Basic.h"
#include "PlayerInfoView.h"
#include "BasicInfoView.h"
#include "EquipInfoView.h"
#include "LuckySprite.h"
#include "FuzzyBgView.h"
#include "PlayerInfoDataManager.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

USING_NS_CC;
USING_NS_CC_EXT;


PlayerInfoView::PlayerInfoView(){

}
PlayerInfoView::~PlayerInfoView(){

}

CCNode* PlayerInfoView::createNodeForCCBI(const char *pCCBFileName , const char *pCCNodeName , cocos2d::extension::CCNodeLoader *pCCNodeLoader){
    /* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("PlayerInfoView", PlayerInfoViewLoader::loader());
    if(pCCNodeName != NULL && pCCNodeLoader != NULL) {
        ccNodeLoaderLibrary->registerCCNodeLoader(pCCNodeName, pCCNodeLoader);
    }
    
    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    /* Read a ccbi file. */
    // Load the scene from the ccbi-file, setting this class as
    // the owner will cause lblTestTitle to be set by the CCBReader.
    // lblTestTitle is in the TestHeader.ccbi, which is referenced
    // from each of the test scenes.
    CCNode * node = ccbReader->readNodeGraphFromFile("pub/", pCCBFileName, this);
    return node;
}

PlayerInfoView * PlayerInfoView::create(cocos2d::CCObject * pOwner){
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("PlayerInfoView", PlayerInfoViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("FuzzyBgView", FuzzyBgViewLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/playerinfo.ccbi", pOwner);
    
    PlayerInfoView *pPlayerInfoView = static_cast<PlayerInfoView *>(pNode);
    
    PlayerInfoDataManager *info = PlayerInfoDataManager::sharedPlayerInfoDataManager();
    
    pPlayerInfoView->m_pBasicInfoView = (BasicInfoView*)pPlayerInfoView->createNodeForCCBI("ccb/basic.ccbi", "BasicInfoView", BasicInfoViewLoader::loader());
    if (pPlayerInfoView->m_pBasicInfoView != NULL) {
        pPlayerInfoView->m_pBasicInfoView->setTag(kPlayerInfoTagBasicLayer);
        pPlayerInfoView->addChild(pPlayerInfoView->m_pBasicInfoView);
        pPlayerInfoView->m_pBasicInfoView->sendBasicInfo();
    }
    pPlayerInfoView->m_pEquipInfoView = (EquipInfoView*)pPlayerInfoView->createNodeForCCBI("ccb/equip.ccbi", "EquipInfoView", EquipInfoViewLoader::loader());
    if (pPlayerInfoView->m_pEquipInfoView != NULL) {
        pPlayerInfoView->m_pEquipInfoView->setTag(kPlayerInfoTagEquipLayer);
        pPlayerInfoView->addChild(pPlayerInfoView->m_pEquipInfoView);
        pPlayerInfoView->m_pEquipInfoView->sendPlayerEquipInfo();
        pPlayerInfoView->m_pEquipInfoView->initEquipListView();
    }
    if (pPlayerInfoView->m_pBasicInfoView != NULL && pPlayerInfoView->m_pEquipInfoView != NULL) {
        pPlayerInfoView->m_iType = kPlayerInfoTagPlayerBtn;
        pPlayerInfoView->showViewForType();
    }
    
    if (pPlayerInfoView)
    {
        CCNode *pBgNode = pPlayerInfoView->getChildByTag(901);
        pPlayerInfoView->registerTouchNode(pBgNode);
        
        if (pPlayerInfoView->m_pBasicInfoView)
        {
            CCNode *pBgNode = pPlayerInfoView->m_pBasicInfoView->getChildByTag(902);
            CCNode *pBgTitleNode = pPlayerInfoView->m_pBasicInfoView->getChildByTag(903);
            pPlayerInfoView->registerTouchNode(pBgNode);
            pPlayerInfoView->registerTouchNode(pBgTitleNode);
        }
        
        pPlayerInfoView->setIsTouchAreaEnabled(true);
    }
    return pPlayerInfoView;
}



cocos2d::SEL_MenuHandler PlayerInfoView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", PlayerInfoView::onMenuItemClicked);
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler PlayerInfoView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "PlayerInfoBarBtnCallback", PlayerInfoView::playerInfoBarBtnCallback);
    return NULL;
}


bool PlayerInfoView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode){
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLaberTitle", cocos2d::CCLabelTTF * , this->mLaberTitle);
    return false;
}



void PlayerInfoView::onMenuItemClicked(cocos2d::CCObject *pTarget){
    
}


void PlayerInfoView::playerInfoBarBtnCallback(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent){
    CCNode* btn = (CCNode*)pSender;
    //cout << btn->getTag() << endl;
    switch (btn->getTag()) {
        case kPlayerInfoTagPlayerBtn:
            m_iType = kPlayerInfoTagPlayerBtn;
            showViewForType();
            break;
        case kPlayerInfoTagHeadBtn:
            m_iType = kPlayerInfoTagHeadBtn;
            showViewForType();
            break;
        case kPlayerInfoTagArmsBtn:
            m_iType = kPlayerInfoTagArmsBtn;
            showViewForType();
            break;
        case kPlayerInfoTagClothseBtn:
            m_iType = kPlayerInfoTagClothseBtn;
            showViewForType();
            break;
        case kPlayerInfoTagShoesBtn:
            m_iType = kPlayerInfoTagShoesBtn;
            showViewForType();
            break;
        default:
            break;
    }
}

void PlayerInfoView::showViewForType(){
    if(m_iType < 0){
        CCLog("cur type is null");
        return;
    }
    
    if(m_iType > kPlayerInfoTagPlayerBtn ){
        m_pBasicInfoView->hideBasicView();
        m_pEquipInfoView->showEquipView();
    }else{
        m_pBasicInfoView->showBasicView();
        m_pEquipInfoView->hideEquipView();
    }
}

void PlayerInfoView::notificationTouchEvent(LTouchEvent tLTouchEvent)
{
    if (tLTouchEvent == kLTouchEventOutsideTouchArea) {
        removeFromParentAndCleanup(true);
        CCLog("kLTouchEvent OutsideTouchArea");
    }
    else if (tLTouchEvent == kLTouchEventInsideTouchArea)
    {
        CCLog("kLTouchEvent InsideTouchArea");
    }
    else {
        CCLog("kLTouchEvent Other...");
    }
}

void PlayerInfoView::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 10 , true);
}
