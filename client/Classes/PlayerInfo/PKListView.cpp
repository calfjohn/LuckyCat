//
//  PKListView.cpp
//  HelloWorld
//
//  Created by Cocos2d-x on 12-8-29.
//
//

#include "PKListView.h"
#include "PKListViewCell.h"
#include "extensions/CCBReader/CCBSelectorResolver.h"
#include "extensions/CCBReader/CCBReader.h"
#include "extensions/CCBReader/CCNodeLoaderLibrary.h"
#include "NetManager.h"


USING_NS_CC;
USING_NS_CC_EXT;

//#include "extensions\CCListView\CCListViewCell.h"

PKListView::PKListView()
{
    m_bFresh = true;
}

PKListView::~PKListView()
{
}

CCNode* PKListView::createNodeForCCBI(const char *pCCBFileName , const char *pCCNodeName , cocos2d::extension::CCNodeLoader *pCCNodeLoader){
    /* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("PKListView", PKListViewLoader::loader());
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

PKListView *PKListView::create(cocos2d::CCObject * pOwner)
{
    cocos2d::extension::CCNodeLoaderLibrary * ccNodeLoaderLibrary = cocos2d::extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("PKListView", PKListViewLoader::loader());
    //ccNodeLoaderLibrary->registerCCNodeLoader("FuzzyBgView", FuzzyBgViewLoader::loader());
    //ccNodeLoaderLibrary->registerCCNodeLoader("PlayerInfoView", PlayerInfoViewLoader::loader());
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    
    CCNode * pNode = ccbReader->readNodeGraphFromFile("pub/", "ccb/pklist.ccbi", pOwner);
    
    PKListView *pInfoView = static_cast<PKListView *>(pNode);
    //pInfoView->m_pPlayerEquipInfoView = EquipInfoView::create(pInfoView);
    //pInfoView->m_pPlayerEquipInfoView->sendPlayerEquipInfoRequest();
    //pInfoView->m_playerInfoView = (PlayerInfoView*)pInfoView->createNodeForCCBI("ccb/playerinfo.ccbi", "PlayerInfoView", PlayerInfoViewLoader::loader());
    //pInfoView->addChild(pInfoView->m_playerInfoView);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    
    // 初始化控件ListView
    CCListView *listView = CCListView::create(CCListViewModeVertical);
    CCLOG("getAnchorPoint=%f,%f",listView->getAnchorPoint().x,listView->getAnchorPoint().y);
    CCSize listSize = CCSizeMake(160 , 230);
    listView->setContentSize(listSize);
    listView->setDelegate(pInfoView);
    //listView->setPosition(winSize.width - listSize.width / 2 , winSize.height - listSize.height / 2);
    float x = (winSize.width - listSize.width) / 2;
    float y = (winSize.height - listSize.height) / 2;
    listView->setPosition(x , y);
    //listView->setPosition(CCPointZero);
    //listView->setAnchorPoint(ccp(60, 90));
    pInfoView->addChild(listView,2);
    
    pInfoView->m_pListView = listView;
    
    pInfoView->sendPKListInfo();
    
    if (pInfoView)
    {
        CCNode *pBgNode = pInfoView->getChildByTag(0);
        pInfoView->registerTouchNode(pBgNode);
        
        //if (pPlayerInfoView->m_pBasicInfoView)
        //{
        //CCNode *pBgNode = pPlayerInfoView->m_pBasicInfoView->getChildByTag(902);
        //CCNode *pBgTitleNode = pPlayerInfoView->m_pBasicInfoView->getChildByTag(903);
        //pPlayerInfoView->registerTouchNode(pBgNode);
        //pPlayerInfoView->registerTouchNode(pBgTitleNode);
        //}
        
        pInfoView->setIsTouchAreaEnabled(true);
    }
    
    return pInfoView;
}

cocos2d::SEL_MenuHandler PKListView::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "basicViewBtnCallback", PKListView::basicViewBtnCallback);
    
    return NULL;
}

cocos2d::extension::SEL_CCControlHandler PKListView::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, cocos2d::CCString * pSelectorName){
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCCControlButtonClicked", PKListView::onCCControlButtonClicked);
    return NULL;
}

bool PKListView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, cocos2d::CCString * pMemberVariableName, cocos2d::CCNode * pNode){
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLaberTitle", cocos2d::CCLabelTTF * , this->mLaberTitle);
    return false;
}

void PKListView::onMenuItemClicked(cocos2d::CCObject *pTarget){
    
}

void PKListView::onCCControlButtonClicked(cocos2d::CCObject *pSender, cocos2d::extension::CCControlEvent pCCControlEvent){
    CCLog("onCCControlButtonClicked success!!!");
}

void PKListView::registerWithTouchDispatcher(void){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -900, false);
}

void PKListView::visit()
{
    CCLayer::visit();
    if (m_bFresh) {
        m_pListView->reload();
        m_bFresh = false;
    }
}

void PKListView::CCListView_numberOfCells(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    data->nNumberOfRows = m_pDataList.size();
    //CCLOG("PKListView::CCListView_numberOfCells=%u,NumberOfRows=%u,point=%d",m_pDataList->size(),data->nNumberOfRows,data);
}

void PKListView::CCListView_cellForRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    CCSize listSize = m_pListView->getContentSize();
    CCSize cellSize = CCSizeMake(listSize.width, listSize.height / 10);
    
    CCListViewCell *cell = CCListViewCell::node();
    cell->setOpacity(0);
    cell->setContentSize(cellSize);
    cell->setSelectionColor(ccc4(255, 0, 0, 255));
    data->cell = cell;
    
    std::list<stPKInfo>::iterator it = m_pDataList.begin();
    //CCLOG("PKListView::CCListView_cellForRow   data->nRow=%u,NumberOfRows=%u,point=%d",data->nRow,data->nNumberOfRows,data);
    for (unsigned int i=0; i<data->nRow; ++i) {
        ++it;
    }
    //CCLabelTTF *cellLabel = CCLabelTTF::create(((std::string) *it).c_str(), "Arial", 15);
    //cellLabel->setPosition(ccp(cellSize.width / 2, cellSize.height / 2));
    PKListViewCell *item = (PKListViewCell*)this->createNodeForCCBI("ccb/pklist_scroll.ccbi", "PKListViewCell", PKListViewCellLoader::loader());
    
    item->setCellUserId((*it).pkUserId);
    item->setCellUserLevel((*it).pkUserLevel);
    item->setCellUserNickName((*it).pkUserNickName.c_str());
    
    cell->addChild(item);
}

void PKListView::CCListView_didClickCellAtRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    /*char info[100];
    CCLOG("PKListView::CCListView_didClickCellAtRow nRow=%u,nNumberOfRows=%u,point=%d",data->nRow,data->nNumberOfRows,data);
    sprintf(info, "No. %d Row", data->nRow);
    m_InfoLabel->setString(info);*/
}

