/*******
���㷨���ڽ��0-1�������⣬��˼��������
nλ������������ȫ�ԣ����ڹ���һ��0-1����
������ת����һ����nλ�����ж����������⣬
���ö��������ĸ���λ��n����Ʒ����������㣬
���Եõ�n����Ʒ���������������ٴ�����ѡ
������Ҫ�����Ʒ��ϡ�����˵����
MAX�� ����һ���Խ����0-1�������������
Number�� ������������Ʒ���������ֵ��
����˵������Ҫ��������
*��һ�У���������n��c���ֱ������Ʒ���ͱ�����������
*�ڶ��У�n����Ʒ�������� 
*�����У�n����Ʒ����Ӧ�ļ�ֵ��
�ڶ������ݻ��а�������ķ�ʽ���룬����������m��������ݺ�
���롰0 0���������룬ִ�г���
---------���Ѿ� 2013��3��30��
 ******/

#include<math.h>
#include<iostream>
using namespace std;
#define MAX 1000   //����������
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
		cout<<"�� "<<Group_count+1<<" �����ݵĽ���� ��"<<Biggest_pi[Group_count]<<endl;
	return 0;
}
