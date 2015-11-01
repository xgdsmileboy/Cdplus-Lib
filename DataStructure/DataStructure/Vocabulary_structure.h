#ifndef VOCABULARY_STRUCTURE_H
#define VOCABULARY_STRUCTURE_H
#include<malloc.h>
#include<iostream>
using namespace std;
#define NULL 0
#define MAX (50000)

typedef struct Node    //hash表后的链表结构
{
	char   ch[50];      //保存单词
	int    count;       //保存单词出现的频数
}Node,*PNode;

typedef struct vocabulary   //hash表结构
{
	Node  Vocab[MAX];      //哈希表
	int   total;           //总单词个数，包含重复的
	int   kinds_num;        //总单词种类数
}VocabularyTable,*PVocabularyTable;
//=========================用于建立哈希表=======================================//
int Hash( char *Vocab)           //哈希函数
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
    while(*Vocab)
	{
	     hash = hash*a+(*Vocab++);
	     a*= b;
	} 
	return (hash&0x7FFFFFFF)%(MAX-1);
} 
//===========================================================================//
//=========================初始化哈希表=========================================//
void Inital_Vocabulary(PVocabularyTable PVobTab)  //初始化hash表内容
{
	int i=0;
	PVobTab->total=0;                    //总单词数为0
	PVobTab->kinds_num=0;                //总单词种类数为0
	for(i=0;i<MAX;i++)                   //将表中所有单词初始化为空，计数器初始化为0
	{
		strcpy(PVobTab->Vocab[i].ch,""); //哈希表中所有节点的单词初始化为空
		PVobTab->Vocab[i].count=0;       //节点词频初始化为0
	}
}
//===========================用于第一问============================================//
bool Push_VocabularyTable(char* Vocab,PVocabularyTable PVobTab)  //将单词存入hash表
{
	int num;
	num = Hash(Vocab);                                    //hash函数散列地址
	PNode p=&PVobTab->Vocab[num];                         //定义一个临时变量，指向将要插入单词的位置
	while(strcmp(p->ch,"") &&strcmp(p->ch,Vocab))         //在哈希表中探测，找到空节点或是之前插入过
	{ 
		num=(num+3)%(MAX-1);                              //处理冲突方式，线性探测再散列
		p=&PVobTab->Vocab[num];
	}
	if(!strcmp(PVobTab->Vocab[num].ch,""))                //如果走到一个空字符串位置，之前没有插入该单词
	{
		strcpy(PVobTab->Vocab[num].ch,Vocab);             //将单词插入
		PVobTab->kinds_num++;                             //将单词种类数加一
	}

	PVobTab->total++;                                     //单词总种类数加一
	PVobTab->Vocab[num].count++;                          //插入单词的词频加一
	return true;
}
//===============创建哈希表，第一问=================================================//
PVocabularyTable Hash_Creat_VocabularyTable()            //创建一个哈希表
{
	PVocabularyTable PVobTab=(PVocabularyTable)malloc(sizeof(VocabularyTable));   //申请哈希表空间
	Inital_Vocabulary(PVobTab);                          //初始化哈希表中的内容
	if(!PVobTab)                                         //申请字典表空间失败
	{
		cerr<<"Have no enough space!"<<endl;
		cerr<<"Creat vocabulary_table failed!"<<endl;
		exit(-1);
	}
	char Vocab[50];                                      //临时保存从文件中读入的单词
	FILE *fp;                                            //打开文件
	fp=fopen("Vocabulary/vocabulary.txt","rt");
	if(!fp)                                              //文件打开失败
	{
		cerr<<"Open file \"vocabulary.txt\" failed!"<<endl;
		exit(0);
	}
	while(!feof(fp))                                     //循环读取整个文件内容
	{
		fscanf(fp,"%s",Vocab);                           //读入单词
		Push_VocabularyTable(Vocab,PVobTab);             //将单词存入哈希表
	}
	fclose(fp);
	//cout<<PVobTab->total<<endl;
	//cout<<PVobTab->kinds_num<<endl;
	return PVobTab;                                      //返回哈希表指针
}
//=============================第二问====================================================//
void SearchWordInVocabulary(PVocabularyTable PVobTab)    //在哈希表中查找单词
{
	FILE *search=fopen("SearchWordInVocabulary/SearchWordInVocabulary.txt","r");
	FILE *result=fopen("SearchWordInVocabulary/SearchWordInVocabulary_Result.txt","w");
	if(!search || !result)
	{
		cerr<<"Open SearchWordInVocabulary failed!"<<endl;
		exit(0);
	}
	int num,ID=1;                                        //记录所要查找单词的编号
	char temp[50];                                       //保存临时读入的要查找的单词
	PNode p=NULL;                                     
	while(!feof(search))                                 //遍历将要查找的单词文件
	{
		fprintf(result,"%s %d\n","CASE",ID);             //控制格式
    	ID++;
		fscanf(search,"%s",temp);                        //读入要查找的单词
		num=Hash(temp);
		while(strcmp(PVobTab->Vocab[num].ch,"") && strcmp(PVobTab->Vocab[num].ch,temp))
	    {
			num=(num+3)%(MAX-1);                         //在哈希表中按照线性探测再散列的方式查找
		}
		if(!strcmp(PVobTab->Vocab[num].ch,""))           //找到一个空位置
		{
			fprintf(result,"%s\n","NO");                 //查找单词不存在，输出“NO”
		}
		else
			fprintf(result,"%d\n",PVobTab->Vocab[num].count);  //查找成功，输出单词的词频
	}
	fclose(search);                                      //关闭文件
	fclose(result);
	
}
//================================用于第三问================================================//
int Q_Sort(PVocabularyTable PVobTab,int low,int high)    //快速排序
{
	int pivodkey;
	char ch[50];                                         //辅助变量，用于字符串交换位置
	int count;                                           //辅助变量
	int i=low;
	pivodkey=PVobTab->Vocab[low].count;                  //快排的参照节点信息
	while(low<high)                                      //指针移动，对整个数组快排
	{
		while(low<high && PVobTab->Vocab[high].count<=pivodkey)  //找到比参照词频大的（参照点在low端）
			high--;
 
		strcpy(ch,PVobTab->Vocab[low].ch);                       //节点交换
		strcpy(PVobTab->Vocab[low].ch,PVobTab->Vocab[high].ch);
		strcpy(PVobTab->Vocab[high].ch,ch);
		count=PVobTab->Vocab[low].count;
		PVobTab->Vocab[low].count=PVobTab->Vocab[high].count;
		PVobTab->Vocab[high].count=count;

		while(low<high && PVobTab->Vocab[low].count>=pivodkey)    //找到比参照词频小的（参照点在high端）
			low++;

		strcpy(ch,PVobTab->Vocab[low].ch);                        //节点交换
		strcpy(PVobTab->Vocab[low].ch,PVobTab->Vocab[high].ch);
		strcpy(PVobTab->Vocab[high].ch,ch);
		count=PVobTab->Vocab[low].count;
		PVobTab->Vocab[low].count=PVobTab->Vocab[high].count;
		PVobTab->Vocab[high].count=count;

	}
	return low;
}
//=================================用于第三问===============================================//
void Qick_Sort(PVocabularyTable PVobTab,int low,int high,int sign)   //快速排序
{
	if(low<high)
	{
		int pivotloc;
		pivotloc=Q_Sort(PVobTab,low,high);                  //参照节点，将排序内容一分为二
		Qick_Sort(PVobTab,low,pivotloc-1,sign);             //快排前半部分
		if(sign)
			Qick_Sort(PVobTab,pivotloc+1,high,sign);        //快排后半部分
	}
}
//==================================第三问==============================================//
void MostFrequentWord(PVocabularyTable PVobTab)             //查找词频最大的前十个单词
{
	int j=0;
	Qick_Sort(PVobTab,0,MAX-1,0);                           //整体前半部分快排
	Qick_Sort(PVobTab,0,20,1);                              //前20个在次快排
	FILE *fp=fopen("MostFrequenceWord/MostFrequenceWord.txt","w");
	if(!fp)
	{
		cout<<"Open file \"MostFrequenceWord.txt\" failed!"<<endl;
		exit(-1);
	}
	while(j<10)                                             //将前十个词频最大的输出
	{
		fprintf(fp,"%s %d\n",PVobTab->Vocab[j].ch,PVobTab->Vocab[j].count);
		j++;
	}
	fclose(fp);
}
//================================================================================//
//================================================================================//
#endif