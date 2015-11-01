#include <iostream>
using namespace std;
#include <sstream>
#include <strstream>
#include <fstream>
#include <iomanip>
#include "train.h"
#include "perceptron.h"

//ѵ��ѭ������
#define TRAININGTIMES 1

/*********************************************************************************/
/* function:
/*       ��ʼ���ؼ��ʺ����Ӧ��ϵ����ʼֵ����ֵΪ0��
/* input:
/*       m_weightMap  (map<int, double>&)  ������ļ��ж�ȡ���Ĺؼ��ʺͶ�Ӧ��ʼֵ
/*********************************************************************************/
void initWeightMap(map<int, double>& m_weightMap)
{
	fstream fstr;
	string fileName = "data2/s";   //�ļ�Ŀ¼��Ϣ
	for(int i = 1; i <= 5; i++)    //��Ŀ¼�µ��ļ�ѭ����ȡ
	{
		cout<<"fetching data from "<<fileName<<i<<"...."<<endl;
		strstream sstr;
		sstr<<i;
		string strFileNum;
		sstr>>strFileNum;
		fstr.open(fileName + strFileNum); //���ļ�

		if (!fstr.is_open())              //���ļ�ʧ��
		{
			cerr<<"Open file "<<fileName + strFileNum<<" failed!"<<endl;
			return ;
		}

		string str;
		int key;
		while ((getline(fstr, str))!=NULL)       //��ȡ�ļ�����
		{
			str = str.substr(3,str.length());    //��ȡ���ļ��е�������Ϣ
			int index;
			while ((index=str.find_first_of(':'))>0)       //�ҵ��ļ��еĹؼ��ʺ����Ӧ��ֵ
			{
				stringstream sstr(str.substr(0,index));
				str = str.substr(str.find_first_of(' ')+1, str.length());
				sstr>>key;
				m_weightMap[key] = 0.0;                    //���ؼ��ʺͳ�ʼֵ��0��������ϵ��map����
			}
		}
		fstr.close();
	}
}

/***************************������************************************************/
int main()
{
	map<int, double> m_weightMap = *(new map<int, double>());   //������Ϊ��������ϵ����Ϣ��¼��map��
	initWeightMap(m_weightMap);                                 //��ʼ��map��

	for (int i = 1; i <= TRAININGTIMES; i++)                    //ʹ��ָ���ļ��Է���������ѵ��
	{
		cout<<endl<<"training cycles:  "<<i<<endl;
		trainFile(m_weightMap, "data2/s1");
		trainFile(m_weightMap, "data2/s2");
		trainFile(m_weightMap, "data2/s3");
		trainFile(m_weightMap, "data2/s4");
	}

	cout<<endl<<"File classify testing..."<<endl;
	filePerceptron(m_weightMap, "data2/s5");        //ʹ��ѵ���õķ�������ָ���ļ�����ʶ��
	system("pause");
	return 0;
}