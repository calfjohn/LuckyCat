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
#include "DictDataManager.h"

#define TAG_EFFECT_MONSTER_NODE 6
#define TAG_EFFECT_ACTOR_NODE 7
#define TAG_MONSTER 91

#define TAG_MONSTER_HP_LINE_1           101
#define TAG_MONSTER_HP_LINE_BG_1        102
#define TAG_MONSTER_HP_LINE_2           103
#define TAG_MONSTER_HP_LINE_BG_2        104
#define TAG_HERO_HP_LINE_1              111
#define TAG_HERO_HP_LINE_BG_1           112
#define TAG_HERO_HP_LINE_2              113
#define TAG_HERO_HP_LINE_BG_2           114

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
    m_nActionNumber = 0;
    m_nCountTime = 0;
    m_nTotalRound = 0;
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

void SpecialBattleView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pSender);
    printf("tag %d\n",p->getTag());
    
    if (this->getIsTouchForbidden() == false)
    {
        if ( m_nCountTime > 0 )
        {
            pressControlButtonDice();
        }
        else {
            analyseBattleData();
        }
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
        
        Json::Value battleArray = battleResult["battleArray"];
        Json::Value playelist = battleArray["playlist"];
        
        Json::Value team = battleResult["team"];
        
        int pos = 0;
        Json::Value json_A_0 = team["A"][pos];
        GRole *role_A_0 = &m_mapTeam["A"][0];
        role_A_0->maxHp = json_A_0["hp"].asInt();
        role_A_0->curHP = role_A_0->maxHp;
        
        Json::Value json_B_0 = team["B"][pos];
        GRole *role_B_0 = &m_mapTeam["B"][0];
        role_B_0->maxHp = json_B_0["hp"].asInt();
        role_B_0->curHP = role_B_0->maxHp;
        
        m_nRound = 0;
        m_nActionNumber = 0;
        
        m_nTotalRound = playelist.size();
        
        this->startBattle();
    }
}

void SpecialBattleView::CreateTeam(Json::Value &data)
{        
//    int i = 0;
//    m_mapTeam;
}

