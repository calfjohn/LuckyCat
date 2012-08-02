/*
 * =====================================================================================
 *
 *       Filename:  PlayerInfoView.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/8/1 10:48:22
 *       Revision:  none
 *
 *         Author:  lihex
 *   Organization:  
 *
 * =====================================================================================
 */



#ifndef  PLAYERINFOVIEW_INC
#define  PLAYERINFOVIEW_INC

#include "cocos2d.h"


class PlayerInfoView : public cocos2d::CCLayerColor
{
    public:
        PlayerInfoView ();                             /* constructor */
		virtual bool init();
		LAYER_CREATE_FUNC(PlayerInfoView);
    protected:


}; /* -----  end of class PlayerInfoView  ----- */

#endif   /* ----- #ifndef PLAYERINFOVIEW_INC  ----- */
