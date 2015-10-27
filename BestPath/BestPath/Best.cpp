#include<iostream>
using namespace std;

void Binary(int bina[],int n)
{
	int jinwei=0;
	bina[0]+=1;
	for(int i=0;i<n;i++)
	{
		bina[i]+=jinwei;
		jinwei=bina[i]/2;
		bina[i]-=jinwei*2;
	}
}
int main()
{
	long int high=0;
	int bina[49]={0};
	high=pow(2,28);
	cout<<high<<endl;
	//for(long int i=0;i<high;i++)
	//{
	//	Binary(bina,28);
	//	for(int j=0;j<49;j++)
	//	   cout<<bina[j];
	//	cout<<endl;
	//	for(int j=0;j<49;j++)
	//	   bina[j]=0;
	//}
}