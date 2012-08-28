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

SpecialBattleView::SpecialBattleView():
pNodeAttacker(NULL),
pNOdeDefener(NULL),
pRoleAction(NULL),
m_nCountTime(0)
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
    
    if ( m_nCountTime > 0 )
    {
        pressControlButtonDice();
    }
    else {
        analyseBattleData();
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
        
        //boss 出现
        this->startBattle();
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
    if(m_nRound == 0)
    {
//        this->setIsTouchForbidden(true);
    }
    
    this->unschedule(schedule_selector(SpecialBattleView::countDownSchedule));
    
    //播放一回合的动作
    Json::Value playList = battleResult["battleArray"]["playlist"];
    if (playList[m_nIndexList].isNull())
    {
        removeAndCleanSelf(0);
        return;
    }
    
    if (m_nRound == 2) 
    {
//        this->setIsTouchForbidden(false);
        m_nRound = 0;
        return;
    }
    
    Json::Value tempMember = playList[m_nIndexList++];
    
    pAttackEffectNode = m_mapTeam[tempMember["teamId"].asString()][tempMember["actId"].asInt()];

    Json::FastWriter jasonWrite;
    CCLOG("%s", jasonWrite.write(playList[m_nIndexList]).c_str());
    
    m_nRound++;
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
            if (this->getIsTouchForbidden() == false)analyseBattleData();
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
    this->setIsTouchForbidden(true);
    
//    CCNode *pMonster = this->getChildByTag(TAG_MONSTER);
    mMonsterSpriteList.clear();
    mMonsterSpriteList.push_back(pMonster);
    
    CCNode *pHero1 = this->getChildByTag(4)->getChildByTag(1);
    CCNode *pHero2 = this->getChildByTag(4)->getChildByTag(2);
    mHeroSpriteList.clear();
    mHeroSpriteList.push_back(pHero1);
    mHeroSpriteList.push_back(pHero2);
    
    CCNode *pHeroHpLineBg1 = this->getChildByTag(TAG_HERO_HP_LINE_BG_1);
    CCNode *pHeroHpLineBg2 = this->getChildByTag(TAG_HERO_HP_LINE_BG_2);
    CCNode *pMonsterHpLineBg1 = this->getChildByTag(TAG_MONSTER_HP_LINE_BG_1);
    mHpLineBgList.clear();
    mHpLineBgList.push_back(pHeroHpLineBg1);
    mHpLineBgList.push_back(pHeroHpLineBg2);
    mHpLineBgList.push_back(pMonsterHpLineBg1);
    
    CCNode *pHeroHpLine1 = this->getChildByTag(TAG_HERO_HP_LINE_1);
    CCNode *pHeroHpLine2 = this->getChildByTag(TAG_HERO_HP_LINE_2);
    CCNode *pMonsterHpLine1 = this->getChildByTag(TAG_MONSTER_HP_LINE_1);
    mHpLineList.clear();
    mHpLineList.push_back(pHeroHpLine1);
    mHpLineList.push_back(pHeroHpLine2);
    mHpLineList.push_back(pMonsterHpLine1);
    
    pHero2->setVisible(false);
    pHeroHpLine2->setVisible(false);
    pHeroHpLineBg2->setVisible(false);
    mHpProgressTimerList.clear();
    
    for (std::vector<CCNode *>::iterator _iter = mHpLineList.begin(); _iter != mHpLineList.end(); _iter++) {
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
    
    NetManager::shareNetManager()->sendEx(kModeBattle, kDoFight2, callfuncND_selector(SpecialBattleView::responseFight), this, "\"monsterId\": %d", p_CurEvent->targetId[0]);
}

void SpecialBattleView::battleAnimationCreate(Json::Value tOneRound)
{
    
    CC_SAFE_DELETE(pNodeAttacker);
    CC_SAFE_DELETE(pNOdeDefener);
    CC_SAFE_DELETE(pRoleAction);
    
    std::string teamId = tOneRound["teamId"].asString();
    if (teamId.compare("A") == 0) {
        pNodeAttacker = new GRole();
        pNodeAttacker->rolePosition = kGRolePositionUpOne;
        pNodeAttacker->pNodeRole = mMonsterSpriteList[0];
        pNodeAttacker->pCCProgressTimer = mHpProgressTimerList[0];
        pNodeAttacker->setMaxHp(100);
        
        pNOdeDefener = new GRole();
        pNOdeDefener->rolePosition = kGRolePositionDownOne;
        pNOdeDefener->pNodeRole = mHeroSpriteList[0];
        pNOdeDefener->pCCProgressTimer = mHpProgressTimerList[3];
        pNOdeDefener->setMaxHp(100);
        
        pRoleAction = new GRoleAction();
    }
    else {
        pNOdeDefener = new GRole();
        pNOdeDefener->rolePosition = kGRolePositionUpOne;
        pNOdeDefener->pNodeRole = mMonsterSpriteList[0];
        pNOdeDefener->pCCProgressTimer = mHpProgressTimerList[0];
        pNOdeDefener->setMaxHp(100);
        
        pNodeAttacker = new GRole();
        pNodeAttacker->rolePosition = kGRolePositionDownOne;
        pNodeAttacker->pNodeRole = mHeroSpriteList[0];
        pNodeAttacker->pCCProgressTimer = mHpProgressTimerList[3];
        pNodeAttacker->setMaxHp(100);
        
        pRoleAction = new GRoleAction();
    }
    
    if (teamId.compare("A") == 0)//操作者是主动攻击的
    {
        this->countDown();
    }
    else {
        this->attackerAnimation();
    }
}

void SpecialBattleView::attackerAnimation()//(GRole *pNodeRole,GRoleAction *pAction)
{
    GRole *pNodeRole = pNodeAttacker;
    
    if ( pNodeRole )
    {
        CCFiniteTimeAction *pActionSequence;
        if ( pNodeRole->rolePosition == kGRolePositionUpOne || pNodeRole->rolePosition == kGRolePositionDownTwo )
        {
            CCActionInterval *actionJump = CCJumpBy::create(ACTION_TIME_JUMP, CCPointMake(0, 0), -20, 1);
            CCActionInterval *actionJumpBack = actionJump->reverse();
            pActionSequence = CCSequence::create(actionJump,actionJumpBack,
            CCCallFunc::create(this, callfunc_selector(SpecialBattleView::attackerEffectAnimation)),NULL);
        }
        else {
            CCActionInterval *actionJump = CCJumpBy::create(ACTION_TIME_JUMP, CCPointMake(0, 0), 20, 1);
            CCActionInterval *actionJumpBack = actionJump->reverse();
            pActionSequence = CCSequence::create(actionJump,actionJumpBack,
                                                 CCCallFunc::create(this, callfunc_selector(SpecialBattleView::attackerEffectAnimation)),NULL);
        }
        pNodeRole->pNodeRole->runAction(pActionSequence);
    }
}

void SpecialBattleView::defenderAnimation()//(GRole *pNodeRole,GRoleAction *pAction)
{
    GRole *pNodeRole = pNOdeDefener;
    
    if ( pNodeRole ) {
        CCActionInterval *actionBlink = CCBlink::create(ACTION_TIME_BLINK, ACTION_BLINK_TIMES);
        pNodeRole->pNodeRole->runAction(CCSequence::create(actionBlink,
                                                           CCCallFunc::create(this, callfunc_selector(SpecialBattleView::analyseBattleData)),NULL));
        
        this->defenderEffectAnimation();
    }
}

void SpecialBattleView::attackerEffectAnimation()//(GRole *pNodeRole,GRoleAction *pAction)
{
    float tempRandom = CCRANDOM_0_1();
    int indexTemp = tempRandom < 0.3 ?  1 : (tempRandom < 0.6 ? 2: (tempRandom < 0.9 ? 3 :0));
    
    float animationTime = animationEffect[indexTemp]->getDuration();
    float animationDelayTime = 0.0f;
    if (ACTION_TIME_SHOW_SKILL_NAME + ACTION_TIME_LABEL_SHOW_TIME > animationTime) {
        animationDelayTime = ACTION_TIME_SHOW_SKILL_NAME + ACTION_TIME_LABEL_SHOW_TIME - animationTime;
    }
    
    pAttackEffectNode->runAction(CCSequence::create(
                                        CCShow::create(),
                                        animationEffect[indexTemp],
                                                    CCHide::create(),
                                                    CCDelayTime::create(animationDelayTime),
                                        CCCallFunc::create(this, callfunc_selector(SpecialBattleView::defenderAnimation)),
                                        NULL));
    
    
    
    
    this->showSkillNameAnimation();

}

void SpecialBattleView::showSkillNameAnimation()//(GRole *pNodeRole,GRoleAction *pAction)
{
    std::string skillName = std::string("..左勾拳");
    CCLabelTTF * label = CCLabelTTF::create(skillName.c_str(), "Thonburi", 26);
    this->addChild(label,99);
    ccColor3B color = ccGREEN;//{ 226, 121, 7};
    label->setColor(color);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint endPos = CCPointMake(screanSize.width * 0.5f, screanSize.height * 0.8f);
    
    CCSize  inputTextSize = label->getContentSize();
    CCPoint beginPos(endPos.x, endPos.y - LABEL_MOVE_DISTANCE); 
    
    label->setPosition(beginPos);
    label->setScale(2);
    
    CCAction * seq = CCSequence::create(
                                        CCDelayTime::create(ACTION_TIME_LABEL_SHOW_TIME),
                                        CCMoveTo::create(ACTION_TIME_SHOW_SKILL_NAME, endPos),
                                        CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::callbackRemoveNodeWhenDidAction)),
                                        0);
    label->runAction(seq);
}

