#ifndef FILEPROCESS_CPP
#define FILEPROCESS_CPP

#include "txtProcess.h"

/************************************************************************/
/* function：
/*       获取输入字符串的类型，根据文件中数据的组织容易获得
/*       每一个字符串的首字符标注的是文本的正负极性
/* input:
/*       txt (string) 待获取类型的字符串
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
/*       获取文本中的关键词和其对应的值
/* input:
/*       txt  (const string&) 待获取器关键词和对应值的字符串
/*       keyMap  (map<int, double>&)  保存输入字符串的关键词和对应值信息
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
		//values的值应该为double类型，在此处有精度损失，但对识别精度影响不是很明显
		values = atof(str.substr(index+1, str.find_first_of(' ')-index-1).c_str());
		str = str.substr(str.find_first_of(' ')+1, str.length());
		keyMap[key] = values;
	}

}

#endif
