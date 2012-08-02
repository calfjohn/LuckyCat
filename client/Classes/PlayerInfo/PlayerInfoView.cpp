/*
 * =====================================================================================
 *
 *       Filename:  PlayerInfoView.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2012/8/1 10:48:55
 *       Revision:  none
 *
 *         Author:  lihex
 *   Organization:  
 *
 * =====================================================================================
 */

#include "Basic.h"
#include "PlayerInfoView.h"

using namespace cocos2d;


PlayerInfoView::PlayerInfoView()
{

}

bool PlayerInfoView::init()
{	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 123, 234, 255), 230,300));
		
		CCLabelTTF *lable = CCLabelTTF::create("OK", "Arial", 30);
		lable->setPosition(VisibleRect::center());
		this->addChild(lable);
	
		bRet=true;

	}while(0);

	return bRet;
}
