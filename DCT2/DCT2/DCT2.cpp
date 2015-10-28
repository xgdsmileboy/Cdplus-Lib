#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

//C（u）宏定义
#define C(u) ((u%8)? 1.0:(double)(1/sqrt(2.0)))
#define PI 3.1415926

#define COLUMS 512
#define ROWS 512

vector< vector<int> > data;  //保存原始文件数据
vector< vector<int> > result; //保存变换之后的数据

//write the result into file
void writeToFile(string filename)  //将结果写入文件
{
	fstream out;
	out.open(filename);
	if(!out.is_open())
	{
		cerr<<"Open write file error!"<<endl;
		return ;
	}

	for (int row = 0; row < result.size(); row++)   //将变换之后的结果写入文件中
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
void printSource(int row_low, int cols_low) //传入参数为原始矩阵中的8x8矩阵的左上角位置
{
	int row_high = row_low + 8;
	int cols_high = cols_low + 8;

	cout<<"------Source-----"<<endl;
	for(int row = row_low; row < row_high; row++)  //用于输出变换之前的8x8矩阵数据
	{
		for(int col = cols_low; col < cols_high; col++)
		{
			cout<<data[row][col]<<"  ";
		}
		cout<<endl;
	}
}

//print the result mat on the console
void printResult(int row_low, int cols_low) //传入参数为结果矩阵中的8x8矩阵的左上角位置
{
	int row_high = row_low + 8;
	int cols_high = cols_low + 8;

	cout<<"------Result-----"<<endl;
	for(int row = row_low; row < row_high; row++) //用于输出变换之后的8x8矩阵数据
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

	for (int u = row_low; u < row_high; u++)  //根据公式对8x8矩阵进行2D DCT变换
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

			result[u][v] = (int)(C(u)*C(v)*temp/4.0+0.5); //采用四舍五入取值
		}
	}

}

int main()  //主函数
{
	fstream in;
	in.open("testimg.txt");  //原始文件
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
	while (getline(in, str))  //读入原始数据
	{
		stringstream istr(str);
		while (istr>>num)
		{
			cols ++;
			data[rows].push_back(num);  
			if (cols>=COLUMS)    //矩阵换行控制
			{
				rows ++;
				cols = 0;
				vector<int> vec;
				data.push_back(vec); //在读入数据的同时为结果矩阵申请内存空间

				vector<int> vect(COLUMS);
				result.push_back(vect);
			}
		}
	}
	data.pop_back();
	result.pop_back();

	//分块计算 DCT
	for(int i=0; i < ROWS; i+=8)  //对512x512原始矩阵数据进行分块处理
	{
		for(int j =0; j<COLUMS; j+=8)
		{
			DCT2(i, j);          //进行8x8 DCT变换
			//printSource(i, j);   //输出当前的原始8x8 矩阵数据
		 //   printResult(i, j);   //输出变换之后的8x8 矩阵数据
			//system("pause");
		}
	}

	system("pause");
	writeToFile("result.txt");
	cout<<"the result has been writen into result.txt "<<endl;

	return 0;
}