void PKListView::CCListView_didScrollToRow(cocos2d::extension::CCListView *listView, cocos2d::extension::CCListViewProtrolData *data)
{
    //m_InfoLabel->setString("Scrolling...");
}


void PKListView::sendPKListInfo(){
    NetManager::shareNetManager()->sendEx(kModePK, kDoGetPKList, callfuncND_selector(PKListView::responesPKListInfo), this, "");
}
void PKListView::responesPKListInfo(CCNode *pNode, void* data){
    if (data != NULL) {
        Json::Value root;
        Json::Reader reader;
        
        if(reader.parse(NetManager::shareNetManager()->processResponse(data), root)){
            Json::Value out = root["meta"]["out"];
            for(int i = 0;i<out.size();i++){
                //std::cout << "i = " << i << " " << out[i]["equip_id"].asInt() << std::endl;
                stPKInfo info;
                info.pkUserId = out[i]["uuid"].asInt();
                info.pkUserLevel = out[i]["level"].asInt();
                info.pkUserNickName = out[i]["nickname"].asString();
                m_pDataList.push_back(info);
            }
        }
    }
    
    m_pListView->reload();
}

void PKListView::notificationTouchEvent(LTouchEvent tLTouchEvent){
    if (tLTouchEvent == kLTouchEventOutsideTouchArea) {
        removeFromParentAndCleanup(true);
        CCLog("kLTouchEvent OutsideTouchArea");
    }
    else if (tLTouchEvent == kLTouchEventInsideTouchArea)
    {
        CCLog("kLTouchEvent InsideTouchArea");
    }
    else {
        CCLog("kLTouchEvent Other...");
    }
}