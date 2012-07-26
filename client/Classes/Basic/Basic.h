//
//  Basic.h
//  cocos2dx
//
//  Created by Cocos2d on 12-7-18.
//  Copyright (c) 2012年 厦门雅基软件有限公司. All rights reserved.
//

#if !defined _BASIC_H__
#define _BASIC_H__

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

#define TRANSITION_PAGE_INTERVAL_TIME   1.0f

//a page is a game level
typedef struct
{
    int id;             //index of page
    string name;        //page's title
    string content;     //page's content
    cocos2d::CCPoint postion;   //position on page map
    int monsterId;      //monster id assosiate with monster_dict table in database
    int state;          //fight result 0:new 1:success 2: failed
    int taskId;         //task id about this page
    std::string image;  //the background of page
}stPage;

//a chapter consist lot of page
typedef struct
{
    int id;             //index of chapter
    string name;        //chapter's title
    cocos2d::CCPoint position;   //position on chapter scene
    vector<stPage> listPage;    //a set of pages in chapter
}stChapter;

//a bible consist lot of stChapter
typedef struct
{
    int id;
    string name;
    vector<stChapter> listChapter;
}stBibleInstance;

//a bible consist lot of stChapter
typedef struct
{
    string name;
    vector<stChapter> listChapter;
}stBible;


typedef struct
{
    int id;         //monster id
    string name;    //monster name
    int image_id;   //monster image id
}stMonster;
#endif

