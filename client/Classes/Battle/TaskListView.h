//
//  TaskListView.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-8-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_TaskListView_h
#define HelloWorld_TaskListView_h

#include "cocos2d.h"
#include "Basic.h"
#include "TaskBasic.h"
#include "BattleDefine.h"
#include "LuckySprite.h"
#include "BattleResultView.h"
#include "NPCDialogView.h"



class TaskListView : public cocos2d::CCLayer 
{
public:
    static bool getIsInTask();
    //
    LAYER_CREATE_FUNC(TaskListView);
    
    virtual void onEnter();
    
    void initLayer(const stPage *p_page, cocos2d::CCObject *target, cocos2d::SEL_CallFuncND pfnSelector);
    
    
    void oneTaskWasFinished(CCNode* node, void* data);
    
    void showNextTask(float dt);

private:
    cocos2d::CCPoint pBeginPoint;
    
    cocos2d::CCObject*       m_target;         //callback listener
    
    cocos2d::SEL_CallFuncND  m_pfnSelector;    //callback selector
    
    const stPage *p_pPage;      //Point of page
    
    EventType mEventType;       //Current task's event type
    
    stTask *p_CurTask;          //Current Task
    
    std::vector<stTask *> mTaskList;        //All task in this page
    
    cocos2d::CCLayer *p_CurLayer;       //Current Show Layer
    
    /*
     *@brief get current task
     */
    stTask * getCurTask(int task_id);
    
    /*
     *@brief get next task
     */
    stTask * getNextTask();
    
    /*
     *@brief get current task type
     */
    TaskType getCurrentTaskType();
    
    /*
     *@brief get the Event Type.
     */
    EventType getEventType();
    
    void showCurrentTask();

    void showDialogView();
    
    void showGeneralBattleView();
    
    void showSpecialBattleView();
    
    void showOpenBoxView();
    
    void removeAndCleanSelf(float dt);
    
    
};


#endif
