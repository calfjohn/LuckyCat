//
//  TestController.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "TestController.h"
#include "testBasic.h"
#include "MShopLayer.h"
#include "LoginLayer.h"

#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"

#include "LoginTestLayerLoader.h"
#include "GameSettingLayer.h"

#include "GameSettingLayerLoader.h"
#include "GameSettingLayer.h"

#include "MTabLayer.h"
#include "MTabLayerLoader.h"

#include "MonsterFightView.h"
#include "BossFightView.h"


USING_NS_CC;
USING_NS_CC_EXT;

TestController::TestController()
{
    CCLayerColor::init();
    
    m_TitleVector.clear();
    m_ListView = NULL;
    
    this->InitLayer();
}

TestController::~TestController()
{
    CC_SAFE_DELETE(m_ListView);
}

void TestController::onEnter()
{
    CCLayerColor::onEnter();
    
    this->setColor(ccBLUE);
}

void TestController::InitLayer()
{
    
    for (int i = 0; i < 33; i++)
    {
        char strArray[100];
        memset(strArray, 0, 100);
        sprintf(strArray,"Test Cell + %d", i);
        std::string tileName(strArray);
        m_TitleVector.push_back(tileName);
    }
    
    m_TitleVector[0] = std::string("Shop ScrollView Test");
    
    m_TitleVector[1] = std::string("Login View");
    
    m_TitleVector[2] = std::string("Game Setting View");
    
    m_TitleVector[3] = std::string("Tab View");
    
    m_TitleVector[4] = std::string("Monster Fight");
    
    m_TitleVector[5] = std::string("Boss Fight");
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    this->setContentSize(size);
    
    //*/
    
    // list
    CCListView *list = CCListView::create(CCListViewModeVertical);
    CCSize tListSize = CCSizeMake( size.width * 0.75 , size.height * 0.75 );
    list->setContentSize(tListSize);
    list->setDelegate(this);
    list->setSeparatorStyle(CCListViewCellSeparatorStyleNone);
    list->setAnchorPoint(ccp(0,0));
    //list->setPosition( ccp( size.width*0.5 , size.height*0.5 ));
    list->setPosition( ccp( size.width * 0.125 , size.height * 0.125 ) );
    list->setColor(ccWHITE);
    this->addChild(list);
    
    m_ListView = list;
}

 TestScene* TestController::CreateTestScene(int nIdx)
{
    return NULL;
}


void TestController::CellButtonCallback(CCObject * pSender)
{
    
}

CCLayer * TestController::CreateLayer( int index )
{
    CCLayer *p_Layer = NULL;
    switch (index) {
        case 0:
        {
            MShopLayer *p_SLayer = MShopLayer::create();
            p_SLayer->initLayer();
            
            p_Layer = (CCLayer *) p_SLayer;
            
            break;
            
        }    
        case 1:
        {
            LoginLayer *p_SLayer = LoginLayer::create();
            p_SLayer->initLayer();
            
            p_Layer = (CCLayer *) p_SLayer;
            
            /* Create an autorelease CCNodeLoaderLibrary. */
            CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
            
            ccNodeLoaderLibrary->registerCCNodeLoader("LoginTestLayer", LoginTestLayerLoader::loader());
            
            /* Create an autorelease CCBReader. */
            cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
            ccbReader->autorelease();
            
            /* Read a ccbi file. */
            CCNode * node = ccbReader->readNodeGraphFromFile("ccb/src/", "ccb/LoginLayer.ccbi", this);
            
            LoginTestLayer *p_LoginTestLayer = (LoginTestLayer *)node;
            
            p_LoginTestLayer->initLayer();
            
            p_Layer->addChild(node);
            
            break;
            
        } 
        case 2:
        {
            /* Create an autorelease CCNodeLoaderLibrary. */
            CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
            
            ccNodeLoaderLibrary->registerCCNodeLoader("GameSettingLayer", GameSettingLayerLoader::loader());
            
            /* Create an autorelease CCBReader. */
            cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
            ccbReader->autorelease();
            
            /* Read a ccbi file. */
            CCNode * node = ccbReader->readNodeGraphFromFile("ccb/src/", "ccb/GameSettingLayer.ccbi", this);
            
            GameSettingLayer *p_GameSettingLayer = (GameSettingLayer *)node;
            
            p_GameSettingLayer->initLayer();
            
            p_Layer = (CCLayer *)node;
            
            break;
        }
        case 3:
        {
            /* Create an autorelease CCNodeLoaderLibrary. */
            CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
            
            ccNodeLoaderLibrary->registerCCNodeLoader("MTabLayer", MTabLayerLoader::loader());
            
            /* Create an autorelease CCBReader. */
            cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
            ccbReader->autorelease();
            
            /* Read a ccbi file. */
            CCNode * node = ccbReader->readNodeGraphFromFile("ccb/src/", "ccb/MTabLayer.ccbi", this);
            
            MTabLayer *p_TabLayer = (MTabLayer *)node;
            
            p_TabLayer->initLayer();
            
            p_Layer = (CCLayer *)p_TabLayer;
            
            break;
        }
        case 4:
        {
            MonsterFightView *pMonster = MonsterFightView::create();
            pMonster->initLayer();
            
            p_Layer = (CCLayer *)pMonster;
            break;
        }
        case 5:
        {
            BossFightView *pBoss = BossFightView::create();
            pBoss->initLayer();
            
            p_Layer = (CCLayer *)pBoss;
            break;
        }
        default:
        {
            MonsterFightView *pBoss = MonsterFightView::create();
            pBoss->initLayer();
            
            p_Layer = (CCLayer *)pBoss;
            break;
        }
    }
    
    if (p_Layer){
        CCDirector *pDirector = CCDirector::sharedDirector();
        CCScene * pScene = new TestScene();
        pScene->addChild(p_Layer);
        pDirector->replaceScene(pScene);
        
        
    }
    
    return p_Layer;
}

