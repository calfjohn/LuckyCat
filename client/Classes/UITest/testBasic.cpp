#include "testBasic.h"
#include "TestController.h"

TestScene::TestScene()
{
    
    CCScene::init();
    
}

void TestScene::onEnter()
{
    CCScene::onEnter();

    //add the menu item for back to main menu
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//    CCLabelBMFont* label = CCLabelBMFont::create("MainMenu",  "fonts/arial16.fnt");
//#else
    CCLabelTTF* label = CCLabelTTF::create("MainMenu", "Arial", 20);
//#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(TestScene::MainMenuCallback));

    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( CCPointMake( s.width - 50, 25) );

    addChild(pMenu, 1);
}

void TestScene::MainMenuCallback(CCObject* pSender)
{
    CCScene* pScene = new TestScene();
    CCLayer* pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    CCDirector::sharedDirector()->replaceScene(pScene);
}
