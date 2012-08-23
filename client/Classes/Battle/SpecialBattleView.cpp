//
//  SpecialBattleView.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-8-9.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "SpecialBattleView.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"
#include "EventDataManager.h"
#include "BattleResultView.h"
#include "LuckySprite.h"
#include "FuzzyBgView.h"
#include "NetManager.h"

#define TAG_EFFECT_MONSTER_NODE 6
#define TAG_EFFECT_ACTOR_NODE 7


USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

SpecialBattleView::SpecialBattleView()
{
    CCAnimationCache *cache = CCAnimationCache::sharedAnimationCache();
    CCAnimation *animation1 = cache->animationByName("yellowBomb");
    CCAnimation *animation2 = cache->animationByName("purpleBomb");
    CCAnimation *animation3 = cache->animationByName("orangeBomb");
    CCAnimation *animation4 = cache->animationByName("greenBomb");
    animationEffect[0] = CCAnimate::create(animation1);
    animationEffect[1] = CCAnimate::create(animation2);
    animationEffect[2] = CCAnimate::create(animation3);
    animationEffect[3] = CCAnimate::create(animation4); 
    
    CC_SAFE_RETAIN(animationEffect[0]);
    CC_SAFE_RETAIN(animationEffect[1]);
    CC_SAFE_RETAIN(animationEffect[2]);
    CC_SAFE_RETAIN(animationEffect[3]);
    
    m_nRound = 0;
}

SpecialBattleView::~SpecialBattleView()
{
    CC_SAFE_RELEASE(animationEffect[0]);
    CC_SAFE_RELEASE(animationEffect[1]);
    CC_SAFE_RELEASE(animationEffect[2]);
    CC_SAFE_RELEASE(animationEffect[3]);
}

SpecialBattleView *SpecialBattleView::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("SpecialBattleView", SpecialBattleViewLoader::loader());
    ccNodeLoaderLibrary->registerCCNodeLoader("FuzzyBgView", FuzzyBgViewLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/battle_special.ccbi", pOwner);
    
    SpecialBattleView *pSpecialBattleView = static_cast<SpecialBattleView *>(pNode);
    
    pSpecialBattleView->getChildByTag(TAG_EFFECT_MONSTER_NODE)->setVisible(false);
    pSpecialBattleView->getChildByTag(TAG_EFFECT_ACTOR_NODE)->setVisible(false);

    return pSpecialBattleView;
}

cocos2d::SEL_MenuHandler SpecialBattleView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", SpecialBattleView::onMenuItemClicked);
    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler SpecialBattleView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", SpecialBattleView::onCCControlButtonClicked );
    return NULL;
}
bool SpecialBattleView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode)
{
    return false;
}

void SpecialBattleView::onMenuItemClicked(cocos2d::CCObject *pTarget)
{
    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pTarget);
    printf("tag %d\n",p->getTag());
}

void SpecialBattleView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pSender);
    printf("tag %d\n",p->getTag());
    
    CallBackHeroAction();
}
                                          
void SpecialBattleView::responseFight(CCNode *pNode, void* data)
{
     Json::Value root;
     Json::Reader reader;
    
    if(reader.parse(NetManager::shareNetManager()->processResponse(data), root))
    {
        battleResult = root["meta"]["out"];
        
        CreateTeam(battleResult["team"]);
        m_nIndexList = 0;
    }
}

void SpecialBattleView::CreateTeam(Json::Value &data)
{        
    int i = 0;
    m_mapTeam.clear();
    m_mapTeam["A"][data["A"][i]["id"].asInt()] = (CCSprite *)getChildByTag(TAG_EFFECT_MONSTER_NODE);
    m_mapTeam["B"][data["B"][i]["id"].asInt()] = (CCSprite *)getChildByTag(TAG_EFFECT_ACTOR_NODE);
}


void SpecialBattleView::CallBackHeroAction()
{
    //播放一回合的动作
    Json::Value playList = battleResult["battleArray"]["playlist"];
    if (playList[m_nIndexList].isNull())
    {
        if ( m_target && m_pfnSelector )
            ((m_target)->*(m_pfnSelector))(this, NULL);
        return;
    }
    
    if (m_nRound == 2) 
    {
        m_nRound = 0;
        return;
    }
    
    Json::Value tempMember = playList[m_nIndexList++];
    CCNode* pNode = m_mapTeam[tempMember["teamId"].asString()][tempMember["actId"].asInt()];
    
    float tempRandom = CCRANDOM_0_1();
    int indexTemp = tempRandom < 0.3 ?  1 : (tempRandom < 0.6 ? 2: (tempRandom < 0.9 ? 3 :0));
    pNode->runAction(CCSequence::create(
                                    CCShow::action(),
                                    animationEffect[indexTemp],
                                    CCHide::action(),
                                    CCCallFunc::create(this, callfunc_selector(SpecialBattleView::CallBackHeroAction)),
                                    NULL));

    Json::FastWriter jasonWrite;
    CCLOG("%s", jasonWrite.write(playList[m_nIndexList]).c_str());
    
    m_nRound++;
}



bool SpecialBattleView::ccTouchBegan(CCTouch* touch, CCEvent *pEvent)
{
    if ( !touch ) return false;
    
    pBeginPoint = this->convertTouchToNodeSpace(touch);
    
    return true;
}

void SpecialBattleView::ccTouchMoved(CCTouch* touch, CCEvent *pEvent)
{
    
}

void SpecialBattleView::ccTouchEnded(CCTouch* touch, CCEvent *pEvent)
{
    if ( !touch ) return;
    CCPoint endPoint = this->convertTouchToNodeSpace(touch);
    
    if ( pBeginPoint.x != 0 && pBeginPoint.y != 0 )
    {
//        if ( m_target && m_pfnSelector )
//            ((m_target)->*(m_pfnSelector))(this, NULL);
    }
    pBeginPoint = CCPointZero;
}

void SpecialBattleView::removeAndCleanSelf(float dt)
{
    ((m_target)->*(m_pfnSelector))(this, NULL);
}

void SpecialBattleView::menuBackCallback(CCObject* pSender)
{
    this->removeAndCleanSelf(0);
}

void SpecialBattleView::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority , true);
}

void SpecialBattleView::setData(LEventData *tEvent, cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector)
{
    p_CurEvent = tEvent;
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    pBeginPoint = CCPointZero;
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCMenu* pMenu = CCMenu::create();
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 100, 1000);
    
    CCMenuItemSprite *pBackItem = CCMenuItemSprite::create(LuckySprite::create(2), LuckySprite::create(3), LuckySprite::create(3), this, menu_selector(SpecialBattleView::menuBackCallback)); 
    pBackItem->setScale(0.5);
    pBackItem->setPosition(ccp(screanSize.width - 30, screanSize.height - 20));
    pMenu->addChild(pBackItem,5);
    
    this->setTouchEnabled(true);
    
    NetManager::shareNetManager()->sendEx(kModeBattle, kDoFight2, callfuncND_selector(SpecialBattleView::responseFight), this, "\"monsterId\": %d", p_CurEvent->targetId[0]);
}

void SpecialBattleView::showBattleResultView()
{
    BattleResultView *retView = BattleResultView::create(this);
    retView->initView(p_CurEvent);
    this->addChild(retView,88);
}