void TestController::CCListView_numberOfCells(CCListView *listView, CCListViewProtrolData *data)
{
    data->nNumberOfRows = m_TitleVector.size();
}
void TestController::CCListView_cellForRow(CCListView *listView, CCListViewProtrolData *data)
{
    CCSize listSize = m_ListView->getContentSize();  
    CCSize cellSize = CCSizeMake(listSize.width * 0.8, listSize.height / 8);  
    
    CCListViewCell *cell = CCListViewCell::node();  
    cell->setOpacity(0);  
    cell->setContentSize(cellSize);  
    cell->setSelectionColor(ccc4(( 11 * data->nRow)%255, 0, 0, 255)); 
    cell->setSelectionColor(ccc4( 155, 0, 0, 100));
    data->cell = cell;  
    
    const char * p_CharStr = m_TitleVector[data->nRow].c_str();
    CCLabelTTF *cellLabel = CCLabelTTF::create( p_CharStr, cellSize,kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter,"Arial", 18); 
    //cellLabel->setPosition(ccp(cellSize.width , cellSize.height )); 
    cellLabel->setAnchorPoint(CCPointZero);
    cellLabel->setPosition(CCPointZero);
    cellLabel->setColor(ccc3(255,( 7 * data->nRow)%255  , 0 ));
    cell->addChild(cellLabel);
    
    CCLayerColor *p_LayerColor = CCLayerColor::create(ccc4( 2,( 11 * data->nRow)%255, 0, 255), 15, 15);
    p_LayerColor->setAnchorPoint(ccp(1,0));
    p_LayerColor->setPosition(ccp(listSize.width - 20, 4));
    cell->addChild(p_LayerColor);
    
}
void TestController::CCListView_didClickCellAtRow(CCListView *listView, CCListViewProtrolData *data)
{
    CCLog("Click Cell %d / %d \n",data->nRow,m_TitleVector.size());
    
    this->CreateLayer(data->nRow);
}
void TestController::CCListView_didScrollToRow(CCListView *listView, CCListViewProtrolData *data)
{
    CCLog("CCListView_didScrollToRow %d / %d \n",data->nRow,(int)(data->nNumberOfRows));
    
//    unsigned int onePage = 8;
//    unsigned int curRow = data->nRow;
//    unsigned int curPage = ( 1.0 / onePage ) * curRow;
//    unsigned int toRow = curPage * onePage;
//    if ( toRow > curRow )
//    {
//        listView->scrollCellToFront(toRow - curRow, true);
//    }
//    else {
//        listView->scrollCellToBack(curRow - toRow, true);
//    }
}

CCNode *TestController::openTest(const char * pCCBFileName, const char * pCCNodeName, CCNodeLoader * pCCNodeLoader) {
    /* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("LoginTestLayer", LoginTestLayerLoader::loader());
    
    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    /* Read a ccbi file. */
    CCNode * node = ccbReader->readNodeGraphFromFile("ccb/src/", "ccb/LoginLayer.ccbi", this);
    
    return node;
}

void TestController::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent) {
    //
}