//
//  BasicFunction.cpp
//  HelloWorld
//
//  Created by XiaoZhong Zhu on 12-7-31.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "BasicFunction.h"

int randNumber(int begin, int end)
{
    if ( begin > end )
    {
        return 0;
    }
    else {
        srand(time(0));
        return begin + rand() % (end - begin);  
    }
}

std::vector<std::string> separateString(std::string orginStr,std::string separateStr)
{
	std::vector<std::string> list;
	
	int pos;
    int separateStrLength = separateStr.length();
	
	while((pos=orginStr.find(separateStr)) != -1)
	{
		list.push_back(orginStr.substr(0,pos));
		
		if(pos <= (int)(orginStr.length()-separateStrLength))
		{
			orginStr=orginStr.substr(pos+separateStrLength);
		}
        else 
            break;
		
	}
	if(orginStr.length() > 0)
	{
		list.push_back(orginStr);
	}
	return list;
}

std::vector<int> separateStringToNumberVector(std::string orgingStr,std::string separateStr)
{
    std::vector<std::string> strList = separateString(orgingStr, separateStr);
    
    std::vector<int> intList;
    for (int i = 0; i < strList.size(); i++) {
        int tmp = std::atoi(strList[i].c_str());
        intList.push_back(tmp);
    }
    return intList;
}