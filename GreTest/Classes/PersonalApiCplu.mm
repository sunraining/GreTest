//
//  PersonalApiCplu.cpp
//  MoeWordBook
//
//  Created by lyy on 12-11-11.
//
//

#include "PersonalApiCplu.h"

using namespace std;

//c++字符串分割函数
vector<string>PersonalApiCplu::split(string str,string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern;//扩展字符串以方便操作
    int size=str.size();
    
    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            result.push_back(s);
            i=pos+pattern.size()-1;
        }
    }
    return result;
}


bool PersonalApiCplu::isContantString(string sourceStr,string patternStr)
{
    const char *show;
    
    show=strstr(sourceStr.c_str(),patternStr.c_str());//返回指向第一次出现r位置的指针，如果没找到则返回NULL。
    
    bool isContant;
    if (show == NULL)
    {
        isContant = NO;
    }
    else
    {
        isContant = YES;
    }
    
    return isContant;
}





void PersonalApiCplu::traversingVector(vector<vector<string> > ivec)
{
    //[SingleTonTool defaultMemory].wordListArray = [[NSMutableArray alloc] initWithCapacity:0];
    for (int i = 0 ; i<ivec.size();i++)
    {
        
        vector<string> tempIvec = ivec[i];
        
        NSMutableArray *  aArray = [[NSMutableArray alloc] initWithCapacity:0];
        
        for (int j = 0; j<tempIvec.size(); j++)
        {
            string str = tempIvec[j];
            
            const char * a = str.c_str();
            
            NSString * aString = [NSString stringWithUTF8String:a];
            
            [aArray addObject:aString];
            
            cout<<str<<endl;
        }
       // [[SingleTonTool defaultMemory].wordListArray addObject:aArray];
        cout<<"/////////////////////"<<endl;
    }
    
}
//安全字符串复制,附加拷贝0结尾
size_t PersonalApiCplu::SafeStringCopy(void* dest,size_t destLen,const char* src)
{
	size_t stringLen = strlen(src);
	size_t size=min(destLen-1,stringLen);
	memcpy(dest,src,size);
	((char*)dest)[size]='\0';
	return size;
}

void PersonalApiCplu::string_replace(string & strBig, const string & strsrc, const string &strdst)
{
    string::size_type pos=0;
    string::size_type srclen=strsrc.size();
    string::size_type dstlen=strdst.size();
    
    while( (pos=strBig.find(strsrc, pos)) != string::npos)
    {
        strBig.replace(pos, srclen, strdst);
        pos += dstlen;
    }
}






