//
//  TaskDataManager.cpp
//  HelloWorld
//
//  Created by JamesChen on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "TaskDataManager.h"
#include "CppSQLite3.h"
#include "cocos2d.h"

USING_NS_CC;

TaskDataManager *TaskDataManager::m_pInstance = NULL;
TaskDataManager::XLRelease TaskDataManager::Garbo;

TaskDataManager::TaskDataManager()
{
    mTaskMap.clear();
    mTalkMap.clear();
    mNpcMap.clear();
    mCurTaskMap.clear();
}

TaskDataManager::~TaskDataManager()
{
    this->deleteTaskMap();
    this->deleteTalkMap();
    this->deleteNpcMap();
    this->deleteCurTaskMap();
}

void TaskDataManager::init()
{
    this->readDB();
}

void TaskDataManager::deleteTaskMap()
{
    for (std::map<int,stTask *>::iterator _iter = mTaskMap.begin(); _iter != mTaskMap.end() ; _iter++ )
    {
        stTask *tmpTask = _iter->second;
        
        CC_SAFE_FREE(tmpTask);
    }
    
    mTaskMap.clear();
}

void TaskDataManager::deleteTalkMap()
{
    for (std::map<int,stTalk *>::iterator _iter = mTalkMap.begin(); _iter != mTalkMap.end() ; _iter++ )
    {
        stTalk *tmpTalk = _iter->second;
        
        CC_SAFE_FREE(tmpTalk);
    }
    
    mTalkMap.clear();
}

void TaskDataManager::deleteNpcMap()
{
    for (std::map<int,stNPC *>::iterator _iter = mNpcMap.begin(); _iter != mNpcMap.end() ; _iter++ )
    {
        stNPC *tmpNPC = _iter->second;
        
        CC_SAFE_FREE(tmpNPC);
    }
    
    mNpcMap.clear();
}

void TaskDataManager::deleteCurTaskMap()
{
    for (std::map<int,stTask *>::iterator _iter = mCurTaskMap.begin(); _iter != mCurTaskMap.end() ; _iter++ )
    {
        stTask *tmpTask = _iter->second;
        
        CC_SAFE_FREE(tmpTask);
    }
    
    mCurTaskMap.clear();
}

void TaskDataManager::setTaskMap(std::vector<stTask *> tmpVector)
{
    this->deleteTaskMap();
    
    std::vector<stTask *>::iterator _iter = tmpVector.begin();
    for (; _iter != tmpVector.end(); _iter++)
    {
        stTask *tmpTask = *_iter;
        
        mTaskMap.insert(make_pair(tmpTask->id, tmpTask));
    }
}

void TaskDataManager::setTalkMap(std::vector<stTalk *> tmpVector)
{
    this->deleteTalkMap();
    
    std::vector<stTalk *>::iterator _iter = tmpVector.begin();
    for (; _iter != tmpVector.end(); _iter++)
    {
        stTalk *tmpTalk = *_iter;
        
        mTalkMap.insert(make_pair(tmpTalk->id, tmpTalk));
    }
}

void TaskDataManager::setNpcMap(std::vector<stNPC *> tmpVector)
{
    this->deleteNpcMap();
    
    std::vector<stNPC *>::iterator _iter = tmpVector.begin();
    for (; _iter != tmpVector.end(); _iter++)
    {
        stNPC *tmpNPC = *_iter;
        
        mNpcMap.insert(make_pair(tmpNPC->id, tmpNPC));
    }
}

stTask * TaskDataManager::getTask(int taskId)
{
    std::map<int, stTask*>::iterator _iter = mTaskMap.find(taskId);
    if ( _iter != mTaskMap.end() )
    {
        stTask *tmpTask = _iter->second;
        return tmpTask;
    }
    else {
        return NULL;
    }
}

stNPC * TaskDataManager::getNPC(int npcId)
{
    std::map<int, stNPC *>::iterator _iter = mNpcMap.find(npcId);
    if ( _iter != mNpcMap.end() )
    {
        stNPC *tmpNpc = _iter->second;
        return tmpNpc;
    }
    else {
        return NULL;
    }
}

