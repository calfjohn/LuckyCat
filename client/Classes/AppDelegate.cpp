#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "LevelDataManager.h"
#include "DictDataManager.h"
#include "CoverScene.h"
#include "TaskDataManager.h"
#include "Basic.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
//     pDirector->enableRetinaDisplay(true);

    pDirector->setDepthTest(true);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    LevelDataManager::shareLevelDataManager();
    DictDataManager::shareDictDataManager();
    TaskDataManager::getShareInstance();
    
    // create a scene. it's an autorelease object
    CCScene *pScene = Cover::scene();

    // run
    pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


//////////////////////////////////////////////////////////////////////////
// implement VisableRect
//////////////////////////////////////////////////////////////////////////

// 获取Screen在View中的坐标 
const CCRect&  VisibleRect::rect()
{
	static CCRect s_rcVisible;
	if (0 == s_rcVisible.size.width)
	{
		//CCEGLView::sharedOpenGLView().getScreenRectInView(s_rcVisible);
		CCSize screenSize = CCEGLView::sharedOpenGLView().getSize();
		s_rcVisible = CCRectMake(0, 0, screenSize.width, screenSize.height);
	}

	return s_rcVisible;
}

const CCPoint& VisibleRect::center()
{
	static CCPoint s_ptCenter;
	if (0 == s_ptCenter.x)
	{
		CCRect rc = VisibleRect::rect();
		s_ptCenter.x = rc.origin.x + rc.size.width / 2;
		s_ptCenter.y = rc.origin.y + rc.size.height / 2;
	}
	return s_ptCenter;
}

const CCPoint& VisibleRect::top()
{
	static CCPoint s_ptTop;
	if (0 == s_ptTop.x)
	{
		CCRect rc = VisibleRect::rect();
		s_ptTop.x = rc.origin.x + rc.size.width / 2;
		s_ptTop.y = rc.origin.y + rc.size.height;
	}
	return s_ptTop;
}

const CCPoint& VisibleRect::topRight()
{
	static CCPoint s_ptTopRight;
	if (0 == s_ptTopRight.x)
	{
		CCRect rc = VisibleRect::rect();
		s_ptTopRight.x = rc.origin.x + rc.size.width;
		s_ptTopRight.y = rc.origin.y + rc.size.height;
	}
	return s_ptTopRight;
}

const CCPoint& VisibleRect::right()
{
	static CCPoint s_ptRight;
	if (0 == s_ptRight.x)
	{
		CCRect rc = VisibleRect::rect();
		s_ptRight.x = rc.origin.x + rc.size.width;
		s_ptRight.y = rc.origin.y + rc.size.height / 2;
	}
	return s_ptRight;
}

const CCPoint& VisibleRect::bottomRight()
{
	static CCPoint s_ptBottomRight;
	if (0 == s_ptBottomRight.x)
	{
		CCRect rc = VisibleRect::rect();
		s_ptBottomRight.x = rc.origin.x + rc.size.width;
		s_ptBottomRight.y = rc.origin.y;
	}
	return s_ptBottomRight;
}

const CCPoint& VisibleRect::bottom()
{
	static CCPoint s_ptBottom;
	if (0 == s_ptBottom.x)
	{
		CCRect rc = VisibleRect::rect();
		s_ptBottom.x = rc.origin.x + rc.size.width / 2;
		s_ptBottom.y = rc.origin.y;
	}
	return s_ptBottom;
}

const CCPoint& VisibleRect::bottomLeft()
{
	return VisibleRect::rect().origin;
}

const CCPoint& VisibleRect::left()
{
	static CCPoint s_ptLeft;
	static bool haveLeft;
	if (! haveLeft)
	{
		CCRect rc = VisibleRect::rect();
		s_ptLeft.x = rc.origin.x;
		s_ptLeft.y = rc.origin.y + rc.size.height / 2;

		haveLeft = true;
	}
	return s_ptLeft;
}

const CCPoint& VisibleRect::topLeft()
{
	static CCPoint s_ptTopLeft;
	static bool haveTopLeft;
	if (! haveTopLeft)
	{
		CCRect rc = VisibleRect::rect();
		s_ptTopLeft.x = rc.origin.x;
		s_ptTopLeft.y = rc.origin.y + rc.size.height;

		haveTopLeft = true;
	}
	return s_ptTopLeft;
}