void SpecialBattleView::defenderEffectAnimation()//(GRole *pNodeRole,GRoleAction *pAction)
{
    GRole *pNodeRole = pNOdeDefener;
    
    pNodeRole->setSubHp(6);
    //pNodeRole->pCCProgressTimer->setPercentage(pNodeRole->getCurPercentHP());
    
    std::string skillName = std::string("爆击-100");
    CCLabelTTF * label = CCLabelTTF::create(skillName.c_str(), "Thonburi", 26);
    this->addChild(label,99);
    ccColor3B color = ccRED;//{ 226, 121, 7};
    label->setColor(color);
    
    CCPoint labPos = pNodeRole->pNodeRole->getPosition();
    labPos.x += pNodeRole->pNodeRole->getContentSize().width * 1.2f;
    
    label->setPosition(labPos);
    
    CCPoint endPos = pNodeRole->pNodeRole->getPosition();
    
    CCSize  inputTextSize = label->getContentSize();
    
    CCAction * seq = CCSequence::create(
                                        CCDelayTime::create(ACTION_TIME_LABEL_SHOW_TIME),
                                        CCMoveBy::create(ACTION_TIME_SHOW_SKILL_NAME, CCPointMake(0, LABEL_MOVE_DISTANCE)),
                                        CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::callbackRemoveNodeWhenDidAction)),
                                        NULL);
    label->runAction(seq);
}

