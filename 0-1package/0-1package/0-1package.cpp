/*******
该算法用于解决0-1背包问题，其思想是利用
n位二进制数的完全性，即在关于一个0-1背包
的问题转化成一个求n位的所有二进制数问题，
再用二进制数的各个位与n件物品进行相乘运算，
可以得到n件物品的所有组合情况，再从中挑选
出满足要求的物品组合。变量说明：
MAX： 可以一次性解决的0-1背包问题个数；
Number： 各个问题中物品总数的最大值；
输入说明：需要三行输入
*第一行：两个整数n和c，分别代表物品数和背包的容量；
*第二行：n个物品的重量； 
*第三行：n个物品所对应的价值。
第二组数据换行按照上面的方式输入，当完整输入m组测试数据后，
输入“0 0”结束输入，执行程序。
---------姜佳君 2013年3月30日
 ******/

#include<math.h>
#include<iostream>
using namespace std;
#define MAX 1000   //最多测试组数
#define Number 10

int main()
{
	int count1=0,count2=0;
	int Group=0,Group_count=0;
	int Binary[Number]={0};
	unsigned int high;
	int Biggest_pi[MAX]={0};
	int c[MAX],n[MAX];
	int wi[MAX][Number],pi[MAX][Number];
	cin>>n[Group]>>c[Group];
	while(n[Group] || c[Group])
	{
		count2=0;
		while(count2<n[Group])
		{
			cin>>wi[Group][count2];
			count2++;
		}
		count2=0;
		while(count2<n[Group])
		{
			cin>>pi[Group][count2];
			count2++;
		}
		Group++;
		cin>>n[Group]>>c[Group];
	}
	for(Group_count=0;Group_count<Group;Group_count++)
	{
		high=(int)pow(2,n[Group_count]);
		for(int data=1;data<high;data++)
		{
			for(int temp=data,count1=0;temp!=0;temp/=2,count1++)
				Binary[count1]=temp%2;
			int temp_total_wi=0;
			int temp_Biggest_pi=0;
			for(count2=0;count2<n[Group_count];count2++)
			{
				temp_total_wi += Binary[count2]*wi[Group_count][count2];
				temp_Biggest_pi += Binary[count2]*pi[Group_count][count2];
				if(temp_total_wi>=c[Group_count])
					break;
			}
			for(count1=0;count1<count2;count1++)
				Binary[count1]=0;
			if(temp_total_wi>c[Group_count] || temp_Biggest_pi<Biggest_pi[Group_count])
				continue;
			Biggest_pi[Group_count]=temp_Biggest_pi;
		}
	}
	for(Group_count=0;Group_count<Group;Group_count++)
		cout<<"第 "<<Group_count+1<<" 组数据的结果是 ："<<Biggest_pi[Group_count]<<endl;
	return 0;
}
