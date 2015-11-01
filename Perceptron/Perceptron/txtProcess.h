#ifndef TXTPROCESS_H
#define TXTPROCESS_H

/**
* Author: ���Ѿ�
* Date��2014��5��18��
* function���ı�����
*/

using namespace std;
#include <string>
#include <iomanip>
#include <map>
#include <sstream>
#include "type.h"

/************************************************************************/
/* function��
/*       ��ȡ�����ַ��������ͣ������ļ������ݵ���֯���׻��
/*       ÿһ���ַ��������ַ���ע�����ı�����������
/* input:
/*       txt (string) ����ȡ���͵��ַ���
/************************************************************************/
int getTxtType(string txt);


/************************************************************************/
/* function:
/*       ��ȡ�ı��еĹؼ��ʺ����Ӧ��ֵ
/* input:
/*       txt  (const string&) ����ȡ���ؼ��ʺͶ�Ӧֵ���ַ���
/*       keyMap  (map<int, double>&)  ���������ַ����Ĺؼ��ʺͶ�Ӧֵ��Ϣ
/************************************************************************/
void getTxtKey(const string& txt, map<int, double>& keyMap);

#endif