void SpecialBattleView::callbackRemoveNodeWhenDidAction(CCNode * pNode)
{
    this->removeChild(pNode, true);
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

void SpecialBattleView::countDown()
{
    this->setIsTouchForbidden(false);
    m_nCountTime = COUNT_DOWN_TIMES;
    this->schedule(schedule_selector(SpecialBattleView::countDownSchedule), COUNT_DOWN_INTERVAL, COUNT_DOWN_TIMES, 0);
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
    
    CCLabelTTF * label = CCLabelTTF::create(strChar, "Thonburi", 26);
    this->addChild(label,99);
    ccColor3B color = ccYELLOW;//{ 226, 121, 7};
    label->setColor(color);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint labPos = CCPointMake(screanSize.width * 0.5f, screanSize.width * 0.5f);
    
    label->setPosition(labPos);
    label->setScale(2);
    
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
    
    m_nCountTime = 0;
    
    std::string labString = std::string("雷霆万钧");
    
    CCLabelTTF * label = CCLabelTTF::create(labString.c_str(), "Thonburi", 20);
    this->addChild(label,99);
    ccColor3B color = ccYELLOW;//{ 226, 121, 7};
    label->setColor(color);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint labPos = CCPointMake(screanSize.width * 0.5f, screanSize.height * 0.5f);
    
    label->setPosition(labPos);
    label->setScale(2);
    
    CCAction * seq = CCSequence::create(
                                        CCDelayTime::create(ACTION_TIME_LABEL_SHOW_TIME),
                                        CCMoveBy::create(ACTION_TIME_SHOW_SKILL_NAME, CCPointMake(0, LABEL_MOVE_DISTANCE)),
                                        CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::callbackRemoveNodeWhenDidAction)),CCCallFunc::create(this, callfunc_selector(SpecialBattleView::attackerAnimation)),
                                        NULL);
    label->runAction(seq);
}

