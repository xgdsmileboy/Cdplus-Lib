#include <stdio.h>
#include "polinomial.h"

void InputData(PNode LinkListHead, int Num)  //输入多项式
{
	int data, index;
	int cycle = 1;
	printf("请输入第_%d_个多项式的第_%d_项的系数和指数，输入0 0结束输入:\n",Num,cycle);
	cycle++;
	scanf("%d %d",&data,&index);
	while(data != 0)
	{
		Insert_LinkList(LinkListHead, data, index);
		printf("请输入第_%d_个多项式的第_%d_项的系数和指数，输入0 0结束输入:\n",Num,cycle);
	    cycle++;
		scanf("%d %d",&data,&index);
	}
	return;
}

void OutPutData(PNode LinkListHead)  //输出多项式和
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

	Creat_LinkList(LinkListHead1);  //创建多项式链表
	InputData(LinkListHead1,1);  //输入第一个多项式

	Creat_LinkList(LinkListHead2);  //创建多项式链表
	InputData(LinkListHead2,2);  //输入第二个多项式

	Creat_LinkList(LinkListHead);  //创建多项式链表
	PolinomialSum(LinkListHead1, LinkListHead2, LinkListHead); //两多项式求和

	printf("\n第一个多项式为：\n");
	OutPutData(LinkListHead1);
	printf("\n第二个多项式为：\n");
	OutPutData(LinkListHead2);
	printf("\n两个多项式和为：\n");
	OutPutData(LinkListHead);  //输出两个多项式的和
	return 0;
}