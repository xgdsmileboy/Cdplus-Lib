#ifndef PERCEPTRON_CPP
#define PERCEPTRON_CPP

#include <iostream>
#include <fstream>
#include <string>

#include "perceptron.h"
#include "txtProcess.h"

/****************************************************************************************/
/* function:
/*       ʶ��һ���ַ�����������Ϣ
/* input:
/*       m_weightMap  (const map<int, double>&) �Ѿ�ѵ���õķ�����ϵ����Ϣ
/*       testMap  (const map<test, double>&)  ���潫Ҫʶ����ַ����Ĺؼ��ʺ����Ӧֵ��Ϣ��
/****************************************************************************************/
int txtPerceptron(const map<int, double>& m_weightMap, const map<int, double> testMap)
{
	double p = 0;
	map<int, double>::const_iterator itor;
	for (itor = testMap.begin(); itor != testMap.end(); itor++)
	{
		p += itor->second * m_weightMap.at(itor->first);   //ʹ��Perceptron�㷨��������Ϣ���з���
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
/*	     ʹ���Ѿ�ѵ���õķ������������ָ���ļ����и�֪����
/* input:
/*       m_weightMap  (const map<int, double>)  �Ѿ�ѵ���õķ�����ϵ����
/*       fileName  (string)  ��������ļ���������ļ�������/����·����
/************************************************************************/
void filePerceptron(const map<int, double> m_weightMap, string fileName)
{
	fstream fstr;
	fstr.open(fileName);
	if (!fstr.is_open())   //���ļ�ʧ��
	{
		cerr<<"Open file "<<fileName<<" failed in filePerceptron!"<<endl;
		return;
	}
	string txt;
	int positiveCorrectNum = 0;
	int positiveNum = 0;
	int negativeCorrectNum = 0;
	int negativNum = 0;
	while (getline(fstr, txt)!=NULL)  //���ļ��е�ÿһ����Ϣ���з���
	{
		map<int, double> keyMap = *(new map<int, double>());
		getTxtKey(txt, keyMap);       //��ȡʶ���ַ����ļ�ֵ��Ӧ��Ϣ
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