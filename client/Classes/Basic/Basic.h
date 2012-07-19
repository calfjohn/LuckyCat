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

using namespace std;

//a page is a game level
typedef struct
{
    int id;
    string name;
    string content;
    int monsterId;
    int state;  //0:new 1:success 2: failed
}stPage;

//a chapter consist lot of page
typedef struct
{
    int id;
    string name;
    vector<stPage> listPage;
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

#endif

