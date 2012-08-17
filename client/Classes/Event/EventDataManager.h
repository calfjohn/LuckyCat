//
//  EventDataManager.h
//  HelloWorld
//
//  Created by MarucsChoo on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_EventDataManager_h
#define HelloWorld_EventDataManager_h

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

class EventDataManager
{
public:
    static EventDataManager* getShareInstance(void)
	{
		if (!m_pInstance)
		{
			m_pInstance = new EventDataManager();
			m_pInstance->init();
		}
		return m_pInstance;
        
	}
    
    void setEventMap(std::vector<stEvent *> tmpVector);
    void setTalkMap(std::vector<stTalk *> tmpVector);
    void setNpcMap(std::vector<stNPC *> tmpVector);
    
    stEvent *getEvent(int EventId);
    stNPC *getNPC(int npcId);
    stTalk *getTalk(int talkId);
    
    /*
     *@brief get current Event by EventId.
     *@return NULL when the the Event is not exit int current Event map.
     */
    stEvent *getCurEvent(int EventId);
    /*
     *@brief remove a Event in curent Event map
     *@return if return true. remove success. else failed.
     */
    bool removeCurEvent(int EventId);
    bool addCurEvent(stEvent *tmpEvent);
    
    /*
     *@brief get all talk by Event id.
     */
    std::vector<stTalk *> getAllTalk(int Event_id);
    
    /*
     *@brief get a series of Event by a first Event of one page
     */
    std::vector<stEvent *> getASeriesOfEvent(int Event_id);
    
    std::string getDialogFromTalk( stTalk * tmpTalk );
private:
    
    std::map<int,stEvent *> mEventMap;    //Event map
    std::map<int,stTalk *> mTalkMap;    //talk map
    std::map<int,stNPC *> mNpcMap;      //npc map
    
    std::map<int, stEvent *> mCurEventMap;   //all working Event 
    
    void deleteEventMap();
    void deleteTalkMap();
    void deleteNpcMap();
    void deleteCurEventMap();
    
    void readDB();                      //read data for SQLite
    
protected:
    EventDataManager();
    virtual ~EventDataManager();
    
    void init();
    
    static EventDataManager *m_pInstance;
    
	class XLRelease
	{
	public:
		~XLRelease()
		{
			if(EventDataManager::m_pInstance)
			{
				delete EventDataManager::m_pInstance;
				EventDataManager::m_pInstance = NULL;
			}
		}
	};
	static XLRelease Garbo;

};

#endif
