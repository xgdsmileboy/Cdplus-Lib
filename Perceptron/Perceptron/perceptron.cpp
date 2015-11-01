#ifndef PERCEPTRON_CPP
#define PERCEPTRON_CPP

#include <iostream>
#include <fstream>
#include <string>

#include "perceptron.h"
#include "txtProcess.h"

/****************************************************************************************/
/* function:
/*       识别一个字符串的类型信息
/* input:
/*       m_weightMap  (const map<int, double>&) 已经训练好的分类器系数信息
/*       testMap  (const map<test, double>&)  保存将要识别的字符串的关键词和其对应值信息表
/****************************************************************************************/
int txtPerceptron(const map<int, double>& m_weightMap, const map<int, double> testMap)
{
	double p = 0;
	map<int, double>::const_iterator itor;
	for (itor = testMap.begin(); itor != testMap.end(); itor++)
	{
		p += itor->second * m_weightMap.at(itor->first);   //使用Perceptron算法对输入信息进行分类
	}
	if ( p > 0)
	{
		return POSITIVE;
	}
	else
	{
		return NEGATIVE;
	}
}

/************************************************************************/
/* function:
/*	     使用已经训练好的分类器对输入的指定文件进行感知分类
/* input:
/*       m_weightMap  (const map<int, double>)  已经训练好的分类器系数表
/*       fileName  (string)  待分类的文件名（相对文件工程名/绝对路径）
/************************************************************************/
void filePerceptron(const map<int, double> m_weightMap, string fileName)
{
	fstream fstr;
	fstr.open(fileName);
	if (!fstr.is_open())   //打开文件失败
	{
		cerr<<"Open file "<<fileName<<" failed in filePerceptron!"<<endl;
		return;
	}
	string txt;
	int positiveCorrectNum = 0;
	int positiveNum = 0;
	int negativeCorrectNum = 0;
	int negativNum = 0;
	while (getline(fstr, txt)!=NULL)  //对文件中的每一条信息进行分类
	{
		map<int, double> keyMap = *(new map<int, double>());
		getTxtKey(txt, keyMap);       //获取识别字符串的键值对应信息
		if (getTxtType(txt) == POSITIVE)
		{
			if (txtPerceptron(m_weightMap, keyMap) == POSITIVE)
			{
				positiveCorrectNum ++;
			} 
			positiveNum ++;
		} 
		else
		{
			if (txtPerceptron(m_weightMap, keyMap) == NEGATIVE)
			{
				negativeCorrectNum ++;
			} 
			negativNum ++;
		}
	}
	fstr.close();
	cout<<"In file "<<fileName<<endl;
	cout<<"Positive number: "<<positiveNum<<"  classify correct:  "<<positiveCorrectNum<<endl;
	cout<<"Negative number: "<<negativNum<<"  classify correct:  "<<negativeCorrectNum<<endl;
}

#endif