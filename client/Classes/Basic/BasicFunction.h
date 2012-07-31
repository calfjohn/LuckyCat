//
//  BasicFunction.h
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-31.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef HelloWorld_BasicFunction_h
#define HelloWorld_BasicFunction_h

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "cocos2d.h"

int randNumber(int begin, int end);

std::vector<std::string> separateString(std::string orginStr,std::string separateStr);
std::vector<int> separateStringToNumberVector(std::string orgingStr,std::string separateStr);

#endif
