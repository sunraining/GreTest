//
//  PersonalApiCplu.h
//  MoeWordBook
//
//  Created by lyy on 12-11-11.
//
//

#ifndef __MoeWordBook__PersonalApiCplu__
#define __MoeWordBook__PersonalApiCplu__

#include <iostream>
#include<vector>
#include<string>
#include<cstdio>
#include <sstream>

class PersonalApiCplu
{
public:

    static std::vector<std::string> split(std::string str,std::string pattern);//字符串分割
    static bool isContantString(std::string sourceStr,std::string patternStr);//判断一个字符串是否包含另外一个
    static void traversingVector(std::vector<std::vector<std::string> > ivec);//打印多维数组
    static size_t SafeStringCopy(void* dest,size_t destLen,const char* src);
    static void string_replace(std::string & strBig, const std::string & strsrc, const std::string &strdst);//字符串替换
    
};


#endif /* defined(__MoeWordBook__PersonalApiCplu__) */
