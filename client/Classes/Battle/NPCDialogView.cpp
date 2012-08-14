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
#include "TaskDataManager.h"
#include "TaskBasic.h"
#include "LuckySprite.h"
#include "FuzzyBgView.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

NPCDialogView::NPCDialogView():
mLabelNpcName(NULL),
mLabelDialogContent(NULL),
mSpriteNpc(NULL)
{
    
}

NPCDialogView::~NPCDialogView()
{
    
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
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", NPCDialogView::onMenuItemClicked);
    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler NPCDialogView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", NPCDialogView::onCCControlButtonClicked );
    return NULL;
}
bool NPCDialogView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode)
{
//    if (!mLabelNpcName)
//    {
//        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelNpcName", cocos2d::CCLabelTTF *, mLabelNpcName);
//    }
//    if (!mLabelDialogContent)
//    {
//        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelDialogContent", cocos2d::CCLabelTTF *, mLabelDialogContent);
//    }
//    if (!mSpriteNpc)
//    {
//        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSpriteNpc", cocos2d::CCSprite *, mSpriteNpc);
//    }
    
    return false;
}

void NPCDialogView::onMenuItemClicked(cocos2d::CCObject *pTarget)
{
    
}

void NPCDialogView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    
}

bool NPCDialogView::ccTouchBegan(CCTouch* touch, CCEvent *pEvent)
{
    if ( !touch ) return false;
    
    pBeginPoint = this->convertTouchToNodeSpace(touch);
    
    return true;
}

void NPCDialogView::ccTouchMoved(CCTouch* touch, CCEvent *pEvent)
{
    
}

void NPCDialogView::ccTouchEnded(CCTouch* touch, CCEvent *pEvent)
{
    if ( !touch ) return;
    CCPoint endPoint = this->convertTouchToNodeSpace(touch);
    
    if ( pBeginPoint.x != 0 && pBeginPoint.y != 0 )
    {
        this->getNextTalk();
        
        showDialog();
    }
    pBeginPoint = CCPointZero;
}

void NPCDialogView::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority , true);
}

void NPCDialogView::setDialog(stTalk *tTalk)
{
    string dialog = TaskDataManager::getShareInstance()->getDialogFromTalk(tTalk);
    mLabelNpcName->setString(tTalk->npcName.c_str());
    mLabelDialogContent->setString(dialog.c_str());
}

void NPCDialogView::setData(stTask *tTask, cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector)
{
    p_CurTask = tTask;
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    mLabelNpcName = static_cast<CCLabelTTF *>(this->getChildByTag(10));
    mLabelDialogContent = static_cast<CCLabelTTF *>(this->getChildByTag(11));
    mSpriteNpc = static_cast<CCSprite *>(this->getChildByTag(12));
    
    mTalkList.clear();
    
    mTalkList = TaskDataManager::getShareInstance()->getAllTalk(p_CurTask->id);
    
    
    pBeginPoint = CCPointZero;
    
    this->setTouchEnabled(true);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 100, 1000);
    
    CCMenuItemSprite *pBackItem = CCMenuItemSprite::create(LuckySprite::create(2), LuckySprite::create(3), LuckySprite::create(3), this, menu_selector(NPCDialogView::menuBackCallback)); 
    pBackItem->setScale(0.5);
    pBackItem->setPosition(ccp(screanSize.width - 30, screanSize.height - 20));
    pMenu->addChild(pBackItem,5);
    
    showDialog();
    
}

void NPCDialogView::removeAndCleanSelf(float dt)
{
    ((m_target)->*(m_pfnSelector))(this, NULL);
    
    CCLayer *pLayer = (CCLayer *)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_TASK_LIST_LAYER));
    if ( pLayer )
    {
        pLayer->removeFromParentAndCleanup(true);
    }
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