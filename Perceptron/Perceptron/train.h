#ifndef TRAIN_H
#define TRAIN_H

/**
* Author: 姜佳君
* Date：2014年5月18日
* function：训练器
*/

#include "type.h"
#include <string>
#include <map>
using namespace std;


/************************************************************************/
/* function:
/*       使用perceptron算法，以指定的文件为样本对分类器进行训练
/* input:
/*       m_weightMap  (map<int, double>&)  保存分类器的系数信息
/*       fileName  (string)  指定的文件名（相对于工程的相对路径/绝对路径）
/************************************************************************/
void trainFile(map<int, double>& m_weightMap, string fileName);

#endif