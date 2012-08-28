//
//  OpenBoxView.cpp
//  LuckyCat
//
//  Created by XiaoZhong Zhu on 12-8-10.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "OpenBoxView.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"
#include "EventDataManager.h"
#include "EventBasic.h"
#include "LuckySprite.h"
#include "OpenBoxResultView.h"
#include "NetManager.h"
#include "CCMessageQueue.h"
#include "json/json.h"

#include "FuzzyBgView.h"

#define TAG_BUTTON_OPEN_BOX 11

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

OpenBoxView::OpenBoxView():m_bIsOpen(false)
{
    
}

OpenBoxView::~OpenBoxView()
{
    
}

OpenBoxView *OpenBoxView::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("FuzzyBgView", FuzzyBgViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("OpenBoxView", OpenBoxViewLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/openbox.ccbi", pOwner);
    
    OpenBoxView *pOpenBoxView = static_cast<OpenBoxView *>(pNode);
    return pOpenBoxView;
}

cocos2d::SEL_MenuHandler OpenBoxView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", OpenBoxView::onMenuItemClicked);
    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler OpenBoxView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", OpenBoxView::onCCControlButtonClicked );
    return NULL;
}
bool OpenBoxView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode)
{
    return false;
}

void OpenBoxView::onMenuItemClicked(cocos2d::CCObject *pTarget)
{
    
}

void OpenBoxView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
//    if ( m_bIsOpen == false && p_CurEvent->m_bBoxIsOpened == false && p_CurEvent && p_CurEvent->box_id != -1)
//    {
//        m_bIsOpen = true;
//        
//        char strChar[100];
//        sprintf(strChar,"\"EventId\": %d,\"boxId\": %d" ,p_CurEvent->id, p_CurEvent->box_id);
//        NetManager::shareNetManager()->send(kModeBox, kDoOpenBox,                                      callfuncND_selector(OpenBoxView::netCallBack), this, strChar);
//    }
//    else {
//        if ( m_target && m_pfnSelector )
//            ((m_target)->*(m_pfnSelector))(this, NULL);
//    }
    if ( m_bIsOpen == false && p_CurEvent->m_bBoxIsOpened == false && p_CurEvent && p_CurEvent->box_id != -1)
    {
        OpenBoxResultView *pOpenBoxResult = OpenBoxResultView::create(this);
        pOpenBoxResult->initView(p_CurEvent->boxAward);
        this->addChild(pOpenBoxResult,99);
        
        m_bIsOpen = true;
        
        CCControlButton *pControlButton = static_cast<CCControlButton *>(this->getChildByTag(TAG_BUTTON_OPEN_BOX));
        if (pControlButton)
        {
            pControlButton->setEnabled(false);
        }
        
        
        if (p_CurEvent)
        {
            p_CurEvent->m_bBoxIsOpened = true;
        }
    }else {
        if ( m_target && m_pfnSelector )
            ((m_target)->*(m_pfnSelector))(this, NULL);
    }
}

void OpenBoxView::setSelector(cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector)
{
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    pBeginPoint = CCPointZero;
    this->setTouchEnabled(true);
}

void OpenBoxView::setEvent(LEventData *t)
{
    p_CurEvent = t;
}

void OpenBoxView::netCallBack(CCNode* pNode, void* data)
{    
    if ( data )
    {
        if ( pNode->getTag() == TAG_BUTTON_OPEN_BOX )
        {
            CCControlButton *pButton = (CCControlButton *)pNode;
            pButton->cocos2d::extension::CCControl::setSelected(true);
        }
        ccnetwork::RequestInfo *tempInfo = static_cast<ccnetwork::RequestInfo *>(data);
        
        vector<stGood> tGoodsList;
        
        Json::Reader reader;
        Json::Value json_root;
        if (!reader.parse(tempInfo->strResponseData.c_str(), json_root))
            return;
        //
        Json::Value json_meta = json_root["meta"];
        Json::Value json_out = json_meta["out"];
        
        int ret = json_out["result"].asInt();
        if ( ret != 0 )
        {
            //open box failed. the box id is not exit. alert player.
            m_bIsOpen = false;
            return;
        }
        Json::Value json_goodsArray = json_out["goodsArray"];
        
        for (int i = 0; i < json_goodsArray.size(); i++) {
            Json::Value goods = json_goodsArray[i];
            stGood tmpGoods;
            tmpGoods.id = goods["id"].asInt();
            tmpGoods.type = goods["type"].asInt();
            tmpGoods.num = goods["num"].asInt();
            
            tGoodsList.push_back(tmpGoods);
        }
        
        OpenBoxResultView *pOpenBoxResult = OpenBoxResultView::create(this);
        pOpenBoxResult->initView(tGoodsList);
        this->addChild(pOpenBoxResult,99);
        
        if (p_CurEvent)
        {
            p_CurEvent->m_bBoxIsOpened = true;
        }
    }
}

void OpenBoxView::notificationTouchEvent(LTouchEvent tLTouchEvent)
{
    if (tLTouchEvent == kLTouchEventSingleClick)
    {
        this->onCCControlButtonClicked(NULL,NULL);
    }
}