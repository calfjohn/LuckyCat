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
#include "PlayerInfoView.h"
#include "BasicFunction.h"

#define TAG_EFFECT_MONSTER_NODE 6
#define TAG_EFFECT_ACTOR_NODE 7
#define TAG_MONSTER 91

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
    
    if(p->getTag() == 1){
        CCNode *pNode = this->getChildByTag(TAG_PLAYER_INFO);
        if (!pNode)
        {
            PlayerInfoView *pInfo = PlayerInfoView::create(this);
            this->addChild(pInfo);
            pInfo->setTag(TAG_PLAYER_INFO);
        }
        else {
            pNode->removeFromParentAndCleanup(true);
        }
    }
}

void SpecialBattleView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
//    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pSender);
//    printf("tag %d\n",p->getTag());
    playList.clear();
    playList = battleResult["battleArray"]["playlist"][m_nRound++];

    if (playList.isNull())
    {   
        //所有回合结束
        removeAndCleanSelf(0);
    }
    else
    {
        CCLOG("第%d轮", m_nRound);
        Json::FastWriter jasonWrite;
        CCLOG("%s", jasonWrite.write(playList).c_str());

        //播放回合
        CallBackHeroAction();
    }
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
        m_nRound = 0;
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
    this->setIsTouchForbidden(true);

    //本回合结束
    if (playList[m_nIndexList].isNull()) 
    {
        m_nIndexList = 0;
        this->setIsTouchForbidden(false);
        return;
    }
    
    //播放动作
    Json::Value tempMember = playList[m_nIndexList++];
    CCNode* pNode = m_mapTeam[tempMember["teamId"].asString()][tempMember["actId"].asInt()];
    
    float tempRandom = CCRANDOM_0_1();
    int indexTemp = tempRandom < 0.3 ?  1 : (tempRandom < 0.6 ? 2: (tempRandom < 0.9 ? 3 :0));
    pNode->runAction(CCSequence::create(
                                    CCShow::create(),
                                    animationEffect[indexTemp],
                                    CCHide::create(),
                                    CCCallFunc::create(this, callfunc_selector(SpecialBattleView::CallBackHeroAction)),
                                    NULL));
    
    showTips(printFight(tempMember).c_str(), pNode->getPosition());
    showTips(ConvertToString(tempMember["hurt"]).c_str(), ccp(160, 240));
}

void SpecialBattleView::notificationTouchEvent(LTouchEvent tLTouchEvent)
{
    if (tLTouchEvent == kLTouchEventSingleClick)
    {
        onCCControlButtonClicked(NULL, NULL);
    }
}

void SpecialBattleView::removeAndCleanSelf(float dt)
{
    if ( m_target && m_pfnSelector )
        ((m_target)->*(m_pfnSelector))(this, NULL);
}

void SpecialBattleView::menuBackCallback(CCObject* pSender)
{
    this->removeAndCleanSelf(0);
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
    
    CCSprite *pMonster = static_cast<CCSprite *>(this->getChildByTag(TAG_MONSTER));
    if (pMonster)
    {
        stEvent *tStEvent = tEvent->pStEvent;
        char strChar[100];
        memset(strChar, 0, 100);
        sprintf(strChar, "pub/image/hero/monster_100%d.png",tStEvent->targetId[0]);
        pMonster->setTexture(LuckySprite::getTextrue2D(strChar));
    }
    
    this->setTouchEnabled(true);
    
    NetManager::shareNetManager()->sendEx(kModeBattle, kDoFight2, callfuncND_selector(SpecialBattleView::responseFight), this, "\"monsterId\": %d", p_CurEvent->targetId[0]);
}

void SpecialBattleView::showTips(const char *tips, CCPoint positon)
{
    CCLabelTTF *pLable = CCLabelTTF::create(tips, "Arial", 36);
    pLable->setColor(ccBLUE);
    addChild(pLable, 10000);
    
    CCAction* spawnAction = CCSpawn::actions(CCMoveBy::actionWithDuration(3.0, ccp(0, 30)),
                                            CCFadeOut::actionWithDuration(3.0),
                                            NULL);
    CCAction* action = CCSequence::actions(CCPlace::actionWithPosition(positon), 
                                           spawnAction, 
                                           CCCallFuncN::create(pLable, callfuncN_selector(SpecialBattleView::removeSelf)),
                                           NULL);

    pLable->runAction(action);
}

void SpecialBattleView::removeSelf(CCNode *pNode)
{
    pNode->removeFromParentAndCleanup(true);
}
