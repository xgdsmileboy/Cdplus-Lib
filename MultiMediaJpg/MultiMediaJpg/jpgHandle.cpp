#include<iostream>
#include<iomanip>
#include<sstream>
#include<fstream>
using namespace std;

int main()
{
	//testimg.txt

	unsigned int data[256];   //记录对应灰度值的频度值
	float changeTo[256];      //记录对应灰度概率累计之后的灰度值，增强之后的灰度值
	float rate[256];          //记录对应灰度值的比例值
	for(int i=0; i<256; i++)  //灰度值计数初始清0
	{
		data[i] = 0;
	}
	ifstream in("testimg.txt");   //原始数据读入
	if(!in)
	{
		cerr<<"Can't open file testimg.txt!"<<endl;
		return 0;
	}
	string str;
	unsigned int num;
	float total = 0;
	while(getline(in,str))   //从文件中读入数据
	{
		istringstream istr(str);
		while(istr>>num)     //数据转化为整型值，累计个数
		{
			data[num]++;
			total++;
		}
	}
	in.close();
	for(int i =0; i < 256; i++)               //计算相应灰度值的比例值
	{
		rate[i] = (float)data[i]/total;
	}
	changeTo[0] = (int)(rate[0] * 255 + 0.5);  //累计不同灰度值的比例，同时计算增强之后的灰度值
	for(int j = 1; j < 256; j++)
	{
		rate[j] += rate[j-1];
		changeTo[j] = (int)(rate[j] * 255 + 0.5);
	}
	ifstream in2("testimg.txt");  //数据读入
	ofstream out("result.txt");   //数据输出
    if(!in2)
	{
		cerr<<"Can't open file testimg.txt!"<<endl;
		return 0;
	}
	if(!out)
	{
		cerr<<"Can't open file result.txt!"<<endl;
		return 0;
	}
	while(getline(in2,str))       //读入数据
	{
		istringstream istr(str);
		while(istr>>num)          //将读入数据转换为增强之后的灰度值输出到文件
		{
			out<<changeTo[num]<<"  ";
		}
		out<<endl;
	}

	in2.close();  //关闭文件
	out.close();
	return 0;

}