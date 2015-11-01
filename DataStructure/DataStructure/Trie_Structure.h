#include<iostream>
#include<string>
#include<malloc.h>
using namespace std;
#define NULL 0

typedef struct Node1        //�ֵ����ṹ
{
	char word;             //��ĸ
	int count;             //���ʴ�Ƶ
	int firsttime;         //������µ��ʵĴ���
	struct Node1 *next[26]; //26������ָ��
}Node1,*PNode1,*PVcabularyTree;

//======================��ʼ���ֵ����Ľڵ�================================//
void Initial_Node1(PNode1 &node, char word)  //��ʼ���ֵ����Ľڵ�
{
	node->count = 0;                       //�ڵ㵥�ʴ�Ƶ��ʼ��Ϊ0
	for (int i=0; i<26; i++)               //��26������ָ����Ϊ��
	{
		node->next[i] = NULL;
		node->firsttime=10000000;          //�״γ�����һ���ϴ�ֵ
	}
	node->word = word;                     //��ʼ���ڵ���ĸ
}
//=========================�����ֵ���===================================//
void Creat_VocabularyTree(PVcabularyTree VT)    //�����ֵ���
{
	FILE *Vocabulary=fopen("Vocabulary/vocabulary.txt","r");
	if(!Vocabulary)
	{
		cerr<<"Open file \"Vocabulary.txt\" failed!"<<endl;
		exit(0);
	}
	Initial_Node1(VT, '\0');                     //��ʼ�����ĵ�һ���ڵ�
	PNode1 CurrNode1=VT;
	int time=1;
	while (!feof(Vocabulary))                   //���뵥�ʽ����ֵ���
	{
		char Temp[50]="";                       //��ʱ�������ĵ���
		CurrNode1 = VT;
		fscanf(Vocabulary,"%s",Temp);           //������
		for (int i=0; Temp[i]!='\0'; i++)       //���ʽ���������ĸ
		{
			if (CurrNode1->next[ Temp[i]-'a' ] != NULL)                 //�Ѿ���ʼ�����ýڵ�
			{
				if ( Temp[i+1] == '\0' )                               //���ʽ����꣬
				{
					CurrNode1->next[Temp[i]-'a']->count++;              //��Ƶ��һ
					if(CurrNode1->next[Temp[i]-'a']->firsttime > time)  //��¼���ʲ���Ĵ����ظ����ʲ������
					{
						CurrNode1->next[Temp[i]-'a']->firsttime=time;
						time++;
					}
					break;
				}
				CurrNode1 = CurrNode1->next[ Temp[i]-'a' ];     //�𲽽���
			}
			else
			{
				PNode1 Newnode = new Node1;                     //�ýڵ�Ķ�Ӧ��̽ڵ�δ��ʼ����
				Initial_Node1(Newnode, Temp[i]);               //�õ�ǰ��������ĸ��ʼ����̽ڵ�
			    CurrNode1->next[ Temp[i]-'a' ] = Newnode;      //�½ڵ����ӵ��ֵ�����
			    if ( Temp[i+1] == '\0' )                      //���ʽ����꣬ͬ��
			    {
					if(Newnode->firsttime>time)
					{
						Newnode->firsttime=time;
						time++;
					}
					Newnode->count++;
				}
				CurrNode1 = CurrNode1->next[Temp[i]-'a'];
			}//else
		}//for(i=0)
	}//while
	fclose(Vocabulary);    //�ر��ļ�
}
//==========================���ڵ�����======================================//
void Print_PrefixWord(string Preword,PNode1 CurrNode1,FILE *Pre_Result)
{                                                         //���ǰ׺���ҵ��ĵ���
	int flag=1;                                           //��־����ֹͬһ���ڵ㵥��������
	for(int i=0;i<26;i++)
	{
		if(CurrNode1->count!=0 && flag)                    //�ڵ㵥�ʴ��ڣ����
		{
			flag=0;
			fprintf(Pre_Result,"%s\n",Preword.c_str());
		}
		if(CurrNode1->next[i]!=NULL)                       //��̲��գ��ݹ�����Ժ�ĵ���
		{
			Print_PrefixWord(Preword+char(i+'a'),CurrNode1->next[i],Pre_Result);
		}
	}
}
//=============================������======================================//
void TotPrefixWord(PVcabularyTree Dic)                     //ǰ׺���ʲ���
{
	FILE *PrefixWord=fopen("TotPrefixWord/TotPrefixWord.txt","r");
	FILE *Pre_Result=fopen("TotPrefixWord/TotPrefixWord_Result.txt","w");
	if(!PrefixWord || !Pre_Result)
	{
		cerr<<"Open file \"TotPrefixWord\" failed!"<<endl;
		exit(0);
	}
	char Temp[50]="0";
	int ID=1;                                              //���ʴ���
	while(!feof(PrefixWord))                               //�������ҵĵ���ǰ׺�ļ�
	{
		PNode1 CurrNode1=Dic;
		int i=0;
		fprintf(Pre_Result,"%s %d\n","CASE",ID);           //�����ʽ����
		ID++;
		fscanf(PrefixWord,"%s",Temp);                      //����ǰ׺
		for(i=0;Temp[i]!='\0';i++)                         //ǰ׺����
		{
			if(CurrNode1->next[Temp[i]-'a']==NULL)          //�����ڸ�ǰ׺����
				break;
			CurrNode1=CurrNode1->next[Temp[i]-'a'];
		}
		if(Temp[i]!='\0')                                  //������
			continue;
		Print_PrefixWord(Temp,CurrNode1,Pre_Result);        //���ǰ׺��Ӧ�ĵ���
	}
	fclose(PrefixWord);                                    //�ر��ļ�
	fclose(Pre_Result);
}
//===============================���ڵ�����=========================================//
typedef struct List                                 //����ǰ׺��Ӧ���ʵ�top10����
{
	PNode1 node;                                     //�ڵ�ָ��
	string Vocab;                                   //����
	int length;                                     //�����ȣ�������10�������βɾ���ڵ�
	struct List *next;                              //���ָ��
}Linklist,*PLinklist;
//=====================���ڵ�����==============//
void Push_Linklist(PNode1 CurrNode1,PLinklist head,string Preword)  //�����ʲ���������
{
	if(head->next==NULL)                                          //����գ�ֱ�Ӳ���
	{
		PLinklist p=new Linklist;
	    p->Vocab=Preword;
		p->node=CurrNode1;
		p->next=head->next;
		head->next=p;
	    head->length++;
	}
	else                                               //������
	{
		PLinklist list=head;
		while(list->next!=NULL && list->next->node->count>=CurrNode1->count)   //��Ҫ���ҵ�����λ�ã������б���Ĵ���Ҫ����Ĵ���
		{
			if(list->next->node->count==CurrNode1->count && list->next->node->firsttime<CurrNode1->firsttime)
				break;                                //������Ƶ����ͬʱ���Ƚϵ��ʵĽ��������еĴ��򣬺��������
			list=list->next;
		}
		PLinklist p=new Linklist;                     //�ڵ���Ϣ��ȫ����
		p->Vocab=Preword;
		p->node=CurrNode1;
		p->next=list->next;
		list->next=p;
		head->length++;
		if(head->length>10)                          //�����ȴ���10��ɾ��β�ڵ�
		{
			head->length--;
			while(head->next->next!=NULL)
				head=head->next;
			free(head->next);
			head->next=NULL;
		}
	}
}
//==========================���ڵ�����==========================================//
void Print_MostPrefixFrequence(PLinklist head,string Preword,PNode1 CurrNode1)
{                                                //�ݹ����ǰ׺���ʣ����浽������
	//cout<<Preword<<endl;
	if(CurrNode1->count!=0)                       //������������������
	{
		Push_Linklist(CurrNode1,head,Preword);
	}
	for(int i=0;i<26;i++)                        //�ݹ麢�ӽڵ�
	{
		if(CurrNode1->next[i]!=NULL)
			Print_MostPrefixFrequence(head,Preword+char(i+'a'),CurrNode1->next[i]);
	}
}
//=============================������============================================//
void PrefixFrequence(PVcabularyTree Dic)        //����ǰ׺��Ӧ��top10����
{
	FILE *PrefixFrequence=fopen("PrefixFrequence/PrefixFrequence.txt","r");
	FILE *result=fopen("PrefixFrequence/PrefixFrequence_Result.txt","w");
	PLinklist Head=new Linklist;                //������������top10�ڵ�
	Head->length=0;
    Head->Vocab="";
	Head->next=NULL;
	Head->node=NULL;
	if(!PrefixFrequence || !result)
	{
		cerr<<"Open file \"PrefixFrequence\" failed!"<<endl;
		exit(0);
	}
	char Temp[50];
	int ID=1;
	while(!feof(PrefixFrequence))                     //����ǰ׺�ĵ�
	{
		PNode1 CurrNode1=Dic;
		int i=0;
	    fprintf(result,"%s %d:\n","CASE",ID);         //�������뵽�ļ��ĸ�ʽ
		ID++;
		fscanf(PrefixFrequence,"%s",Temp);            //����ǰ׺
		for(i=0;Temp[i]!='\0';i++)
		{
			if(CurrNode1->next[Temp[i]-'a']==NULL)     //�����ڸ�ǰ׺����
				break;
			CurrNode1=CurrNode1->next[Temp[i]-'a'];
		}
		if(Temp[i]!='\0')                             //�����ڸ�ǰ׺����
			continue;
		Print_MostPrefixFrequence(Head,Temp,CurrNode1); //����ǰ׺��Ӧtop10���ʣ���top10���浽����Head��
		PLinklist p=Head,pre=NULL;                     //��top10���뵽�ļ�
		for(p=p->next,Head->next=NULL;p->next!=NULL && Head->length;Head->length--)
		{
			fprintf(result,"%s %d\n",p->Vocab.c_str(),p->node->count);
			pre=p;
			p=p->next;
			free(pre);
		}
		if(p->node)                                    //����β�ڵ�
		{
			fprintf(result,"%s %d\n",p->Vocab.c_str(),p->node->count);
			free(p);
		}
	}
	fclose(PrefixFrequence);                          //�ر��ļ�
	fclose(result);
}
//==========================================================================//