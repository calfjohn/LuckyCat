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
using namespace cocos2d;

PlayerInfoBar::PlayerInfoBar()
:m_pPlayerIcon(NULL)
,m_pInfoItemsMenu(NULL)
{

}

bool PlayerInfoBar::init()
{
	bool bRet = false;
	do 
	{
		//CC_BREAK_IF(CCLayer::init());
		CCLayer::init();

		/*Set plyer head icon*/
		m_pPlayerIcon = CCMenuItemSprite::create(CCSprite::create("head.png"), CCSprite::create("head2.png"), this, menu_selector(PlayerInfoBar::playIconCliced));
		m_pPlayerIcon->setAnchorPoint(CCPointZero);
		CCMenu *infoMenu = CCMenu::create(m_pPlayerIcon, NULL);		
		infoMenu->setPosition(CCPointZero);
		this->addChild(infoMenu);

		/*init info items hear*/
		m_pInfoItemsMenu = CCMenu::create();
		m_pInfoItemsMenu->setPosition(VisibleRect::left());
		for(int i=0; i<5; ++i)
		{
			CCMenuItemSprite *item = CCMenuItemSprite::create(CCSprite::create("CloseNormal.png"), CCSprite::create("CloseSelected.png"), this, menu_selector(PlayerInfoBar::playIconCliced));
			item->setAnchorPoint(CCPointZero);
			m_pInfoItemsMenu->addChild(item);
		}
			m_pInfoItemsMenu->alignItemsVertically();
		this->addChild(m_pInfoItemsMenu);

		bRet = true;
	} while (0);

	return bRet;

}

void PlayerInfoBar::playIconCliced(CCObject* pSender)
{
	m_pInfoItemsMenu->setVisible(m_pInfoItemsMenu->isVisible()? false:true);
	CCLog("Out put Menu!");
}


