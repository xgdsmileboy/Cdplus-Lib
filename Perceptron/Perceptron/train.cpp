#ifndef TRAIN_CPP
#define TRAIN_CPP

#include <iostream>
#include <sstream>
#include <fstream>

#include "train.h"
#include "txtProcess.h"

//机器学习率，反应学习的速度
#define alpha 0.25

/************************************************************************/
/* function:
/*       使用perceptron算法，以指定的文件为样本对分类器进行训练
/* input:
/*       m_weightMap  (map<int, double>&)  保存分类器的系数信息
/*       fileName  (string)  指定的文件名（相对于工程的相对路径/绝对路径）
/************************************************************************/

void trainFile(map<int, double>& m_weightMap, string fileName)
{
	fstream fstr;
	fstr.open(fileName);   //打开待训练的文件样本
	if (!fstr.is_open())
	{
		cerr<<"Open file "<<fileName<<" failed in trainFile()!"<<endl;
		return;
	}
	cout<<"Using file "<<fileName<<" training...."<<endl;
	string txt;
	int type;
	map<int, double>::iterator itor;
	while (getline(fstr, txt)!=NULL)  //读取文件中的一个训练样例
	{
		type = getTxtType(txt);       //获取训练样例原始类型
		map<int, double> keyMap = *(new map<int, double>());
		getTxtKey(txt,keyMap);        //获取驯良样例，存入键值对map表
		double p = 0;
		for (itor = keyMap.begin(); itor != keyMap.end(); itor++)  //使用perceptron算法对分类器进行训练
		{
			p += itor->second * m_weightMap.at(itor->first);
		}
		if (type * p <= 0)   //更新分类器信息
		{
			for (itor = keyMap.begin(); itor != keyMap.end(); itor++)
			{
				m_weightMap.at(itor->first) += alpha * type * itor->second;
			}
		}

	}
}

#endif