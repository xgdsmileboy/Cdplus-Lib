#include<iostream>
using namespace std;
#define MAX 50

void Merge(int num[],int low,int mid,int high)
{
	int temp[MAX];
	int flag1=low;
	int flag2=mid+1;
	int count=0;
	while(flag1<=mid && flag2<=high)
	{
		if(num[flag1]<num[flag2])
		{
			temp[count]=num[flag1];
			count++;
			flag1++;
		}
		else
		{
			temp[count]=num[flag2];
			count++;
			flag2++;
		}
	}
	while(flag1<=mid)
	{
		temp[count]=num[flag1];
		flag1++;
		count++;
	}
	while(flag2<=high)
	{
		temp[count]=num[flag2];
		flag2++;
		count++;
	}
	for(int j=0, i=low;low<=high;low++,j++)
		num[low]=temp[j];
}

void Mergsort(int *num,int low,int high)
{
    if(low<high)
	{
		int mid=(low+high)/2;
		Mergsort(num,low,mid);
		Mergsort(num,mid+1,high);
		Merge(num,low,mid,high);
	}
}

int main()
{
	int num[MAX];
	int total_num;
	cin>>total_num;
	for(int i=0;i<total_num;i++)
		cin>>num[i];
	Mergsort(num,0,total_num-1);
	for(int j=0;j<total_num;j++)
		cout<<num[j]<<endl;
	return 0;
}