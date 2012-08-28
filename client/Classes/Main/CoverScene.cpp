//
//  Cover.cpp
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#include "CoverScene.h"
#include "ChapterScene.h"
#include "LevelDataManager.h"
#include "LuckySprite.h"
#include "NetManager.h"
#include "PageScene.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

#define TAG_BUTTON_BOOK 1
#define TAG_BUTTON_MAGIC 2
#define TAG_BUTTON_DAGGER 3
#define TAG_BUTTON_OPTION 4

USING_NS_CC;
USING_NS_CC_EXT;

Cover *Cover::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("Cover", CoverLoader::loader());
    
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/cover.ccbi", pOwner);
    
    Cover *pCover = static_cast<Cover *>(pNode);
    return pCover;
}

cocos2d::SEL_MenuHandler Cover::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMenuItemClicked", Cover::onMenuItemClicked);
    
    return NULL;
}
cocos2d::extension::SEL_CCControlHandler Cover::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", Cover::onCCControlButtonClicked );
    return NULL;
}
bool Cover::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode)
{
    return false;
}

void Cover::onMenuItemClicked(cocos2d::CCObject *pTarget)
{
    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pTarget);
    printf("tag %d\n",p->getTag());
}

void Cover::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    cocos2d::CCNode *p = static_cast<cocos2d::CCNode *>(pSender);
    printf("tag %d\n",p->getTag());
    
    switch (p->getTag()) 
    {
        case TAG_BUTTON_BOOK:
            menuBookCallback(pSender);
            break;
        case TAG_BUTTON_MAGIC:
            menuMagicCallback(pSender);
            break;
        case TAG_BUTTON_DAGGER:
            menuDaggerCallback(pSender);
            break;
        case TAG_BUTTON_OPTION:
            menuOptionCallback(pSender);
            break;            
        default:
            break;
    }    
}

CCScene* Cover::scene()
{
    CCScene * scene = NULL;
    do 
    {
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        Cover *layer = Cover::create(scene);
        CC_BREAK_IF(! layer);

        scene->addChild(layer);
    } while (0);

    return scene;
}

// on "init" you need to initialize your instance
bool Cover::init()
{
    CCTouchPageTurn::init();
    
    return true;
}

#include "NetManager.h"
void Cover::menuDaggerCallback(CCObject* pSender)
{
    NetManager::shareNetManager()->sendEx(kModeBattle, kDoFight3, callfuncND_selector(Cover::responseFight), this, "\"actorId\": %d", 2);
}

void Cover::responseFight(CCNode *pNode, void *data)
{
    Json::Value root;
    Json::Reader reader;
    
    if(reader.parse(NetManager::shareNetManager()->processResponse(data), root))
    {
        Json::Value playList = root["meta"]["out"]["battleArray"]["playlist"];
        for (int i = 0; i < playList.size(); i++) 
        {
            Json::Value tempRound = playList[i];
            CCLOG("第几轮%d", i+1);
            
            for (int j = 0; j < tempRound.size(); j++) 
            {
                Json::Value tempMember = tempRound[j];

            string tempString = "";
            switch (tempMember["type"].asInt()) {
                case 1:
                    tempString = "攻击";
                    break;
                case 2:
                    tempString = "爆击1";
                    break;
                case 3:
                    tempString = "爆击2";
                    break;
                case 4:
                    tempString = "破防";
                    break;
                case 5:
                    tempString = "吸血1";
                    break;
                case 6:
                    tempString = "吸血2";
                    break;
                case 7:
                    tempString = "受击";
                    break;
                case 8:
                    tempString = "闪避";
                    break;
                case 9:
                    tempString = "反震";
                    break;
            }
            CCLOG("队伍:%s, 角色:%d, 动作类型:%s, 伤害值:%.2f", tempMember["teamId"].asCString(), tempMember["actId"].asInt(), tempString.c_str(), tempMember["hurt"].asDouble());
            }
        }
    }
}

void Cover::menuMagicCallback(CCObject* pSender)
{
}

void Cover::menuBookCallback(CCObject* pSender)
{
    CCScene *pScene = Chapter::scene();
    
    CCTransitionPageTurn *pTp = CCTransitionPageTurn::create(TRANSITION_PAGE_INTERVAL_TIME, pScene, false);
    
    CCDirector::sharedDirector()->pushScene(pTp);
}

void Cover::menuCardCallback(CCObject* pSender)
{
}

void Cover::menuOptionCallback(CCObject* pSender)
{
    LevelDataManager::shareLevelDataManager()->reload();
}

void Cover::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

