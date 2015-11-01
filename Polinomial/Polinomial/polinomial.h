# ifndef POLINOMIAL_H
# define POLINOMIAL_H
#include <malloc.h>

typedef struct Node  //链表节点结构
{
	int data;
	int index;
	struct Node *next;
} Node, *PNode;

void Creat_LinkList(PNode &head)  //创建空链表
{
	head = (PNode)malloc(sizeof(Node));
	head->data = -1000;
	head->index = -1000;
	head->next = NULL;
	return;
}

void Insert_LinkList(PNode &head, int data, int index) //向多项式链表中插入节点，包含同项合并和系数为零项删除
{
	PNode tempHead = head->next;
	PNode tempRear = head;
	while(tempHead != NULL)
	{
		if(tempHead->index < index)
		{
			tempRear = tempHead;
			tempHead = tempRear->next;
			continue;
		}
		else
		{
			if(tempHead->index == index)
			{
				tempHead->data += data;
				if(tempHead->data == 0)
				{
					tempRear->next = tempHead->next;
					free(tempHead);
				}
				return;
			}
			else
			{
				PNode newNode = (PNode) malloc(sizeof(Node));
				newNode->data = data;
				newNode->index = index;
				newNode->next = tempHead;
				tempRear->next = newNode;
				return ;
			}
		}
	}
	PNode newNode = (PNode) malloc(sizeof(Node));
	newNode->data = data;
	newNode->index = index;
	newNode->next = tempHead;
	tempRear->next = newNode;
	return ;
}

# endif