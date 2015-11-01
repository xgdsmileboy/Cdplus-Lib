#ifndef PERCEPTRON_H
#define PERCEPTRON_H

/**
* Author: 姜佳君
* Date：2014年5月18日
* function：分类器
*/


using namespace std;
#include <map>
#include "type.h"


/****************************************************************************************/
/* function:
/*       识别一个字符串的类型信息
/* input:
/*       m_weightMap  (const map<int, double>&) 已经训练好的分类器系数信息
/*       testMap  (const map<test, double>&)  保存将要识别的字符串的关键词和其对应值信息表
/****************************************************************************************/
int txtPerceptron(const map<int, double>& m_weightMap, const map<int, double> testMap);


/************************************************************************/
/* function:
/*	     使用已经训练好的分类器对输入的指定文件进行感知分类
/* input:
/*       m_weightMap  (const map<int, double>)  已经训练好的分类器系数表
/*       fileName  (string)  待分类的文件名（相对文件工程名/绝对路径）
/************************************************************************/
void filePerceptron(const map<int, double> m_weightMap, string fileName);

#endif