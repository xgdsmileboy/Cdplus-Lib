#include<iostream>
#include<iomanip>
#include<sstream>
#include<fstream>
using namespace std;

int main()
{
	//testimg.txt

	unsigned int data[256];   //��¼��Ӧ�Ҷ�ֵ��Ƶ��ֵ
	float changeTo[256];      //��¼��Ӧ�Ҷȸ����ۼ�֮��ĻҶ�ֵ����ǿ֮��ĻҶ�ֵ
	float rate[256];          //��¼��Ӧ�Ҷ�ֵ�ı���ֵ
	for(int i=0; i<256; i++)  //�Ҷ�ֵ������ʼ��0
	{
		data[i] = 0;
	}
	ifstream in("testimg.txt");   //ԭʼ���ݶ���
	if(!in)
	{
		cerr<<"Can't open file testimg.txt!"<<endl;
		return 0;
	}
	string str;
	unsigned int num;
	float total = 0;
	while(getline(in,str))   //���ļ��ж�������
	{
		istringstream istr(str);
		while(istr>>num)     //����ת��Ϊ����ֵ���ۼƸ���
		{
			data[num]++;
			total++;
		}
	}
	in.close();
	for(int i =0; i < 256; i++)               //������Ӧ�Ҷ�ֵ�ı���ֵ
	{
		rate[i] = (float)data[i]/total;
	}
	changeTo[0] = (int)(rate[0] * 255 + 0.5);  //�ۼƲ�ͬ�Ҷ�ֵ�ı�����ͬʱ������ǿ֮��ĻҶ�ֵ
	for(int j = 1; j < 256; j++)
	{
		rate[j] += rate[j-1];
		changeTo[j] = (int)(rate[j] * 255 + 0.5);
	}
	ifstream in2("testimg.txt");  //���ݶ���
	ofstream out("result.txt");   //�������
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
	while(getline(in2,str))       //��������
	{
		istringstream istr(str);
		while(istr>>num)          //����������ת��Ϊ��ǿ֮��ĻҶ�ֵ������ļ�
		{
			out<<changeTo[num]<<"  ";
		}
		out<<endl;
	}

	in2.close();  //�ر��ļ�
	out.close();
	return 0;

}