void SpecialBattleView::notificationTouchEvent(LTouchEvent tLTouchEvent)
{
    if (tLTouchEvent == kLTouchEventSingleClick)
    {
        if ( m_nCountTime > 0 )
        {
            pressControlButtonDice();
        }
        else {
            if (this->getIsTouchForbidden() == false)
                analyseBattleData();
        }
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
    
    LuckySprite *pSpriteMonster = static_cast<LuckySprite *>(this->getChildByTag(TAG_MONSTER));
    if (pSpriteMonster)
    {
        const stMonster * pMonster = DictDataManager::shareDictDataManager()->getMonsterImageId(p_CurEvent->targetId);
        pSpriteMonster->setNewTexture(pMonster->imageId);
    }
    
    this->setTouchEnabled(true);
    this->setIsTouchForbidden(true);
    
    CCNode *pHero1 = this->getChildByTag(4)->getChildByTag(1);
    CCNode *pHero2 = this->getChildByTag(4)->getChildByTag(2);
    
    CCNode *pHeroHpLineBg1 = this->getChildByTag(TAG_HERO_HP_LINE_BG_1);
    CCNode *pHeroHpLineBg2 = this->getChildByTag(TAG_HERO_HP_LINE_BG_2);
    CCNode *pMonsterHpLineBg1 = this->getChildByTag(TAG_MONSTER_HP_LINE_BG_1);
    
    CCNode *pHeroHpLine1 = this->getChildByTag(TAG_HERO_HP_LINE_1);
    CCNode *pHeroHpLine2 = this->getChildByTag(TAG_HERO_HP_LINE_2);
    CCNode *pMonsterHpLine1 = this->getChildByTag(TAG_MONSTER_HP_LINE_1);
    
    pHero2->setVisible(false);
    pHeroHpLine2->setVisible(false);
    pHeroHpLineBg2->setVisible(false);
    
    std::vector<CCNode *> tHpLineList;
    tHpLineList.push_back(pHeroHpLine1);
    tHpLineList.push_back(pHeroHpLine2);
    tHpLineList.push_back(pMonsterHpLine1);
    
    std::vector<CCProgressTimer *> mHpProgressTimerList;
    
    mHpProgressTimerList.clear();
    for (std::vector<CCNode *>::iterator _iter = tHpLineList.begin(); _iter != tHpLineList.end(); _iter++) {
        CCNode *pNode = *_iter;
        CCSprite *pSprite = static_cast<CCSprite *>(pNode);
        pSprite->setVisible(false);
        
        CCSprite *temp = CCSprite::create(pSprite->getTexture());
        CCProgressTimer *pProgressTimer = CCProgressTimer::create(temp);
        pProgressTimer->setType(kCCProgressTimerTypeBar);
        pProgressTimer->setMidpoint(ccp(0,0));
        pProgressTimer->setBarChangeRate(ccp(1, 0));
        addChild(pProgressTimer);
        pProgressTimer->setPosition(pSprite->getPosition());
        pProgressTimer->setPercentage(100);
        
        mHpProgressTimerList.push_back(pProgressTimer);
    }
    
    mHpProgressTimerList[1]->setVisible(false);
    
    GRole roleA_1 = GRole();
    roleA_1.teamId = kGTeamA;
    roleA_1.pNodeRole = pHero1;
    roleA_1.pProgressTimer = mHpProgressTimerList[0];
    
    GRole roleB_1 = GRole();
    roleB_1.teamId = kGTeamB;
    roleB_1.pNodeRole = pSpriteMonster;
    roleB_1.pProgressTimer = mHpProgressTimerList[2];
    
    m_mapTeam.clear();
    m_mapTeam["A"][0] = roleA_1;
    m_mapTeam["B"][0] = roleB_1;
    
    NetManager::shareNetManager()->sendEx(kModeBattle, kDoFight2, callfuncND_selector(SpecialBattleView::responseFight), this, "\"monsterId\": %d",p_CurEvent->targetId);
}

void SpecialBattleView::callbackRemoveNodeWhenDidAction(CCNode * pNode)
{
    this->removeChild(pNode, true);
}

void SpecialBattleView::showTip(std::string tStr,ccColor3B tColor,TipMotion tTipMotion,unsigned int fontSize,cocos2d::CCCallFuncN *callBack)
{
    CCLabelTTF * label = CCLabelTTF::create(tStr.c_str(), "Thonburi", fontSize);
    this->addChild(label,99);
    ccColor3B color = tColor;
    label->setColor(color);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint beginPos;
    
    CCPoint midPos;
    
    CCPoint endPos;
    
    if ( tTipMotion == kTipMotionGeneral ) {
        beginPos = CCPointMake(screanSize.width * 0.5f, screanSize.height * 0.5f);
        
        midPos = CCPointMake(screanSize.width * 0.5f, screanSize.height * 0.6f);
        
        endPos = CCPointMake(screanSize.width *0.5f, screanSize.height * 0.7f);
    }
    else if ( tTipMotion == kTipMotionRise ){
        beginPos = CCPointMake(screanSize.width * 0.5f, screanSize.height * 0.2f);
        
        midPos = CCPointMake(screanSize.width * 0.5f, screanSize.height * 0.5f);
        
        endPos = CCPointMake(screanSize.width *0.5f, screanSize.height * 0.8f );
    }
    else {
        beginPos = CCPointMake(screanSize.width * 0.5f, screanSize.height * 0.8f);
        
        midPos = CCPointMake(screanSize.width * 0.5f, screanSize.height * 0.5f);
        
        endPos = CCPointMake(screanSize.width *0.5f, screanSize.height * 0.2f);
    }
    
    
    label->setPosition(beginPos);
    
    CCAction * seq;
    
    float t_f_moveTime = 0.8f;
    float t_f_delayTime = 0.5f;
    
    if (callBack)
    {
        seq = CCSequence::create(
                                 CCSpawn::create(
                                                 CCMoveTo::create(t_f_moveTime, midPos),
                                                 CCFadeIn::create(t_f_moveTime),
                                                 NULL),
                                 CCDelayTime::create(t_f_delayTime),
                                 CCSpawn::create(CCMoveTo::create(t_f_moveTime, endPos),
                                                 CCFadeOut::create(t_f_moveTime),
                                                 NULL),
                                 callBack,
                                 CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::callbackRemoveNodeWhenDidAction)),
                                 NULL);
    }
    else {
        seq = CCSequence::create(
                                 CCSpawn::create(
                                                 CCMoveTo::create(t_f_moveTime, midPos),
                                                 CCFadeIn::create(t_f_moveTime),
                                                 NULL),
                                 CCDelayTime::create(t_f_delayTime),
                                 CCSpawn::create(CCMoveTo::create(t_f_moveTime, endPos),
                                                 CCFadeOut::create(t_f_moveTime),
                                                 NULL),
                                 CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::callbackRemoveNodeWhenDidAction)),
                                 0);
    }
    
    label->runAction(seq);
}

