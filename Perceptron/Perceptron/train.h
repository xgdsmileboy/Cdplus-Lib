#ifndef TRAIN_H
#define TRAIN_H

/**
* Author: ���Ѿ�
* Date��2014��5��18��
* function��ѵ����
*/

#include "type.h"
#include <string>
#include <map>
using namespace std;


/************************************************************************/
/* function:
/*       ʹ��perceptron�㷨����ָ�����ļ�Ϊ�����Է���������ѵ��
/* input:
/*       m_weightMap  (map<int, double>&)  �����������ϵ����Ϣ
/*       fileName  (string)  ָ�����ļ���������ڹ��̵����·��/����·����
/************************************************************************/
void trainFile(map<int, double>& m_weightMap, string fileName);

#endif