void SpecialBattleView::analyseBattleData()
{
    if(m_nRound == 0)
    {
        //this->setIsTouchForbidden(true);
    }
    
    this->unschedule(schedule_selector(SpecialBattleView::countDownSchedule));
    
    //播放一回合的动作
    Json::Value playList = battleResult["battleArray"]["playlist"];
    if (playList[m_nIndexList].isNull())
    {
        removeAndCleanSelf(0);
        return;
    }
    
    if (m_nRound == 2) 
    {
        //this->setIsTouchForbidden(false);
        m_nRound = 0;
        //return;
    }
    
    Json::Value tOneRound = playList[m_nIndexList++];
    
//    CC_SAFE_DELETE(pNodeAttacker);
//    CC_SAFE_DELETE(pNOdeDefener);
//    CC_SAFE_DELETE(pRoleAction);
    
    std::string teamId = tOneRound["teamId"].asString();
    if (teamId.compare("A") == 0) {
        pNodeAttacker = new GRole();
        pNodeAttacker->rolePosition = kGRolePositionUpOne;
        pNodeAttacker->pNodeRole = mMonsterSpriteList[0];
        pNodeAttacker->pCCProgressTimer = mHpProgressTimerList[2];
        pNodeAttacker->setMaxHp(100);
        pNodeAttacker->setCurHp(100);
        pNodeAttacker->setMaxHp(100);
        
        pNOdeDefener = new GRole();
        pNOdeDefener->rolePosition = kGRolePositionDownOne;
        pNOdeDefener->pNodeRole = mHeroSpriteList[0];
        pNOdeDefener->pCCProgressTimer = mHpProgressTimerList[0];
        pNOdeDefener->setMaxHp(100);
        pNOdeDefener->setCurHp(100);
        pNOdeDefener->setMaxHp(100);
        
        pRoleAction = new GRoleAction();
        pRoleAction->m_Attacker = kGRoleTypeMonster;
        pRoleAction->m_Defender = kGRoleTypeLeadingActor;
    }
    else {
        pNOdeDefener = new GRole();
        pNOdeDefener->rolePosition = kGRolePositionUpOne;
        pNOdeDefener->pNodeRole = mMonsterSpriteList[0];
        pNOdeDefener->pCCProgressTimer = mHpProgressTimerList[0];
        pNOdeDefener->setMaxHp(100);
        pNOdeDefener->setCurHp(100);
        pNOdeDefener->setMaxHp(100);
        
        pNodeAttacker = new GRole();
        pNodeAttacker->rolePosition = kGRolePositionDownOne;
        pNodeAttacker->pNodeRole = mHeroSpriteList[0];
        pNodeAttacker->pCCProgressTimer = mHpProgressTimerList[2];
        pNodeAttacker->setMaxHp(100);
        pNodeAttacker->setCurHp(100);
        pNodeAttacker->setMaxHp(100);
        
        pRoleAction = new GRoleAction();
        pRoleAction->m_Attacker = kGRoleTypeLeadingActor;
        pRoleAction->m_Defender = kGRoleTypeMonster;
    }
    
    this->showRoundNumber();
    
//    CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::showRoundNumber)),
    
    pAttackEffectNode = m_mapTeam[tOneRound["teamId"].asString()][tOneRound["actId"].asInt()];
    
    Json::FastWriter jasonWrite;
    CCLOG("%s", jasonWrite.write(playList[m_nIndexList]).c_str());
    
    m_nRound++;
}

void SpecialBattleView::showRoundNumber()
{   
    if ( m_nRound == 1 )
    {
        this->attackerAnimation();
        return;
    }
    char strChar[512];
    memset(strChar, 0, 512);
    sprintf(strChar,"第 %d 回合", m_nIndexList);
    
    CCLabelTTF * label = CCLabelTTF::create(strChar, "Thonburi", 20);
    this->addChild(label,99);
    ccColor3B color = ccYELLOW;//{ 226, 121, 7};
    label->setColor(color);
    
    CCSize screanSize = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint labPos = CCPointMake(screanSize.width * 0.5f, screanSize.height * 0.75f);
    
    label->setPosition(labPos);
    label->setScale(2);
    
    CCAction * seq;    
    if (pRoleAction->m_Attacker == kGRoleTypeLeadingActor)//操作者是主动攻击的
    {
        seq = CCSequence::create(
                                 CCDelayTime::create(ACTION_TIME_LABEL_SHOW_TIME),
                                 CCMoveBy::create(ACTION_TIME_SHOW_SKILL_NAME, CCPointMake(0, LABEL_MOVE_DISTANCE)),
                                 CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::countDown)),
                                 CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::callbackRemoveNodeWhenDidAction)),
                                 0);    }
    else {
        seq = CCSequence::create(
                                 CCDelayTime::create(ACTION_TIME_LABEL_SHOW_TIME),
                                 CCMoveBy::create(ACTION_TIME_SHOW_SKILL_NAME, CCPointMake(0, LABEL_MOVE_DISTANCE)),
                                 CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::attackerAnimation)),
                                 CCCallFuncN::create(this, callfuncN_selector(SpecialBattleView::callbackRemoveNodeWhenDidAction)),
                                 0);
    }

    label->runAction(seq);
}

void SpecialBattleView::pressControlButtonDice()
{
    if (m_nCountTime > 0)
    {
        this->unschedule(schedule_selector(SpecialBattleView::countDownSchedule));
        this->showDiceResult();
    }
}