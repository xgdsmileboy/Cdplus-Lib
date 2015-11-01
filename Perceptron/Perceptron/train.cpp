#ifndef TRAIN_CPP
#define TRAIN_CPP

#include <iostream>
#include <sstream>
#include <fstream>

#include "train.h"
#include "txtProcess.h"

//����ѧϰ�ʣ���Ӧѧϰ���ٶ�
#define alpha 0.25

/************************************************************************/
/* function:
/*       ʹ��perceptron�㷨����ָ�����ļ�Ϊ�����Է���������ѵ��
/* input:
/*       m_weightMap  (map<int, double>&)  �����������ϵ����Ϣ
/*       fileName  (string)  ָ�����ļ���������ڹ��̵����·��/����·����
/************************************************************************/

void trainFile(map<int, double>& m_weightMap, string fileName)
{
	fstream fstr;
	fstr.open(fileName);   //�򿪴�ѵ�����ļ�����
	if (!fstr.is_open())
	{
		cerr<<"Open file "<<fileName<<" failed in trainFile()!"<<endl;
		return;
	}
	cout<<"Using file "<<fileName<<" training...."<<endl;
	string txt;
	int type;
	map<int, double>::iterator itor;
	while (getline(fstr, txt)!=NULL)  //��ȡ�ļ��е�һ��ѵ������
	{
		type = getTxtType(txt);       //��ȡѵ������ԭʼ����
		map<int, double> keyMap = *(new map<int, double>());
		getTxtKey(txt,keyMap);        //��ȡѱ�������������ֵ��map��
		double p = 0;
		for (itor = keyMap.begin(); itor != keyMap.end(); itor++)  //ʹ��perceptron�㷨�Է���������ѵ��
		{
			p += itor->second * m_weightMap.at(itor->first);
		}
		if (type * p <= 0)   //���·�������Ϣ
		{
			for (itor = keyMap.begin(); itor != keyMap.end(); itor++)
			{
				m_weightMap.at(itor->first) += alpha * type * itor->second;
			}
		}

	}
}

#endif