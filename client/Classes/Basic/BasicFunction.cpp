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

std::string ConvertJsonToString(Json::Value data)
{
	switch ( data.type() )
	{
		case Json::stringValue:
			return data.asString();
			
		case Json::booleanValue:
			if(data.asBool())
				return "1";
			return "0";
			
		case Json::intValue:
			return ConvertToString(data.asInt());
			
		case Json::uintValue:
			return ConvertToString(data.asUInt());
			
		case Json::nullValue:
		case Json::realValue:
		case Json::arrayValue:
		case Json::objectValue:
		default:
			break;
	}
	
	return "此json数据不能转换为字符串";
}

//返回-1，表示错误
int ConvertJsonToInt(Json::Value data)
{
	switch ( data.type() )
	{
		case Json::stringValue:
			return atoi(data.asString().c_str());
			
		case Json::booleanValue:
			if(data.asBool())
				return 1;
			return 0;
			
		case Json::intValue:
			return data.asInt();
			
		case Json::uintValue:
			return data.asUInt();
			
		case Json::nullValue:
		case Json::realValue:
		case Json::arrayValue:
		case Json::objectValue:
		default:
			break;
	}
	
	
	return -1;
}

