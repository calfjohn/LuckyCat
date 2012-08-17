//
//  TaskListView.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-8-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "TaskListView.h"
#include "BattleDefine.h"
#include "LevelDataManager.h"
#include "DictDataManager.h"
#include "TaskDataManager.h"
#include "NPCDialogView.h"
#include "GeneralBattleView.h"
#include "SpecialBattleView.h"
#include "OpenBoxView.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

static bool m_bIsInTask = false;

bool TaskListView::getIsInTask()
{
    return m_bIsInTask;
}

void TaskListView::onEnter()
{
    CCLayer::onEnter();
}

void TaskListView::initLayer(const stPage *p_page, CCObject *target, SEL_CallFuncND pfnSelector)
{
    mTaskType = kTaskTypeOneEventWasFinished;
    
    m_target = target;
    m_pfnSelector = pfnSelector;
    
    p_pPage = p_page;
    
    if ( p_pPage == NULL )return;
    
    mTaskList.clear();
    mTaskList = TaskDataManager::getShareInstance()->getASeriesOfTask(p_pPage->taskId);
    
    p_CurTask = getCurTask();
    
    this->showCurTask();
};

stTask * TaskListView::getCurTask()
{
    if ( mTaskList.empty() == false )
    {
        p_CurTask = mTaskList[0];
        
        switch (p_CurTask->type) {
            case kTaskTypeGeneralBattle:
            {
                mTaskType = kTaskTypeGeneralBattle;

                break;
            }
            case kTaskTypeDialogue:
            {
                mTaskType = kTaskTypeDialogue;
                break;
            }
            case kTaskTypeSpecialBattle:
            {
                mTaskType = kTaskTypeSpecialBattle;
            }
            default:
                break;
        }
    }
    else {
        p_CurTask = NULL;
    }
    
    return p_CurTask;
}

void TaskListView::popTask()
{
    if ( mTaskList.empty() == false )
    {
        std::vector<stTask *>::iterator _iter = mTaskList.begin();
        mTaskList.erase(_iter);
        
        if ( mTaskList.empty() == false )
        {
            p_CurTask = mTaskList[0];
            
            switch (p_CurTask->type) {
                case kTaskTypeGeneralBattle:
                {
                    mTaskType = kTaskTypeGeneralBattle;
                    break;
                }
                case kTaskTypeDialogue:
                {
                    mTaskType = kTaskTypeDialogue;
                    break;
                }
                case kTaskTypeSpecialBattle:
                {
                    mTaskType = kTaskTypeSpecialBattle;
                    break;
                }
                default:
                {
                    mTaskType = kTaskTypeFinishedEvent;
                    p_CurTask = NULL;
                    break;
                }
            }
        }
        else {
            mTaskType = kTaskTypeFinishedEvent;
            p_CurTask = NULL;
        }
    }
    else {
        mTaskType = kTaskTypeFinishedEvent;
        p_CurTask = NULL;
    }
}

TaskType TaskListView::getTaskType()
{
    return mTaskType;
}

void TaskListView::removeAndCleanSelf(float dt)
{
    m_bIsInTask = false;
    
    ((m_target)->*(m_pfnSelector))(this, NULL);
    
    CCLayer *pLayer = (CCLayer *)(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(TAG_BATTLE_LAYER));
    if ( pLayer )
    {
        pLayer->removeFromParentAndCleanup(true);
    }
}

void TaskListView::callbackTaskWasFinished(CCNode* node, void* data)
{
    this->scheduleOnce(schedule_selector(TaskListView::showNextTask), 0.1f);
}

void TaskListView::showCurTask()
{
    if ( mTaskType == kTaskTypeDialogue )
    {
        showDialogView();
    }
    else if ( mTaskType == kTaskTypeSpecialBattle )
    {
        showSpecialBattleView();
    }
    else if ( mTaskType == kTaskTypeGeneralBattle ){
        showGeneralBattleView();
    }
    else  if ( mTaskType == kTaskTypeFinishedEvent ||  mTaskType == kTaskTypeOneEventWasFinished ) {
        this->scheduleOnce(schedule_selector(TaskListView::removeAndCleanSelf), 0.05f);
    }
}

void TaskListView::showDialogView()
{
    NPCDialogView *tDialog = NPCDialogView::create(this);
    if (tDialog)
    {
        tDialog->setData(p_CurTask, this, callfuncND_selector(TaskListView::callbackTaskWasFinished));
        
        p_CurLayer = static_cast<cocos2d::CCLayer *>(tDialog);
        
        this->addChild(p_CurLayer);
    }
}

void TaskListView::showGeneralBattleView()
{
    GeneralBattleView *tGeneralBattle = GeneralBattleView::create(this);
    if (tGeneralBattle)
    {
        tGeneralBattle->setData(p_CurTask, this, callfuncND_selector(TaskListView::callbackTaskWasFinished));
        
        p_CurLayer = static_cast<cocos2d::CCLayer *>(tGeneralBattle);
        
        this->addChild(p_CurLayer);
        
        this->showOpenBoxView();
    }
}

void TaskListView::showSpecialBattleView()
{
    SpecialBattleView *tSpecialBattle = SpecialBattleView::create(this);
    if (tSpecialBattle)
    {
        tSpecialBattle->setData(p_CurTask, this, callfuncND_selector(TaskListView::callbackTaskWasFinished));
        
        p_CurLayer = static_cast<cocos2d::CCLayer *>(tSpecialBattle);
        
        this->addChild(p_CurLayer);
        
        this->showOpenBoxView();
    }
}

void TaskListView::showOpenBoxView()
{
    if ( p_CurTask && p_CurTask->box_id != -1 )
    {
        OpenBoxView *p = OpenBoxView::create(this);
        p->setTask(p_CurTask);
        this->addChild(p,99);
    }
}

void TaskListView::showNextTask(float dt)
{
    if ( p_CurLayer )
    {
        p_CurLayer->removeFromParentAndCleanup(true);
        
        p_CurLayer = NULL;
    }
    
    popTask();
    
    showCurTask();
}