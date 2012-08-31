//
//  PKListViewCell.cpp
//  LuckyCat
//
//  Created by Cocos2d-x on 12-8-31.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "PKListViewCell.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

PKListViewCell::PKListViewCell(){
    m_userName = NULL;
    m_userLevel = NULL;
    m_userId = 0;
    
}
PKListViewCell::~PKListViewCell(){

}

CCNode* PKListViewCell::createNodeForCCBI(const char *pCCBFileName , const char *pCCNodeName , cocos2d::extension::CCNodeLoader *pCCNodeLoader){
    /* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("PKListViewCell", PKListViewCellLoader::loader());
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

PKListViewCell *PKListViewCell::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("PKListViewCell", PKListViewCellLoader::loader());
    //ccNodeLoaderLibrary->registerCCNodeLoader("FuzzyBgView", FuzzyBgViewLoader::loader());
    //ccNodeLoaderLibrary->registerCCNodeLoader("PlayerInfoView", PlayerInfoViewLoader::loader());
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/pklist_scroll.ccbi", pOwner);
    
    PKListViewCell *pCellView = static_cast<PKListViewCell *>(pNode);
    
    return pCellView;
}

cocos2d::SEL_MenuHandler PKListViewCell::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "pkCellMenuCallback", PKListViewCell::pkCellMenuCallback);
    
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler PKListViewCell::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", PKListViewCell::onCCControlButtonClicked);
    return NULL;
}

bool PKListViewCell::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode){
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLaberTitle", cocos2d::CCLabelTTF * , this->mLaberTitle);
    return false;
}

void PKListViewCell::onMenuItemClicked(cocos2d::CCObject *pTarget){
    
}

void PKListViewCell::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent){
    CCLog("onCCControlButtonClicked success!!!");
}

void PKListViewCell::setCellUserNickName(const char *pUserName){
    if (m_userName == NULL) {
        m_userName = (CCLabelTTF*)this->getChildByTag(kPKListNickName);
    }
    m_userName->setString(pUserName);
}
void PKListViewCell::setCellUserLevel(int level){
    if (m_userLevel == NULL) {
        m_userLevel = (CCLabelTTF*)this->getChildByTag(kPKListLevel);
    }
    CCString *strLevel = CCString::createWithFormat("%d",level);
    m_userLevel->setString(strLevel->getCString());
}
void PKListViewCell::setCellUserId(int userId){
    m_userId = userId;
}

void PKListViewCell::pkCellMenuCallback(CCObject *pSender){
    cout << m_userId << endl;
}