void SpecialBattleView::startBattle()
{
    std::string labString;
    if (true)
    {
        labString = std::string("Boss出现...");
    }
    else {
        labString = std::string("小小\n    VS\n      大大");
    }
    CCLabelTTF * label = CCLabelTTF::create(labString.c_str(), "Thonburi", 20);
    this->addChild(label,99);
    ccColor3B color = ccYELLOW;//{ 226, 121, 7};
    label->setColor(color);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint labPos = CCPointMake(screanSize.width * 0.5f, screanSize.height * 0.75f);
    
    label->setPosition(labPos);
    label->setScale(2);
    
    CCAction * seq = CCSequence::create(
                                        CCDelayTime::create(ACTION_TIME_LABEL_SHOW_TIME),
                                        CCMoveBy::create(ACTION_TIME_SHOW_SKILL_NAME, CCPointMake(0, LABEL_MOVE_DISTANCE)),
                                        CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::analyseBattleData)),
                                        CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::callbackRemoveNodeWhenDidAction)),
                                        0);
    label->runAction(seq);
}

void SpecialBattleView::analyseBattleData()
{
    if ( m_nActionNumber >= m_OneRoundActionList.size() && m_nActionNumber != 0){
        //一个回合显示结束
        m_nRound++;
        m_nActionNumber = 0;
    }
    
    if ( m_nRound < m_nTotalRound )
    {
        if ( m_nActionNumber == 0 )
        {
            Json::Value roundData =battleResult["battleArray"]["playlist"][m_nRound];
            
            m_OneRoundActionList.clear();
            for (int i = 0; i < roundData.size(); i++) {
                Json::Value jsonAction = roundData[i];
                GRoleAction tAction;
                tAction.type = (GActionType)jsonAction["type"].asInt();
                string teamId = jsonAction["teamId"].asString();
                if ( teamId.compare("A") == 0 )
                {
                    tAction.teamId = kGTeamA;
                }
                else {
                    tAction.teamId = kGTeamB;
                }
                tAction.actId = jsonAction["actId"].asInt();
                tAction.skillId = jsonAction["skillId"].asInt();
                tAction.hurt = jsonAction["hurt"].asInt();
                tAction.fx = jsonAction["fx"].asInt();
                
                m_OneRoundActionList.push_back(tAction);
            }
            this->showRoundNumber();
        }
        else {
            this->showRoleAction();
        }
    }
    else {
        //整个动画结束
        this->removeAndCleanSelf(0);
    }
}

void SpecialBattleView::showRoundNumber()
{   
    char strChar[512];
    memset(strChar, 0, 512);
    sprintf(strChar,"第 %d 回合", m_nRound + 1);
    
    CCLabelTTF * label = CCLabelTTF::create(strChar, "Thonburi", 34);
    this->addChild(label,99);
    ccColor3B color = ccYELLOW;
    label->setColor(color);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint posLeft = CCPointMake(screanSize.width * 0.1f, screanSize.height * 0.5f);
    CCPoint posMid = CCPointMake(screanSize.width * 0.5f, screanSize.height *0.5f);
    CCPoint posRight = CCPointMake(screanSize.width * 0.9f, screanSize.height * 0.5f);
    
    label->setPosition(posLeft);
    
    CCAction * seq = CCSequence::create(
                                        CCSpawn::create(
                                                        CCMoveTo::create(SHOW_ROUND_TIME, posMid),
                                                        CCFadeIn::create(0.5f),
                                                        0),
                                        CCDelayTime::create(SHOW_ROUND_TIME),
                                        CCSpawn::create(
                                                        CCMoveTo::create(SHOW_ROUND_TIME, posRight),
                                                        CCFadeOut::create(0.5f),
                                                        0),
                                        CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::countDown)),
                                        CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::callbackRemoveNodeWhenDidAction)),
                                        0);
    
    label->runAction(seq);
}

