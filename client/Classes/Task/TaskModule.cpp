//
//  TaskModule.cpp
//  HelloWorld
//
//  Created by JamesChen on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "TaskModule.h"
#include "CppSQLite3.h"
#include "cocos2d.h"
#include <algorithm>
#include "BasicFunction.h"

USING_NS_CC;

TaskModule *TaskModule::m_pInstance = NULL;
TaskModule::XLRelease TaskModule::Garbo;

TaskModule::TaskModule()
{
}

TaskModule::~TaskModule()
{
}

void TaskModule::init()
{
}