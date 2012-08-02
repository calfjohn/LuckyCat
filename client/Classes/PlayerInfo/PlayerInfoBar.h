/*
 * =====================================================================================
 *
 *       Filename:  PlayerInfoBar.h
 *
 *    Description:  UI controller, Display player info 
 *
 *        Version:  1.0
 *        Created:  2012/7/30 17:13:29
 *       Revision:  none
 *
 *         Author:  lihex
 *   Organization:  
 *
 * =====================================================================================
 */


#ifndef  PLAYERINFOBAR_INC
#define  PLAYERINFOBAR_INC

#include "cocos2d.h"

enum InfoMenuItemType {
	kInfoMenuItemTypePlayer          = 0,
	kInfoMenuItemTypeEquipment		 = 1,
};

class PlayerInfoView;
class PlayerInfoBar : public cocos2d::CCLayer
{
    public:
		PlayerInfoBar();
		virtual bool init();
		LAYER_CREATE_FUNC(PlayerInfoBar);
		
		/*menu click callback*/
		void playIconClicked(cocos2d::CCObject *pSender);
		void menuItemPlayerClicked(cocos2d::CCObject *pSender);
		void menuItemEquipmentClicked(cocos2d::CCObject *pSender);


    protected:
		/*player head icon*/
		cocos2d::CCMenuItem *m_pPlayerIcon;
		/*player info items*/
		cocos2d::CCMenu	*m_pInfoItemsMenu;

		CC_SYNTHESIZE(int, m_iSelectedMenuItem, SelectedMenuItem);
		PlayerInfoView *m_pPlayerInfoView;

}; /* -----  end of class PlayerInfoBar  ----- */

#endif   /* ----- #ifndef PLAYERINFOBAR_INC  ----- */