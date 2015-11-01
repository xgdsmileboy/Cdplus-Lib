#include <stdio.h>
#include "polinomial.h"

void InputData(PNode LinkListHead, int Num)  //�������ʽ
{
	int data, index;
	int cycle = 1;
	printf("�������_%d_������ʽ�ĵ�_%d_���ϵ����ָ��������0 0��������:\n",Num,cycle);
	cycle++;
	scanf("%d %d",&data,&index);
	while(data != 0)
	{
		Insert_LinkList(LinkListHead, data, index);
		printf("�������_%d_������ʽ�ĵ�_%d_���ϵ����ָ��������0 0��������:\n",Num,cycle);
	    cycle++;
		scanf("%d %d",&data,&index);
	}
	return;
}

void OutPutData(PNode LinkListHead)  //�������ʽ��
{
	PNode tempHead = LinkListHead->next;
	while(tempHead != NULL)
	{
		if(tempHead->data != 1)
		{
			printf("%d*",tempHead->data);
		}
		
		printf("X^%d",tempHead->index);
		tempHead = tempHead->next;
		if(tempHead != NULL)
		{
			printf("+");
		}
	}
	printf("\n");
	return;
}

void PolinomialSum(PNode LinkListHead1, PNode LinkListHead2, PNode LinkListHead)
{
	PNode p;
	p = LinkListHead1->next;
	while(p != NULL)
	{
		Insert_LinkList(LinkListHead, p->data, p->index);
		p = p->next;
	}

	p = LinkListHead2->next;
	while(p != NULL)
	{
		Insert_LinkList(LinkListHead, p->data, p->index);
		p = p->next;
	}

	return;
}


int main()
{
	
	PNode LinkListHead1, LinkListHead2,LinkListHead;

	Creat_LinkList(LinkListHead1);  //��������ʽ����
	InputData(LinkListHead1,1);  //�����һ������ʽ

	Creat_LinkList(LinkListHead2);  //��������ʽ����
	InputData(LinkListHead2,2);  //����ڶ�������ʽ

	Creat_LinkList(LinkListHead);  //��������ʽ����
	PolinomialSum(LinkListHead1, LinkListHead2, LinkListHead); //������ʽ���

	printf("\n��һ������ʽΪ��\n");
	OutPutData(LinkListHead1);
	printf("\n�ڶ�������ʽΪ��\n");
	OutPutData(LinkListHead2);
	printf("\n��������ʽ��Ϊ��\n");
	OutPutData(LinkListHead);  //�����������ʽ�ĺ�
	return 0;
}