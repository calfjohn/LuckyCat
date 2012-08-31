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


#define INVALID_VALUES                  -1      //无效值, 比如 表示没有下一个值 
//a page is a game level
typedef struct
{
    int id;             //index of page
    string name;        //page's title
    string content;     //page's content
    int imageId;        //page's image
    int eventId;         //page's event
    cocos2d::CCPoint position;   //position on page map
    int state;          //fight result 0:new 1:success 2: failed
    std::string image;  //the background of page
    bool end;           //is last page of chapter
}stPage;

//a chapter consist lot of page
typedef struct
{
    int id;             //index of chapter
    string name;        //chapter's title
    int imageId;        //chapter's image
    cocos2d::CCPoint position;   //position on chapter scene
    vector<stPage> listPage;    //a set of pages in chapter
}stChapter;

//a bible consist lot of stChapter
typedef struct
{
    int id;                         //index of bible
    string name;                    //bible name
    int bgId;                       //bible background image
    int chapterBgId;                //chapter background image
    vector<stChapter> listChapter;
}stBible;

typedef struct
{
    int id;         //monster id
    string name;    //monster name
    int imageId;   //monster image id
}stMonster;

typedef struct
{
    int id;
    int type;
    string name;
    string filePath;
    string plistPath;
}stImage;

class VisibleRect
{
public:
	static const cocos2d::CCRect&  rect();
	static const cocos2d::CCPoint& center();
	static const cocos2d::CCPoint& top();
	static const cocos2d::CCPoint& topRight();
	static const cocos2d::CCPoint& right();
	static const cocos2d::CCPoint& bottomRight();
	static const cocos2d::CCPoint& bottom();
	static const cocos2d::CCPoint& bottomLeft();
	static const cocos2d::CCPoint& left();
	static const cocos2d::CCPoint& topLeft();
};
typedef struct 
{
    int id;
    int count;
    int type;
    
    void print()
    {
        printf("Good ID %d,Type %d, GoodNum %d\n",id,type,count);
    }
}stGood;

typedef struct {
    int                     level;      //level of actor
    std::string             title;      //title of notification
    std::string             content;    //content of notification
    std::vector<stGood>     bonus;      //bouns of level upgrade reaward
    
    void print()
    {
        printf("---stActorLevelUpgrade---\n");
        printf("title %s\n", title.c_str());
        printf("content %s\n", content.c_str());
        printf("bonus\n");
        for ( int i=0; i<bonus.size(); i++ )
        {
            bonus[i].print();
        }
    }
}stActorLevelUpgrade;



typedef struct{
    int                         equipId;
    std::string                 equipName;
    int                         equipImageId;
    int                         equipType;
    int                         equipLife;
    int                         equipLevelLimit;
    int                         equipAttack;
    int                         equipDefence;
    int                         equipSpeed;
    std::string                 equipDescription;
}stActorEquipInfo;

typedef struct{
    bool                userPutOn;
    int                 userListId;
    int                 userEquipId;
    int                 userEquipType;
    stActorEquipInfo    *equipInfo;
}stActorUserEquipInfo;

typedef struct {
    int                     userUuid;
    std::string             userNickName;
    int                     userImageId;
    int                     userLevel;
    int                     userExp;
    int                     userHp;
    int                     userCareerId;
    int                     userChapterId;
    int                     userPageId;
    float                   userAttack;
    float                   userDefence;
    float                   userSpeed;
    int                     userMaxHp;
    stActorUserEquipInfo    *userEquipInfo;
}stActorUserInfo;

typedef struct
{
	int	id;				//id of event.
    int targetId;		//id of target.
}stEvent;


#endif

