#ifndef TXTPROCESS_H
#define TXTPROCESS_H

/**
* Author: 姜佳君
* Date：2014年5月18日
* function：文本处理
*/

using namespace std;
#include <string>
#include <iomanip>
#include <map>
#include <sstream>
#include "type.h"

/************************************************************************/
/* function：
/*       获取输入字符串的类型，根据文件中数据的组织容易获得
/*       每一个字符串的首字符标注的是文本的正负极性
/* input:
/*       txt (string) 待获取类型的字符串
/************************************************************************/
int getTxtType(string txt);


/************************************************************************/
/* function:
/*       获取文本中的关键词和其对应的值
/* input:
/*       txt  (const string&) 待获取器关键词和对应值的字符串
/*       keyMap  (map<int, double>&)  保存输入字符串的关键词和对应值信息
/************************************************************************/
void getTxtKey(const string& txt, map<int, double>& keyMap);

#endif