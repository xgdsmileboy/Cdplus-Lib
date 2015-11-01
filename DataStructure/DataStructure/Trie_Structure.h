#include<iostream>
#include<string>
#include<malloc.h>
using namespace std;
#define NULL 0

typedef struct Node1        //字典树结构
{
	char word;             //字母
	int count;             //单词词频
	int firsttime;         //插入该新单词的次序
	struct Node1 *next[26]; //26个孩子指针
}Node1,*PNode1,*PVcabularyTree;

//======================初始化字典树的节点================================//
void Initial_Node1(PNode1 &node, char word)  //初始化字典树的节点
{
	node->count = 0;                       //节点单词词频初始化为0
	for (int i=0; i<26; i++)               //将26个孩子指针置为空
	{
		node->next[i] = NULL;
		node->firsttime=10000000;          //首次出现置一个较大值
	}
	node->word = word;                     //初始化节点字母
}
//=========================建立字典树===================================//
void Creat_VocabularyTree(PVcabularyTree VT)    //建立字典树
{
	FILE *Vocabulary=fopen("Vocabulary/vocabulary.txt","r");
	if(!Vocabulary)
	{
		cerr<<"Open file \"Vocabulary.txt\" failed!"<<endl;
		exit(0);
	}
	Initial_Node1(VT, '\0');                     //初始化树的第一个节点
	PNode1 CurrNode1=VT;
	int time=1;
	while (!feof(Vocabulary))                   //读入单词建立字典树
	{
		char Temp[50]="";                       //临时保存读入的单词
		CurrNode1 = VT;
		fscanf(Vocabulary,"%s",Temp);           //读单词
		for (int i=0; Temp[i]!='\0'; i++)       //单词解析，按字母
		{
			if (CurrNode1->next[ Temp[i]-'a' ] != NULL)                 //已经初始化过该节点
			{
				if ( Temp[i+1] == '\0' )                               //单词解析完，
				{
					CurrNode1->next[Temp[i]-'a']->count++;              //词频加一
					if(CurrNode1->next[Temp[i]-'a']->firsttime > time)  //记录单词插入的次序，重复单词不算次序
					{
						CurrNode1->next[Temp[i]-'a']->firsttime=time;
						time++;
					}
					break;
				}
				CurrNode1 = CurrNode1->next[ Temp[i]-'a' ];     //逐步解析
			}
			else
			{
				PNode1 Newnode = new Node1;                     //该节点的对应后继节点未初始化过
				Initial_Node1(Newnode, Temp[i]);               //用当前读到的字母初始化后继节点
			    CurrNode1->next[ Temp[i]-'a' ] = Newnode;      //新节点连接到字典树中
			    if ( Temp[i+1] == '\0' )                      //单词解析完，同上
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
	fclose(Vocabulary);    //关闭文件
}
//==========================用于第四问======================================//
void Print_PrefixWord(string Preword,PNode1 CurrNode1,FILE *Pre_Result)
{                                                         //输出前缀查找到的单词
	int flag=1;                                           //标志，防止同一个节点单词输出多次
	for(int i=0;i<26;i++)
	{
		if(CurrNode1->count!=0 && flag)                    //节点单词存在，输出
		{
			flag=0;
			fprintf(Pre_Result,"%s\n",Preword.c_str());
		}
		if(CurrNode1->next[i]!=NULL)                       //后继不空，递归输出以后的单词
		{
			Print_PrefixWord(Preword+char(i+'a'),CurrNode1->next[i],Pre_Result);
		}
	}
}
//=============================第四问======================================//
void TotPrefixWord(PVcabularyTree Dic)                     //前缀单词查找
{
	FILE *PrefixWord=fopen("TotPrefixWord/TotPrefixWord.txt","r");
	FILE *Pre_Result=fopen("TotPrefixWord/TotPrefixWord_Result.txt","w");
	if(!PrefixWord || !Pre_Result)
	{
		cerr<<"Open file \"TotPrefixWord\" failed!"<<endl;
		exit(0);
	}
	char Temp[50]="0";
	int ID=1;                                              //单词次序
	while(!feof(PrefixWord))                               //遍历查找的单词前缀文件
	{
		PNode1 CurrNode1=Dic;
		int i=0;
		fprintf(Pre_Result,"%s %d\n","CASE",ID);           //输出格式控制
		ID++;
		fscanf(PrefixWord,"%s",Temp);                      //读入前缀
		for(i=0;Temp[i]!='\0';i++)                         //前缀解析
		{
			if(CurrNode1->next[Temp[i]-'a']==NULL)          //不存在该前缀单词
				break;
			CurrNode1=CurrNode1->next[Temp[i]-'a'];
		}
		if(Temp[i]!='\0')                                  //不存在
			continue;
		Print_PrefixWord(Temp,CurrNode1,Pre_Result);        //输出前缀对应的单词
	}
	fclose(PrefixWord);                                    //关闭文件
	fclose(Pre_Result);
}
//===============================用于第五问=========================================//
typedef struct List                                 //保存前缀对应单词的top10链表
{
	PNode1 node;                                     //节点指针
	string Vocab;                                   //单词
	int length;                                     //链表长度，不大于10，否则从尾删除节点
	struct List *next;                              //后继指针
}Linklist,*PLinklist;
//=====================用于第无问==============//
void Push_Linklist(PNode1 CurrNode1,PLinklist head,string Preword)  //将单词插入链表中
{
	if(head->next==NULL)                                          //链表空，直接插入
	{
		PLinklist p=new Linklist;
	    p->Vocab=Preword;
		p->node=CurrNode1;
		p->next=head->next;
		head->next=p;
	    head->length++;
	}
	else                                               //链表不空
	{
		PLinklist list=head;
		while(list->next!=NULL && list->next->node->count>=CurrNode1->count)   //按要求找到插入位置，链表中保存的次序即要输出的次序
		{
			if(list->next->node->count==CurrNode1->count && list->next->node->firsttime<CurrNode1->firsttime)
				break;                                //当单词频数相同时，比较单词的建树过程中的次序，后插入优先
			list=list->next;
		}
		PLinklist p=new Linklist;                     //节点信息完全复制
		p->Vocab=Preword;
		p->node=CurrNode1;
		p->next=list->next;
		list->next=p;
		head->length++;
		if(head->length>10)                          //链表长度大于10，删除尾节点
		{
			head->length--;
			while(head->next->next!=NULL)
				head=head->next;
			free(head->next);
			head->next=NULL;
		}
	}
}
//==========================用于第五问==========================================//
void Print_MostPrefixFrequence(PLinklist head,string Preword,PNode1 CurrNode1)
{                                                //递归查找前缀单词，保存到链表中
	//cout<<Preword<<endl;
	if(CurrNode1->count!=0)                       //满足条件，插入链表
	{
		Push_Linklist(CurrNode1,head,Preword);
	}
	for(int i=0;i<26;i++)                        //递归孩子节点
	{
		if(CurrNode1->next[i]!=NULL)
			Print_MostPrefixFrequence(head,Preword+char(i+'a'),CurrNode1->next[i]);
	}
}
//=============================第五问============================================//
void PrefixFrequence(PVcabularyTree Dic)        //查找前缀对应的top10单词
{
	FILE *PrefixFrequence=fopen("PrefixFrequence/PrefixFrequence.txt","r");
	FILE *result=fopen("PrefixFrequence/PrefixFrequence_Result.txt","w");
	PLinklist Head=new Linklist;                //辅助链表，不存top10节点
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
	while(!feof(PrefixFrequence))                     //遍历前缀文档
	{
		PNode1 CurrNode1=Dic;
		int i=0;
	    fprintf(result,"%s %d:\n","CASE",ID);         //控制输入到文件的格式
		ID++;
		fscanf(PrefixFrequence,"%s",Temp);            //读入前缀
		for(i=0;Temp[i]!='\0';i++)
		{
			if(CurrNode1->next[Temp[i]-'a']==NULL)     //不存在该前缀单词
				break;
			CurrNode1=CurrNode1->next[Temp[i]-'a'];
		}
		if(Temp[i]!='\0')                             //不存在该前缀单词
			continue;
		Print_MostPrefixFrequence(Head,Temp,CurrNode1); //查找前缀对应top10单词，把top10保存到链表Head中
		PLinklist p=Head,pre=NULL;                     //将top10输入到文件
		for(p=p->next,Head->next=NULL;p->next!=NULL && Head->length;Head->length--)
		{
			fprintf(result,"%s %d\n",p->Vocab.c_str(),p->node->count);
			pre=p;
			p=p->next;
			free(pre);
		}
		if(p->node)                                    //链表尾节点
		{
			fprintf(result,"%s %d\n",p->Vocab.c_str(),p->node->count);
			free(p);
		}
	}
	fclose(PrefixFrequence);                          //关闭文件
	fclose(result);
}
//==========================================================================//