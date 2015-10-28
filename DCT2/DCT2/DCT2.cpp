#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

//C��u���궨��
#define C(u) ((u%8)? 1.0:(double)(1/sqrt(2.0)))
#define PI 3.1415926

#define COLUMS 512
#define ROWS 512

vector< vector<int> > data;  //����ԭʼ�ļ�����
vector< vector<int> > result; //����任֮�������

//write the result into file
void writeToFile(string filename)  //�����д���ļ�
{
	fstream out;
	out.open(filename);
	if(!out.is_open())
	{
		cerr<<"Open write file error!"<<endl;
		return ;
	}

	for (int row = 0; row < result.size(); row++)   //���任֮��Ľ��д���ļ���
	{
		for(int col = 0; col < result[row].size(); col++)
		{
			out<<result[row][col]<<"  ";
		}
		out<<endl;
	}
	out.close();
}

//print the source mat on the console
void printSource(int row_low, int cols_low) //�������Ϊԭʼ�����е�8x8��������Ͻ�λ��
{
	int row_high = row_low + 8;
	int cols_high = cols_low + 8;

	cout<<"------Source-----"<<endl;
	for(int row = row_low; row < row_high; row++)  //��������任֮ǰ��8x8��������
	{
		for(int col = cols_low; col < cols_high; col++)
		{
			cout<<data[row][col]<<"  ";
		}
		cout<<endl;
	}
}

//print the result mat on the console
void printResult(int row_low, int cols_low) //�������Ϊ��������е�8x8��������Ͻ�λ��
{
	int row_high = row_low + 8;
	int cols_high = cols_low + 8;

	cout<<"------Result-----"<<endl;
	for(int row = row_low; row < row_high; row++) //��������任֮���8x8��������
	{
		for(int col = cols_low; col < cols_high; col++)
		{
			cout<<result[row][col]<<"  ";
		}
		cout<<endl;
	}
}

//8x8 2D-DCT transation
void DCT2(int row_low, int cols_low)
{
	int row_high = row_low + 8;
	int cols_high = cols_low + 8;

	for (int u = row_low; u < row_high; u++)  //���ݹ�ʽ��8x8�������2D DCT�任
	{
		for (int v = cols_low; v < cols_high; v++)
		{
			double temp = 0;
			for(int i = row_low; i < row_high; i++)
			{
				for (int j = cols_low; j < cols_high; j++)
				{

					temp += data[i][j]*cos((2.0*(i%8)+1.0)*(u%8)*PI/16.0)*cos((2.0*(j%8)+1.0)*(v%8)*PI/16.0);
				}
			}

			result[u][v] = (int)(C(u)*C(v)*temp/4.0+0.5); //������������ȡֵ
		}
	}

}

int main()  //������
{
	fstream in;
	in.open("testimg.txt");  //ԭʼ�ļ�
	if(!in.is_open())
	{
		cerr<<"Open file testimg.txt failed!"<<endl;
		return 1;
	}
	string str;
	int num;
	int rows=0;
	int cols=0;
	vector<int> vec;
	data.push_back(vec);
	vector<int> vect(COLUMS);
	result.push_back(vect);
	while (getline(in, str))  //����ԭʼ����
	{
		stringstream istr(str);
		while (istr>>num)
		{
			cols ++;
			data[rows].push_back(num);  
			if (cols>=COLUMS)    //�����п���
			{
				rows ++;
				cols = 0;
				vector<int> vec;
				data.push_back(vec); //�ڶ������ݵ�ͬʱΪ������������ڴ�ռ�

				vector<int> vect(COLUMS);
				result.push_back(vect);
			}
		}
	}
	data.pop_back();
	result.pop_back();

	//�ֿ���� DCT
	for(int i=0; i < ROWS; i+=8)  //��512x512ԭʼ�������ݽ��зֿ鴦��
	{
		for(int j =0; j<COLUMS; j+=8)
		{
			DCT2(i, j);          //����8x8 DCT�任
			//printSource(i, j);   //�����ǰ��ԭʼ8x8 ��������
		 //   printResult(i, j);   //����任֮���8x8 ��������
			//system("pause");
		}
	}

	system("pause");
	writeToFile("result.txt");
	cout<<"the result has been writen into result.txt "<<endl;

	return 0;
}