stTalk * TaskDataManager::getTalk(int talkId)
{
    std::map<int, stTalk *>::iterator _iter = mTalkMap.find(talkId);
    if ( _iter != mTalkMap.end() )
    {
        stTalk *tmpTalk = _iter->second;
        return tmpTalk;
    }
    else
    {
        return NULL;
    }
}

stTask * TaskDataManager::getCurTask(int taskId)
{
    std::map<int, stTask *>::iterator _iter = mCurTaskMap.find(taskId);
    if ( _iter != mCurTaskMap.end() )
    {
        stTask *tmpTalk = _iter->second;
        return tmpTalk;
    }
    else
    {
        return NULL;
    }
}

bool TaskDataManager::removeCurTask(int taskId)
{
    std::map<int, stTask *>::iterator _iter = mCurTaskMap.find(taskId);
    if ( _iter != mCurTaskMap.end() )
    {
        stTask *tmpTask = _iter->second;
        CC_SAFE_FREE(tmpTask);
        return true;
    }
    else
    {
        return false;
    }
}

bool TaskDataManager::addCurTask(stTask *tmpTask)
{
    if ( NULL != tmpTask )
    {
        std::map<int, stTask *>::iterator _iter = mCurTaskMap.find(tmpTask->id);
        if ( _iter == mCurTaskMap.end() )
        {
            mCurTaskMap.insert(make_pair(tmpTask->id, tmpTask));
            return true;
        }
    }
    return false;
}

std::vector<stTalk *> TaskDataManager::getAllTalk(int task_id)
{
    printf("------getAllTalk-------\n");
    std::vector<stTalk *> tVectorRetTalk;
    std::map<int, stTalk *>::iterator _iter = mTalkMap.begin();
    for ( ; _iter != mTalkMap.end(); _iter++)
    {
        stTalk *tmpTalk = _iter->second;
        if ( tmpTalk && tmpTalk->taskId == task_id )
        {
            tVectorRetTalk.push_back(tmpTalk);
        }
    }
    
    sort(tVectorRetTalk.begin(), tVectorRetTalk.end());
    
    for (vector<stTalk *>::iterator it = tVectorRetTalk.begin(); it != tVectorRetTalk.end(); it++) {
        stTalk *_talk = *it;
        _talk->print();
    }
    return tVectorRetTalk;
}

#pragma Read SQLite
void TaskDataManager::readDB()
{
    string strFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/LuckyCat.sqlite");
    CppSQLite3DB db;
    db.open(strFullPath.c_str());
	if (!db.isOpen())
	{
		return;
	}
    
    CppSQLite3Query result = db.execQuery("select * from task;");
    
    std::vector<stTask *> tTaskVector;
	while(!result.eof())
	{
        stTask *tTask = new stTask();
        tTask->id = result.getIntField("id");
        tTask->type = (TaskType)result.getIntField("type");
        tTask->targetId = result.getIntField("target_id");
        tTask->bonusId = result.getIntField("bonus_id");
        tTask->bonusRepeat = result.getIntField("bonus_repeat");
        tTask->nextTaskId = result.getIntField("next_task_id");
        
        tTaskVector.push_back(tTask);
        tTask->print();
        
        result.nextRow();
    }
    
    this->setTaskMap(tTaskVector);
    
    CppSQLite3Query result_1 = db.execQuery("select * from npc_talk;");
    
    std::vector<stTalk *> tTalkVector;
	while(!result_1.eof())
	{
        stTalk *tTalk = new stTalk();
        tTalk->id = result_1.getIntField("id");
        tTalk->taskId = result_1.getIntField("task_id");
        tTalk->dialog = result_1.getStringField("content");
        tTalk->npcId = result_1.getIntField("npc_id");
        tTalk->npcName = result_1.getStringField("npc_name");
        
        tTalkVector.push_back(tTalk);
        tTalk->print();
        
        result_1.nextRow();
    }
    this->setTalkMap(tTalkVector);
    
    db.close();
}