void SpecialBattleView::countDown()
{
    if ( m_OneRoundActionList[0].teamId == kGTeamA )
    {
        this->setIsTouchForbidden(false);
        m_nCountTime = COUNT_DOWN_TIMES;
        this->schedule(schedule_selector(SpecialBattleView::countDownSchedule), COUNT_DOWN_INTERVAL, COUNT_DOWN_TIMES, 0);
    }
    else {
        this->showRoleAction();
    }
}

void SpecialBattleView::countDownSchedule(float tArg)
{
    char strChar[512];
    memset(strChar, 0, 512);
    sprintf(strChar,"%d", m_nCountTime--);
    
    if (m_nCountTime == 0)
    {
        this->showDiceResult();
    }
    
    CCLabelTTF * label = CCLabelTTF::create(strChar, "Thonburi", 46);
    this->addChild(label,99);
    ccColor3B color = ccYELLOW;//{ 226, 121, 7};
    label->setColor(color);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint labPos = CCPointMake(screanSize.width * 0.5f, screanSize.width * 0.5f);
    
    label->setPosition(labPos);
    
    CCAction * seq = CCSequence::create(
                                        CCDelayTime::create(0.5f),
                                        CCSpawn::create(
                                                        CCMoveBy::create(0.5f, CCPointMake(0, LABEL_MOVE_DISTANCE*2)),
                                                        CCFadeOut::create(0.5f),
                                                        0),
                                        CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::callbackRemoveNodeWhenDidAction)),
                                        0);
    label->runAction(seq);
}

void SpecialBattleView::showDiceResult()
{
    this->setIsTouchForbidden(true);
    
    this->showTip(getActionName(m_OneRoundActionList[m_nActionNumber].type), ccGREEN, kTipMotionGeneral,26,CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::showRoleAction)));
}

void SpecialBattleView::pressControlButtonDice()
{
    if (m_nCountTime > 0)
    {
        this->unschedule(schedule_selector(SpecialBattleView::countDownSchedule));
        this->showDiceResult();
    }
}

void SpecialBattleView::showRoleAction()
{
    GRoleAction tAction = m_OneRoundActionList[m_nActionNumber++];
    
    string strTip;
    
    if (tAction.hurt < 0)
    {
        strTip = getActionName(tAction.type);
    }
    else {
        strTip = getActionName(tAction.type);
        char strChar[512];
        memset(strChar, 0, 512);
        
        int hurt = static_cast<int>(tAction.hurt);
        if (hurt != 0)
        {
            sprintf(strChar, "%s - %d",strTip.c_str(), tAction.hurt);
        }
        else {
            sprintf(strChar, "%s",strTip.c_str());
        }
        
        strTip = string(strChar);
    }
    
    TipMotion tMotion;
    GRole *pRole;
    if (tAction.teamId == kGTeamA)
    {
        tMotion = kTipMotionRise;
        pRole = &m_mapTeam["A"][0];
    }
    else {
        tMotion = kTipMotionSink;
        pRole = &m_mapTeam["B"][0];
    }

    dealRoleAction(pRole,tAction);
    pRole->pProgressTimer->setPercentage(pRole->getCurPercentHP());
    
    this->showTip(strTip, ccRED,tMotion);
    
    CCActionInterval *pActionEffect = GetSkillEffect(tAction.type);
    CCNode *pActionNode = getActionNode(tAction);
    
    if (pActionEffect && pActionNode)
    {
        pActionNode->runAction(CCSequence::create(
                                                                             CCShow::create(),
                                                                             pActionEffect,
                                                                             CCHide::create(),
                                                                             CCDelayTime::create(1.0f),
                                                                             CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::analyseBattleData)),
                                                                             NULL));
    }
    else {
        this->runAction(CCSequence::create(
                                                                             CCDelayTime::create(1.0f),
                                                                             CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::analyseBattleData)),
                                                                             NULL));
    }

}

