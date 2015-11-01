#ifndef PERCEPTRON_H
#define PERCEPTRON_H

/**
* Author: ���Ѿ�
* Date��2014��5��18��
* function��������
*/


using namespace std;
#include <map>
#include "type.h"


/****************************************************************************************/
/* function:
/*       ʶ��һ���ַ�����������Ϣ
/* input:
/*       m_weightMap  (const map<int, double>&) �Ѿ�ѵ���õķ�����ϵ����Ϣ
/*       testMap  (const map<test, double>&)  ���潫Ҫʶ����ַ����Ĺؼ��ʺ����Ӧֵ��Ϣ��
/****************************************************************************************/
int txtPerceptron(const map<int, double>& m_weightMap, const map<int, double> testMap);


/************************************************************************/
/* function:
/*	     ʹ���Ѿ�ѵ���õķ������������ָ���ļ����и�֪����
/* input:
/*       m_weightMap  (const map<int, double>)  �Ѿ�ѵ���õķ�����ϵ����
/*       fileName  (string)  ��������ļ���������ļ�������/����·����
/************************************************************************/
void filePerceptron(const map<int, double> m_weightMap, string fileName);

#endif