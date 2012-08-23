//
//  EventBasic.h
//  HelloWorld
//
//  Created by MarucsChoo on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_EventBasic_h
#define HelloWorld_EventBasic_h

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "cocos2d.h"
#include "Basic.h"



enum LEventType {
    kLEventTypeGeneralBattle          =   0,   //general battle
    kLEventTypeDialogue               =   1,    //Dialogue
    kLEventTypeSpecialBattle          =   2,     //Special battle
    kLEventTypeOneEventWasFinished    =   3,
    kLEventTypeFinishedEvent          =   4,         //event was finished
    kLEventTypeNone                   =   5       //There is no event
};

//stNPC have info of npc's name and image
typedef struct
{
    int id;             //id of NPC
	std::string name;	//name of NPC
	std::string image;	//name of image
}stNPC;

typedef struct
{
	int	id;				//id of event.
	LEventType type;			//type of event. 
    std::vector<int> targetId;		//id of target.
	std::vector<stGood> bonus;		//bonus of event.
	int nextEventId;		//next event follow this event.
    int box_id;             //id of treasure chests
	bool bonusRepeat;	//if bonusRepeat is true, player can get bonus again.
    
    void print()
    {
        printf("---- stEvent -----\n");
        printf("id %d\n", id);
        printf("type %d\n", type);
        for ( int i=0; i<targetId.size(); i++ )
        {
            printf("%d target--> %d\n",i,targetId[i]);
        }
        printf("bonus\n");
        for ( int i=0; i<bonus.size(); i++ )
        {
            bonus[i].print();
        }
        printf("nextEventId %d\n", nextEventId);
        printf("box_id %d\n", box_id);
        printf("bonusRepeat %d\n", bonusRepeat);
    }
}stEvent;

class stTalk
{
public:
	int id;				//id of talk.
    std::vector<std::string> dialogList;     //list of dialog
	int npcId;			//if npcId is 0, lead role is talk. else it is a monster.
    int eventId;
    std::string npcName;
    
    void print()
    {
        printf("---- stTalk -----\n");
        printf("id %d\n", id);
        printf("npcId %d\n", npcId);
        printf("eventId %d\n", eventId);
        printf("npcName %s\n", npcName.c_str());
        
        for( int i = 0; i < dialogList.size(); i++ )
        {
            printf("Dialog %d: %s\n",i,dialogList[i].c_str());
        }
    }
    bool operator < (const stTalk &m)const {
        return id < m.id;
    }
    bool operator > (const stTalk &m)const {
        return id > m.id;
    }
    bool operator < (const stTalk *m)const {
        return id < m->id;
    }
    bool operator > (const stTalk *m)const {
        return id > m->id;
    }
};

typedef int BattleProcess;  //Temporary data of battle. It's will be replace by Lijun.

typedef  struct LEventData
{
    LEventData()
    :m_bBoxIsOpened(false),
    m_bBattleResultIsShowed(false),
    id(0),
    pBattle(NULL),
    pStEvent(NULL)
    {
        
    }
    ~LEventData()
    {
        targetId.clear();
        bonus.clear();
    }
    int getTarget()
    {
        if ( this->targetId.empty() == false )return this->targetId[0];
        else {
            return 0;
        }
    }
    std::vector<stGood> getBouns()
    {
        return this->bonus;
    }
    bool getBattleResultIsShowed()
    {
        if (this->m_bBattleResultIsShowed == false && ( this->type == kLEventTypeGeneralBattle ||  this->type == kLEventTypeSpecialBattle ) )
        {
            return false;
        }
        else return true;
    }
    void setBattleResultIsShowed()
    {
        this->m_bBattleResultIsShowed = true;
    }
    
    stEvent *pStEvent;                //Dict Event Struct
    
	int	id;                   //id of event.
	LEventType type;                //type of event.
    std::vector<int> targetId;		//id of target.
	std::vector<stGood> bonus;		//bonus of event.
    
    int box_id;
    std::vector<stGood> boxAward;   //if box_id is not equal to -1. boxAward have some goods
    
    BattleProcess *pBattle;         //Battle process struct. GeneralBattleView. 
    
    bool m_bBoxIsOpened;              //The box is opened.
    bool m_bBattleResultIsShowed;
}LEventData;

enum EventLayerTag
{
    kTagLayerBattle = 1,
    kTagLayerHeroHead,
    kTagLayerHeroInfo,
    kTagLayerDialog,
    kTagLayerOpenBox,
    kTagLayerOpenBoxResult,
    kTagLayerBattleResult
};


#endif
