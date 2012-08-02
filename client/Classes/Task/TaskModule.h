//
//  TaskModule.h
//  HelloWorld
//
//  Created by MarucsChoo on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_TaskModule_h
#define HelloWorld_TaskModule_h

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

class TaskModule
{
public:
    static TaskModule* getShareInstance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new TaskModule();
			m_pInstance->init();
		}
		return m_pInstance;
        
	}
    
protected:
    TaskModule();
    virtual ~TaskModule();
    
    void init();
    
    static TaskModule *m_pInstance;
    
	class XLRelease
	{
	public:
		~XLRelease()
		{
			if(TaskModule::m_pInstance)
			{
				delete TaskModule::m_pInstance;
				TaskModule::m_pInstance = NULL;
			}
		}
	};
	static XLRelease Garbo;
    
};
    

#endif
