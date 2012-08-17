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

class Page : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
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
    cocos2d::CCLabelTTF *m_monster;
    cocos2d::CCLabelTTF *m_state;
    cocos2d::CCLabelTTF *m_tips;
    int m_nChapterId;
    const stPage *m_pPage;
    
    cocos2d::CCPoint pBeginPoint;
    
};

#endif  // __PAGE_SCENE_H__