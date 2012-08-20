//
//  Page.h
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#ifndef __PAGE_SCENE_H__
#define __PAGE_SCENE_H__

#include "cocos2d.h"
#include "LevelDataManager.h"
#include "extensions/CCBReader/CCNodeLoader.h"
#include "extensions/CCBReader/CCLayerLoader.h"

class Page : public cocos2d::CCLayer
{
public:
    static Page *create(cocos2d::CCObject * pOwner);
    
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene(int chapterId, const stPage *pPage);
    
    // implement the "static node()" method manually
    LAYER_CREATE_FUNC(Page);
    
    void turnToPage(int chapterId, const stPage *pPage);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void registerWithTouchDispatcher(void);
    
protected:
    // a selector callback
    void menuBackCallback(CCObject* pSender);
        
    void fightCallback(CCNode* pNode, void* data);

    void nextPageCallback(CCNode* pNode, void* data);
    
    void showBattleView(CCObject *pSender);
    
    cocos2d::CCLabelTTF *m_title;
    cocos2d::CCLabelTTF *m_content;
    
    cocos2d::CCSprite *m_SpriteMonster;
    cocos2d::CCSprite *m_SpriteBg;
    
//    cocos2d::CCLabelTTF *m_monster;
//    cocos2d::CCLabelTTF *m_state;
//    cocos2d::CCLabelTTF *m_tips;
    int m_nChapterId;
    const stPage *m_pPage;
    
    cocos2d::CCPoint pBeginPoint;
    
};

class CCBReader;

class PageLoader : public cocos2d::extension::CCLayerLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(PageLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(Page);
};

#endif  // __PAGE_SCENE_H__