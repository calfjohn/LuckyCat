//
//  EventModule.h
//  HelloWorld
//
//  Created by MarucsChoo on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_EventModule_h
#define HelloWorld_EventModule_h

#include "EventBasic.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "cocos2d.h"

class EventModule
{
public:
    static EventModule* getShareInstance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new EventModule();
			m_pInstance->init();
		}
		return m_pInstance;
        
	}
    
protected:
    EventModule();
    virtual ~EventModule();
    
    void init();
    
    static EventModule *m_pInstance;
    
	class XLRelease
	{
	public:
		~XLRelease()
		{
			if(EventModule::m_pInstance)
			{
				delete EventModule::m_pInstance;
				EventModule::m_pInstance = NULL;
			}
		}
	};
	static XLRelease Garbo;
    
};
    

#endif
