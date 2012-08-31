//
//  NPCDialogView.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-8-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "NPCDialogView.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"
#include "EventDataManager.h"
#include "EventBasic.h"
#include "LuckySprite.h"
#include "FuzzyBgView.h"
#include "DictDataManager.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

#define TAG_MONSTER 91

NPCDialogView::NPCDialogView():
mLabelNpcName(NULL),
mLabelDialogContent(NULL),
mSpriteNpc(NULL)
{
    mTalkList.clear();
}

NPCDialogView::~NPCDialogView()
{
    mTalkList.clear();
}

NPCDialogView *NPCDialogView::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("FuzzyBgView", FuzzyBgViewLoader::loader());
    
    ccNodeLoaderLibrary->registerCCNodeLoader("NPCDialogView", NPCDialogViewLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/dialog.ccbi", pOwner);
    
    NPCDialogView *pNPCDialogView = static_cast<NPCDialogView *>(pNode);
    return pNPCDialogView;
}

cocos2d::SEL_MenuHandler NPCDialogView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler NPCDialogView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    return NULL;
}
bool NPCDialogView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode)
{
    
    return false;
}

void NPCDialogView::onMenuItemClicked(cocos2d::CCObject *pTarget)
{
    
}

void NPCDialogView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    
}

void NPCDialogView::notificationTouchEvent(LTouchEvent tLTouchEvent)
{
    if (tLTouchEvent == kLTouchEventSingleClick)
    {
        this->getNextTalk();
        
        showDialog();
    }
}

void NPCDialogView::setDialog(stTalk *tTalk)
{
    string dialog = EventDataManager::getShareInstance()->getDialogFromTalk(tTalk);
    mLabelNpcName->setString(tTalk->npcName.c_str());
    mLabelDialogContent->setString(dialog.c_str());
}

void NPCDialogView::setData(LEventData *tEvent, cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector)
{
    p_CurEvent = tEvent;
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    mLabelNpcName = static_cast<CCLabelTTF *>(this->getChildByTag(10));
    mLabelDialogContent = static_cast<CCLabelTTF *>(this->getChildByTag(11));
    mSpriteNpc = static_cast<CCSprite *>(this->getChildByTag(TAG_MONSTER));
    
    mTalkList.clear();
    
    mTalkList = EventDataManager::getShareInstance()->getAllTalk(p_CurEvent->id);
    
    
    pBeginPoint = CCPointZero;
    
    LuckySprite *pSpriteMonster = static_cast<LuckySprite *>(this->getChildByTag(TAG_MONSTER));
    if (pSpriteMonster)
    {
        const stMonster * pMonster = DictDataManager::shareDictDataManager()->getMonsterImageId(p_CurEvent->targetId);
        pSpriteMonster->setNewTexture(pMonster->imageId);
    }
    
    showDialog();
    
}

void NPCDialogView::removeAndCleanSelf(float dt)
{
    ((m_target)->*(m_pfnSelector))(this, NULL);
}

void NPCDialogView::menuBackCallback(CCObject* pSender)
{
    this->removeAndCleanSelf(0);
}

void NPCDialogView::showDialog()
{
    stTalk *tTalk = this->getCurTalk();
    
    if (tTalk)
    {
        this->setDialog(tTalk);
    }
    else {
        //Dialog was end.
        if ( m_target && m_pfnSelector )
            ((m_target)->*(m_pfnSelector))(this, NULL);
    }
}

stTalk * NPCDialogView::getCurTalk()
{
    if ( mTalkList.empty() == false )
    {
        return mTalkList[0];
    }
    else return NULL;
}

stTalk * NPCDialogView::getNextTalk()
{
    if ( mTalkList.empty() == false )
    {
        mTalkList.erase(mTalkList.begin());
        if ( mTalkList.empty() == false )
        {
            return mTalkList[0];
        }
        else
            return NULL;
    }
    else
        return NULL;
}