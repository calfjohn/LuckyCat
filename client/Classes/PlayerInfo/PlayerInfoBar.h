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

class PlayerInfoBar : public cocos2d::CCLayer
{
    public:
		PlayerInfoBar();
		virtual bool init();
		LAYER_CREATE_FUNC(PlayerInfoBar);
		void playIconCliced(CCObject* pSender);

    protected:
		/*player head icon*/
		cocos2d::CCMenuItem *m_pPlayerIcon;
		/*player info items*/
		cocos2d::CCMenu	*m_pInfoItemsMenu;
		

}; /* -----  end of class PlayerInfoBar  ----- */

#endif   /* ----- #ifndef PLAYERINFOBAR_INC  ----- */
