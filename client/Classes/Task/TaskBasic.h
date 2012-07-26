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
	int type;			//type of task. 0 main task, 1 side task.
	int targetId;		//id of target.
	int bonusId;		//bonus of task.
	int nextTaskId;		//next task follow this task.
	int npcTalkId;		//a talk about this task.
	bool bonusRepeat;	//if bonusRepeat is true, player can get bonus again.
}stTask;

typedef struct
{
	int id;				//id of talk.
	std::string dialog;	//content of dialog.
	int npcId;			//if npcId is 0, lead role is talk. else it is a monster.
}stTalk;


#endif
