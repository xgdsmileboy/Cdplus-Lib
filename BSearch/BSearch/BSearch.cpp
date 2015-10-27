#include<iostream>
using namespace std;
#define MAX 50000

void Bsearch(int num[],int low,int high,int search_num)
{
	if(low>=high)
		cout<<"No"<<endl;
	else
	{
		int mid = (low+high)/2;
		if(search_num==num[mid])
			cout<<"Yes"<<endl;
		else
		{
			if(search_num>num[mid])
				Bsearch(num,mid+1,high,search_num);
			else
				Bsearch(num,low,mid-1,search_num);
		}
	}
}
int main()
{
	int num[MAX];
	int total_num;
	int search_num;
	cin>>total_num;
	for(int i=0;i<total_num;i++)
		cin>>num[i];
	cin>>search_num;
	Bsearch(num,0,total_num-1,search_num);
	return 0;
}