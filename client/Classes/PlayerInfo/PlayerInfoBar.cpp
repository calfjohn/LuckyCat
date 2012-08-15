/*
 * =====================================================================================
 *
 *       Filename:  PlayerInfoBar.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/7/30 17:13:50
 *       Revision:  none
 *
 *         Author:  lihex (lhx), hexuan.li@cocos2d-x.org
 *
 *    Copyright (c) 2012 厦门雅基软件有限公司. All rights reserved.
 *
 * =====================================================================================
 */

#include "Basic.h"
#include "PlayerInfoBar.h"
#include "TestPlayerInfoView.h"
#include "LuckySprite.h"
using namespace cocos2d;

#define INFO_MENU_ITEMS_COUNT 2
static const int scInfoMenuItems[INFO_MENU_ITEMS_COUNT]={
	kInfoMenuItemTypePlayer,
	kInfoMenuItemTypeEquipment
};

PlayerInfoBar::PlayerInfoBar()
:m_pPlayerIcon(NULL)
,m_pInfoItemsMenu(NULL)
,m_iSelectedMenuItem(kInfoMenuItemTypePlayer)
{

}

bool PlayerInfoBar::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());

		/*Set plyer head icon*/
		m_pPlayerIcon = CCMenuItemSprite::create(LuckySprite::create(39), LuckySprite::create(40), this, menu_selector(PlayerInfoBar::playIconClicked));
		m_pPlayerIcon->setAnchorPoint(CCPointZero);
		CCMenu *infoMenu = CCMenu::create(m_pPlayerIcon, NULL);		
		infoMenu->setPosition(CCPointZero);
		this->addChild(infoMenu);

		/*init info items hear*/
		m_pInfoItemsMenu = CCMenu::create();
		m_pInfoItemsMenu->setPosition(VisibleRect::left());

		for(int i=0; i<INFO_MENU_ITEMS_COUNT; ++i)
		{
			CCMenuItemSprite *item = NULL;
			int menuItemType = scInfoMenuItems[i];
			switch (menuItemType)
			{
			case kInfoMenuItemTypePlayer:
				item = CCMenuItemSprite::create(CCSprite::create("CloseNormal.png"), CCSprite::create("CloseSelected.png"), this, menu_selector(PlayerInfoBar::menuItemPlayerClicked));
				break;
			case kInfoMenuItemTypeEquipment:
				item = CCMenuItemSprite::create(CCSprite::create("CloseNormal.png"), CCSprite::create("CloseSelected.png"), this, menu_selector(PlayerInfoBar::menuItemEquipmentClicked));
				break;
			default:
				break;
			}	
			if(item)
			{
				item->setAnchorPoint(CCPointZero);
				item->setTag(scInfoMenuItems[i]);
				m_pInfoItemsMenu->addChild(item);
			}
		}
		m_pInfoItemsMenu->alignItemsVertically();
		m_pInfoItemsMenu->setVisible(false);
		this->addChild(m_pInfoItemsMenu);


		m_pPlayerInfoView = TestPlayerInfoView::create(this);
		//m_pPlayerInfoView->setPosition(ccp(40,100));
		this->addChild(m_pPlayerInfoView,1);
		m_pPlayerInfoView->setVisible(false);
        m_pPlayerInfoView->sendPlayerInfo();
		bRet = true;
	} while (0);

	return bRet;

}

void PlayerInfoBar::playIconClicked(CCObject* pSender)
{
	m_pInfoItemsMenu->setVisible(m_pInfoItemsMenu->isVisible()? false:true);
    //TestPlayerInfoView* info = (TestPlayerInfoView*)this->getChildByTag(m_iPlayerInfoViewTag);
	//info->setVisible(info->isVisible());
    m_pPlayerInfoView->setVisible(m_pPlayerInfoView->isVisible()? false:true);
	CCLog("Out put Menu!");
}

void PlayerInfoBar::menuItemPlayerClicked( cocos2d::CCObject *pSender )
{
	CCLog("PlayerInfoBar::menuItemPlayerClicked!");
	m_pPlayerInfoView->setVisible(m_pPlayerInfoView->isVisible()? false:true);
}

void PlayerInfoBar::menuItemEquipmentClicked( cocos2d::CCObject *pSender )
{
	CCLog("PlayerInfoBar::menuItemEquipmentClicked!");

}


