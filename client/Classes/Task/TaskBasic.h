//
//  TaskBasic.h
//  HelloWorld
//
//  Created by MarucsChoo on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_TaskBasic_h
#define HelloWorld_TaskBasic_h

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "cocos2d.h"

using namespace std;

//任务类型约定：
//0，普通战斗
//1，对话
//2，特殊战斗
enum TaskType {
    generalBattle   =   0,   //general battle
    DialogueTask    =   1,    //Dialogue
    specialBattle   =   2     //Special battle
};

enum EventType {
    talkEvent           = 1,
    monsterBattleEvent  = 0,
    bossBattleEvent     = 2,
    oneEventWasFinished = 3,
    finishedEvent       = 4         //event was finished
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
	int	id;				//id of task.
	TaskType type;			//type of task. 0 main task, 1 side task.
	int targetId;		//id of target.
	int bonusId;		//bonus of task.
	int nextTaskId;		//next task follow this task.
	//int npcTalkId;		//a talk about this task.
	bool bonusRepeat;	//if bonusRepeat is true, player can get bonus again.
    
    void print()
    {
        printf("---- stTask -----\n");
        printf("id %d\n", id);
        printf("type %d\n", type);
        printf("targetId %d\n", targetId);
        printf("bonusId %d\n", bonusId);
        printf("nextTaskId %d\n", nextTaskId);
        //printf("npcTalkId %d\n", npcTalkId);
        printf("bonusRepeat %d\n", bonusRepeat);
    }
}stTask;

typedef struct
{
	int id;				//id of talk.
	std::string dialog;	//content of dialog.
	int npcId;			//if npcId is 0, lead role is talk. else it is a monster.
    int taskId;
    std::string npcName;
    
    void print()
    {
        printf("---- stTalk -----\n");
        printf("id %d\n", id);
        printf("dialog %s\n", dialog.c_str());
        printf("npcId %d\n", npcId);
        printf("taskId %d\n", taskId);
        printf("npcName %s\n", npcName.c_str());
    }
    bool operator < (const stTask &m)const {
        return id < m.id;
    }
    bool operator > (const stTask &m)const {
        return id > m.id;
    }
}stTalk;

#endif
