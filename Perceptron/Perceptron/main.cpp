#include <iostream>
using namespace std;
#include <sstream>
#include <strstream>
#include <fstream>
#include <iomanip>
#include "train.h"
#include "perceptron.h"

//训练循环周期
#define TRAININGTIMES 1

/*********************************************************************************/
/* function:
/*       初始化关键词和其对应的系数初始值（初值为0）
/* input:
/*       m_weightMap  (map<int, double>&)  保存从文件中读取到的关键词和对应初始值
/*********************************************************************************/
void initWeightMap(map<int, double>& m_weightMap)
{
	fstream fstr;
	string fileName = "data2/s";   //文件目录信息
	for(int i = 1; i <= 5; i++)    //对目录下的文件循环读取
	{
		cout<<"fetching data from "<<fileName<<i<<"...."<<endl;
		strstream sstr;
		sstr<<i;
		string strFileNum;
		sstr>>strFileNum;
		fstr.open(fileName + strFileNum); //打开文件

		if (!fstr.is_open())              //打开文件失败
		{
			cerr<<"Open file "<<fileName + strFileNum<<" failed!"<<endl;
			return ;
		}

		string str;
		int key;
		while ((getline(fstr, str))!=NULL)       //读取文件内容
		{
			str = str.substr(3,str.length());    //截取掉文件中的类型信息
			int index;
			while ((index=str.find_first_of(':'))>0)       //找到文件中的关键词和其对应的值
			{
				stringstream sstr(str.substr(0,index));
				str = str.substr(str.find_first_of(' ')+1, str.length());
				sstr>>key;
				m_weightMap[key] = 0.0;                    //将关键词和初始值（0）保存入系数map表中
			}
		}
		fstr.close();
	}
}

/***************************主函数************************************************/
int main()
{
	map<int, double> m_weightMap = *(new map<int, double>());   //定义作为分类器的系数信息记录的map表
	initWeightMap(m_weightMap);                                 //初始化map表

	for (int i = 1; i <= TRAININGTIMES; i++)                    //使用指定文件对分类器进行训练
	{
		cout<<endl<<"training cycles:  "<<i<<endl;
		trainFile(m_weightMap, "data2/s1");
		trainFile(m_weightMap, "data2/s2");
		trainFile(m_weightMap, "data2/s3");
		trainFile(m_weightMap, "data2/s4");
	}

	cout<<endl<<"File classify testing..."<<endl;
	filePerceptron(m_weightMap, "data2/s5");        //使用训练好的分类器对指定文件进行识别
	system("pause");
	return 0;
}