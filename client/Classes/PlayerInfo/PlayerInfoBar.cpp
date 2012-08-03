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
 *         Author:  lihx
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Basic.h"
#include "PlayerInfoBar.h"
#include "PlayerInfoView.h"
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
		m_pPlayerIcon = CCMenuItemSprite::create(CCSprite::create("head.png"), CCSprite::create("head2.png"), this, menu_selector(PlayerInfoBar::playIconClicked));
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


		m_pPlayerInfoView = PlayerInfoView::create();
		m_pPlayerInfoView->setPosition(ccp(40,100));
		this->addChild(m_pPlayerInfoView);
		m_pPlayerInfoView->setVisible(false);

		bRet = true;
	} while (0);

	return bRet;

}

void PlayerInfoBar::playIconClicked(CCObject* pSender)
{
	m_pInfoItemsMenu->setVisible(m_pInfoItemsMenu->isVisible()? false:true);
	m_pPlayerInfoView->setVisible(m_pInfoItemsMenu->isVisible());
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


