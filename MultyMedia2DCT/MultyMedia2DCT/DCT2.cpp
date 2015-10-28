#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define C(u) ((u%8)? 1.0:(double)(1/sqrt(2.0)))
#define PI 3.1415926

vector< vector<int> > data;
vector< vector<int> > result;

void DCT2(int row_low, int cols_low)
{
	int row_high = row_low + 8;
	int cols_high = cols_low + 8;

	for (int u = row_low; u < row_high; u++)
	{
		for (int v = cols_low; v < row_high; v++)
		{
			double temp = 0;
			for(int i = row_low; i < row_high; i++)
			{
				for (int j = cols_low; j < cols_high; j++)
				{
					temp += data[i][j]*cos((2.0*i+1.0)*u*PI/16.0)*cos((2.0*j+1.0)*v*PI/16.0);
				}
			}

			result[u][v] = (int)(C(u)*C(v)*temp);
		}
	}

}

void writeToFile(string filename)
{
	fstream out;
	out.open(filename);
	if(!out.is_open())
	{
		cerr<<"Open write file error!"<<endl;
		return ;
	}

	for (int row = 0; row < result.size(); row++)
	{
		for(int col = 0; col < result[row].size(); col++)
		{
			out<<result[row][col]<<"  ";
		}
		out<<endl;
	}
	out.close();
}

void printSource(int row_low, int cols_low)
{
	int row_high = row_low + 8;
	int cols_high = cols_low + 8;

	cout<<"------Source-----"<<endl;
	for(int row = row_low; row < row_high; row++)
	{
		for(int col = cols_low; col < cols_high; col++)
		{
			cout<<data[row][col]<<"  ";
		}
		cout<<endl;
	}
}

void printResult(int row_low, int cols_low)
{
	int row_high = row_low + 8;
	int cols_high = cols_low + 8;

	cout<<"------Result-----"<<endl;
	for(int row = row_low; row < row_high; row++)
	{
		for(int col = cols_low; col < cols_high; col++)
		{
			cout<<result[row][col]<<"  ";
		}
		cout<<endl;
	}
}

int main()
{
	fstream in;
	in.open("testimg.txt");
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
	vector<int> vect(512);
	result.push_back(vect);
	while (getline(in, str))
	{
		stringstream istr(str);
		while (istr>>num)
		{
			cols ++;
			data[rows].push_back(num);
			if (cols>=512)
			{
				rows ++;
				cols = 0;
				vector<int> vec;
				data.push_back(vec);

				vector<int> vect(512);
				result.push_back(vect);
			}
		}
	}
	data.pop_back();
	result.pop_back();
	
	//·Ö¿é¼ÆËã DCT
	for(int i=0; i < 512; i+=8)
	{
		for(int j =0; j<512; j+=8)
		{
			DCT2(i, j);
			/*printSource(i, j);
			printResult(i, j);
			system("pause");*/
		}
		cout<<i<<endl;
	}

	system("pause");
	writeToFile("result.txt");

	return 0;
}