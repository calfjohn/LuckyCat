//
//  TaskDataManager.h
//  HelloWorld
//
//  Created by MarucsChoo on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_TaskDataManager_h
#define HelloWorld_TaskDataManager_h

#include "TaskBasic.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "cocos2d.h"


class TaskDataManager
{
public:
    static TaskDataManager* getShareInstance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new TaskDataManager();
			m_pInstance->init();
		}
		return m_pInstance;
        
	}
    
    void setTaskMap(std::vector<stTask *> tmpVector);
    void setTalkMap(std::vector<stTalk *> tmpVector);
    void setNpcMap(std::vector<stNPC *> tmpVector);
    
    stTask *getTask(int taskId);
    stNPC *getNPC(int npcId);
    stTalk *getTalk(int talkId);
    
    /*
     *@brief get current task by taskId.
     *@return NULL when the the task is not exit int current task map.
     */
    stTask *getCurTask(int taskId);
    /*
     *@brief remove a task in curent task map
     *@return if return true. remove success. else failed.
     */
    bool removeCurTask(int taskId);
    bool addCurTask(stTask *tmpTask);
    
    /*
     *@brief get all task by task id.
     */
    std::vector<stTalk *> getAllTalk(int task_id);
private:
    
    std::map<int,stTask *> mTaskMap;    //task map
    std::map<int,stTalk *> mTalkMap;    //talk map
    std::map<int,stNPC *> mNpcMap;      //npc map
    
    std::map<int, stTask *> mCurTaskMap;   //all working task 
    
    void deleteTaskMap();
    void deleteTalkMap();
    void deleteNpcMap();
    void deleteCurTaskMap();
    
    void readDB();                      //read data for SQLite
    
protected:
    TaskDataManager();
    virtual ~TaskDataManager();
    
    void init();
    
    static TaskDataManager *m_pInstance;
    
	class XLRelease
	{
	public:
		~XLRelease()
		{
			if(TaskDataManager::m_pInstance)
			{
				delete TaskDataManager::m_pInstance;
				TaskDataManager::m_pInstance = NULL;
			}
		}
	};
	static XLRelease Garbo;

};

#endif
