//
//  EventModule.cpp
//  HelloWorld
//
//  Created by JamesChen on 12-7-25.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "EventModule.h"
#include "CppSQLite3.h"
#include "cocos2d.h"
#include <algorithm>
#include "BasicFunction.h"

USING_NS_CC;

EventModule *EventModule::m_pInstance = NULL;
EventModule::XLRelease EventModule::Garbo;

EventModule::EventModule()
{
}

EventModule::~EventModule()
{
}

void EventModule::init()
{
}