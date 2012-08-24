//
//  EventDataManager.cpp
//  HelloWorld
//
//  Created by JamesChen on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "EventDataManager.h"
#include "CppSQLite3.h"
#include "cocos2d.h"
#include <algorithm>
#include "BasicFunction.h"

USING_NS_CC;

bool SortTalkById(stTalk *first,stTalk *second){
	if(first == NULL || second == NULL)
		return false;
	if(first->id > second->id)
		return false;
	else
        return true;
}

EventDataManager *EventDataManager::m_pInstance = NULL;
EventDataManager::XLRelease EventDataManager::Garbo;

EventDataManager::EventDataManager()
{
    mEventMap.clear();
    mTalkMap.clear();
    mNpcMap.clear();
    mCurEventMap.clear();
}

EventDataManager::~EventDataManager()
{
    this->deleteEventMap();
    this->deleteTalkMap();
    this->deleteNpcMap();
    this->deleteCurEventMap();
}

void EventDataManager::init()
{
    this->readDB();
}

void EventDataManager::deleteEventMap()
{
    for (std::map<int,stEvent *>::iterator _iter = mEventMap.begin(); _iter != mEventMap.end() ; _iter++ )
    {
        stEvent *tmpEvent = _iter->second;
        
        CC_SAFE_FREE(tmpEvent);
    }
    
    mEventMap.clear();
}

void EventDataManager::deleteTalkMap()
{
    for (std::map<int,stTalk *>::iterator _iter = mTalkMap.begin(); _iter != mTalkMap.end() ; _iter++ )
    {
        stTalk *tmpTalk = _iter->second;
        
        CC_SAFE_FREE(tmpTalk);
    }
    
    mTalkMap.clear();
}

void EventDataManager::deleteNpcMap()
{
    for (std::map<int,stNPC *>::iterator _iter = mNpcMap.begin(); _iter != mNpcMap.end() ; _iter++ )
    {
        stNPC *tmpNPC = _iter->second;
        
        CC_SAFE_FREE(tmpNPC);
    }
    
    mNpcMap.clear();
}

void EventDataManager::deleteCurEventMap()
{
    for (std::map<int,stEvent *>::iterator _iter = mCurEventMap.begin(); _iter != mCurEventMap.end() ; _iter++ )
    {
        stEvent *tmpEvent = _iter->second;
        
        CC_SAFE_FREE(tmpEvent);
    }
    
    mCurEventMap.clear();
}

void EventDataManager::setEventMap(std::vector<stEvent *> tmpVector)
{
    this->deleteEventMap();
    
    std::vector<stEvent *>::iterator _iter = tmpVector.begin();
    for (; _iter != tmpVector.end(); _iter++)
    {
        stEvent *tmpEvent = *_iter;
        
        mEventMap.insert(make_pair(tmpEvent->id, tmpEvent));
    }
}

void EventDataManager::setTalkMap(std::vector<stTalk *> tmpVector)
{
    this->deleteTalkMap();
    
    std::vector<stTalk *>::iterator _iter = tmpVector.begin();
    for (; _iter != tmpVector.end(); _iter++)
    {
        stTalk *tmpTalk = *_iter;
        
        mTalkMap.insert(make_pair(tmpTalk->id, tmpTalk));
    }
}

void EventDataManager::setNpcMap(std::vector<stNPC *> tmpVector)
{
    this->deleteNpcMap();
    
    std::vector<stNPC *>::iterator _iter = tmpVector.begin();
    for (; _iter != tmpVector.end(); _iter++)
    {
        stNPC *tmpNPC = *_iter;
        
        mNpcMap.insert(make_pair(tmpNPC->id, tmpNPC));
    }
}

stEvent * EventDataManager::getEvent(int EventId)
{
    std::map<int, stEvent*>::iterator _iter = mEventMap.find(EventId);
    if ( _iter != mEventMap.end() )
    {
        stEvent *tmpEvent = _iter->second;
        return tmpEvent;
    }
    else {
        return NULL;
    }
}

stNPC * EventDataManager::getNPC(int npcId)
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

stTalk * EventDataManager::getTalk(int talkId)
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

stEvent * EventDataManager::getCurEvent(int EventId)
{
    std::map<int, stEvent *>::iterator _iter = mCurEventMap.find(EventId);
    if ( _iter != mCurEventMap.end() )
    {
        stEvent *tmpTalk = _iter->second;
        return tmpTalk;
    }
    else
    {
        return NULL;
    }
}

bool EventDataManager::removeCurEvent(int EventId)
{
    std::map<int, stEvent *>::iterator _iter = mCurEventMap.find(EventId);
    if ( _iter != mCurEventMap.end() )
    {
        stEvent *tmpEvent = _iter->second;
        CC_SAFE_FREE(tmpEvent);
        return true;
    }
    else
    {
        return false;
    }
}