CCActionInterval *SpecialBattleView::GetSkillEffect(GActionType type)
{
    CCActionInterval *pAction = NULL;
    switch (type) {
        case kGActionTypeAttack:
        {
            pAction = (CCActionInterval *)animationEffect[0];
            break;
        }
        case kGActionTypeCritical_1:
        {
            pAction = (CCActionInterval *)animationEffect[1];
            break;
        }
        case kGActionTypeCritical_2:
        {
            pAction = (CCActionInterval *)animationEffect[3];
            break;
        }
        case kGActionTypeCrush:
        {
            pAction = (CCActionInterval *)animationEffect[2];
            break;
        }
        case kGActionTypeSuckBlood_1:
        {
            
            break;
        }
        case kGActionTypeSuckBlood_2:
        {
            
            break;
        } 
        case kGActionTypeHurt:
        {
            
            break;
        }
        case kGActionTypeDodge:
        {
            pAction = CCBlink::create(ACTION_TIME_BLINK, ACTION_BLINK_TIMES);
            break;
        }
        case kGActionTypeRevert:
        {
            
            break;
        }  
        default:
            break;
    }
    return pAction;
}

std::string SpecialBattleView::getActionName(GActionType type)
{
    string actionName;
    switch (type) {
        case kGActionTypeAttack:
            actionName = "攻击";
            break;
        case kGActionTypeCritical_1:
            actionName = "爆击";
            break;
        case kGActionTypeCritical_2:
            actionName = "爆击";
            break;
        case kGActionTypeCrush:
            actionName = "破防";
            break;
        case kGActionTypeSuckBlood_1:
            actionName = "吸血";
            break;
        case kGActionTypeSuckBlood_2:
            actionName = "吸血";
            break;
            
        case kGActionTypeHurt:
            actionName = "受击";
            break;
        case kGActionTypeDodge:
            actionName = "闪避";
            break;
        case kGActionTypeRevert:
            actionName = "反震";
            break;
            
        default:
            actionName = "error";
            break;
    }
    return actionName;
}

CCNode * SpecialBattleView::getActionNode(GRoleAction tAction)
{
    CCNode *pNode = NULL;
    if ( tAction.type == kGActionTypeDodge ) {
        if ( tAction.teamId == kGTeamA )
        {
            pNode = m_mapTeam["A"][0].pNodeRole;
        }
        else {
            pNode = m_mapTeam["B"][0].pNodeRole;
        }
    }
    else {
        if ( tAction.teamId == kGTeamA )
        {
            pNode = this->getChildByTag(TAG_EFFECT_ACTOR_NODE);
        }
        else {
            pNode = this->getChildByTag(TAG_EFFECT_MONSTER_NODE);
        }
    }
    return pNode;
}

void SpecialBattleView::dealRoleAction(GRole *pRole,GRoleAction tAction)
{
    switch (tAction.type) {
        case kGActionTypeAttack:
        {
            break;
        }
        case kGActionTypeCritical_1:
        {
            
            break;
        }
        case kGActionTypeCritical_2:
        {
            
            break;
        }
        case kGActionTypeCrush:
        {
            
            break;
        }
        case kGActionTypeSuckBlood_1:
        {
            if (m_nActionNumber) {
                pRole->setPlusHp(tAction.hurt);
            }
            break;
        }
        case kGActionTypeSuckBlood_2:
        {
            if (m_nActionNumber) {
                pRole->setPlusHp(tAction.hurt);
            }
            break;
        }
        case kGActionTypeHurt:
        {
            if (m_nActionNumber) {
                pRole->setSubHp(tAction.hurt);
            }
            break;
        }
        case kGActionTypeDodge:
        {
            
            break;
        }
        case kGActionTypeRevert:
        {
            if (m_nActionNumber == 2) {
                pRole->setSubHp(tAction.hurt);
            }
            break;
        }
        default:
        {
            
            break;
        }
    }
}