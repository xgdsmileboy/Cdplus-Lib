#ifndef FILEPROCESS_CPP
#define FILEPROCESS_CPP

#include "txtProcess.h"

/************************************************************************/
/* function��
/*       ��ȡ�����ַ��������ͣ������ļ������ݵ���֯���׻��
/*       ÿһ���ַ��������ַ���ע�����ı�����������
/* input:
/*       txt (string) ����ȡ���͵��ַ���
/************************************************************************/
int getTxtType(string txt)
{
	if (txt.at(0) == '+')
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
/*       ��ȡ�ı��еĹؼ��ʺ����Ӧ��ֵ
/* input:
/*       txt  (const string&) ����ȡ���ؼ��ʺͶ�Ӧֵ���ַ���
/*       keyMap  (map<int, double>&)  ���������ַ����Ĺؼ��ʺͶ�Ӧֵ��Ϣ
/************************************************************************/
void getTxtKey(const string& txt, map<int, double>& keyMap)
{
	string str;
	int key;
	double values;
	str = txt.substr(3,txt.length());
	int index;
	while ((index=str.find_first_of(':'))>0)
	{
		stringstream sstr(str.substr(0,index));
		sstr>>key;
		//values��ֵӦ��Ϊdouble���ͣ��ڴ˴��о�����ʧ������ʶ�𾫶�Ӱ�첻�Ǻ�����
		values = atof(str.substr(index+1, str.find_first_of(' ')-index-1).c_str());
		str = str.substr(str.find_first_of(' ')+1, str.length());
		keyMap[key] = values;
	}

}

#endif