bool EventDataManager::addCurEvent(stEvent *tmpEvent)
{
    if ( NULL != tmpEvent )
    {
        std::map<int, stEvent *>::iterator _iter = mCurEventMap.find(tmpEvent->id);
        if ( _iter == mCurEventMap.end() )
        {
            mCurEventMap.insert(make_pair(tmpEvent->id, tmpEvent));
            return true;
        }
    }
    return false;
}

std::vector<stTalk *> EventDataManager::getAllTalk(int event_id)
{
    std::vector<stTalk *> tVectorRetTalk;
    std::map<int, stTalk *>::iterator _iter = mTalkMap.begin();
    
    std::vector<stTalk> talkVector;
    for ( ; _iter != mTalkMap.end(); _iter++)
    {
        stTalk *tmpTalk = _iter->second;
        
        if ( tmpTalk && tmpTalk->eventId == event_id )
        {
            tVectorRetTalk.push_back(tmpTalk);
            
            stTalk t = *tmpTalk;
            
            talkVector.push_back(t);
        }
    }
    
    sort(tVectorRetTalk.begin(), tVectorRetTalk.end(),SortTalkById);    
    std::vector<stTalk *> retVectorTalk;
    for (vector<stTalk *>::iterator it = tVectorRetTalk.begin(); it != tVectorRetTalk.end(); it++) {
        stTalk *_talk = *it;
        retVectorTalk.push_back(_talk);
    }
    return retVectorTalk;
}

std::vector<stEvent *> EventDataManager::getASeriesOfEvent(int event_id)
{
    printf("----get a series Event-------\n");
    std::vector<stEvent *> tVectorEvent;
    int tmpEventId = event_id;
    while (tmpEventId > 0 ) {
        stEvent *tmpEvent = getEvent(tmpEventId);
        tVectorEvent.push_back(tmpEvent);
        tmpEventId = tmpEvent->nextEventId;
        
        tmpEvent->print();
    }
    
    return tVectorEvent;
}

std::string EventDataManager::getDialogFromTalk( stTalk * tmpTalk )
{
    if ( !tmpTalk || tmpTalk->dialogList.size() == 0 )
    {
        return "";
    }
    else if ( tmpTalk->dialogList.size() == 1 )
    {
        return tmpTalk->dialogList[0];
    }
    else {
        int pos = randNumber(0,999)%tmpTalk->dialogList.size();
        return tmpTalk->dialogList[pos];
    }
}

#pragma Read SQLite
void EventDataManager::readDB()
{
    string strFullPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("config/LuckyCat.sqlite");
    CppSQLite3DB db;
    db.open(strFullPath.c_str());
	if (!db.isOpen())
	{
		return;
	}
    
    CppSQLite3Query result = db.execQuery("select * from dict_event;");
    
    std::vector<stEvent *> tEventVector;
	while(!result.eof())
	{
        stEvent *tEvent = new stEvent();
        tEvent->id = result.getIntField("id");
        tEvent->type = (LEventType)result.getIntField("type");
        std::string strTarget = result.getStringField("target");
        tEvent->targetId = separateStringToNumberVector(strTarget, ",");
        std::string strBonus = result.getStringField("bonus");
        std::vector<int> tmpBonusList = separateStringToNumberVector(strBonus, ",");
        
        if (tmpBonusList.size() > 0)
            CCAssert( tmpBonusList[0]*2 == tmpBonusList.size()-1, "Something error in sql field\n");
        for (int i = 1; tmpBonusList[0] != 0 && i+1 < tmpBonusList.size(); i+=2) {
            stGood _good;
            _good.id = tmpBonusList[i];
            _good.num = tmpBonusList[i+1];
            tEvent->bonus.push_back(_good);
        }
        
        tEvent->bonusRepeat = result.getIntField("bonus_repeat");
        tEvent->nextEventId = result.getIntField("next_event_id");
        tEvent->box_id = result.getIntField("box_id");
        
        tEventVector.push_back(tEvent);
        
        result.nextRow();
    }
    
    this->setEventMap(tEventVector);
    
    CppSQLite3Query result_1 = db.execQuery("select * from dict_npc_talk;");
    
    std::vector<stTalk *> tTalkVector;
	while(!result_1.eof())
	{
        stTalk *tTalk = new stTalk();
        tTalk->id = result_1.getIntField("id");
        tTalk->eventId = result_1.getIntField("event_id");
        std::string _dialog= result_1.getStringField("content");
        
        tTalk->dialogList = separateString(_dialog,"||");
        
        tTalk->npcId = result_1.getIntField("npc_id");
        tTalk->npcName = result_1.getStringField("npc_name");
        
        tTalkVector.push_back(tTalk);
        
        result_1.nextRow();
    }
    this->setTalkMap(tTalkVector);
    
    db.close();
}
