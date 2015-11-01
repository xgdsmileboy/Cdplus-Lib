#ifndef VOCABULARY_STRUCTURE_H
#define VOCABULARY_STRUCTURE_H
#include<malloc.h>
#include<iostream>
using namespace std;
#define NULL 0
#define MAX (50000)

typedef struct Node    //hash��������ṹ
{
	char   ch[50];      //���浥��
	int    count;       //���浥�ʳ��ֵ�Ƶ��
}Node,*PNode;

typedef struct vocabulary   //hash��ṹ
{
	Node  Vocab[MAX];      //��ϣ��
	int   total;           //�ܵ��ʸ����������ظ���
	int   kinds_num;        //�ܵ���������
}VocabularyTable,*PVocabularyTable;
//=========================���ڽ�����ϣ��=======================================//
int Hash( char *Vocab)           //��ϣ����
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
//=========================��ʼ����ϣ��=========================================//
void Inital_Vocabulary(PVocabularyTable PVobTab)  //��ʼ��hash������
{
	int i=0;
	PVobTab->total=0;                    //�ܵ�����Ϊ0
	PVobTab->kinds_num=0;                //�ܵ���������Ϊ0
	for(i=0;i<MAX;i++)                   //���������е��ʳ�ʼ��Ϊ�գ���������ʼ��Ϊ0
	{
		strcpy(PVobTab->Vocab[i].ch,""); //��ϣ�������нڵ�ĵ��ʳ�ʼ��Ϊ��
		PVobTab->Vocab[i].count=0;       //�ڵ��Ƶ��ʼ��Ϊ0
	}
}
//===========================���ڵ�һ��============================================//
bool Push_VocabularyTable(char* Vocab,PVocabularyTable PVobTab)  //�����ʴ���hash��
{
	int num;
	num = Hash(Vocab);                                    //hash����ɢ�е�ַ
	PNode p=&PVobTab->Vocab[num];                         //����һ����ʱ������ָ��Ҫ���뵥�ʵ�λ��
	while(strcmp(p->ch,"") &&strcmp(p->ch,Vocab))         //�ڹ�ϣ����̽�⣬�ҵ��սڵ����֮ǰ�����
	{ 
		num=(num+3)%(MAX-1);                              //�����ͻ��ʽ������̽����ɢ��
		p=&PVobTab->Vocab[num];
	}
	if(!strcmp(PVobTab->Vocab[num].ch,""))                //����ߵ�һ�����ַ���λ�ã�֮ǰû�в���õ���
	{
		strcpy(PVobTab->Vocab[num].ch,Vocab);             //�����ʲ���
		PVobTab->kinds_num++;                             //��������������һ
	}

	PVobTab->total++;                                     //��������������һ
	PVobTab->Vocab[num].count++;                          //���뵥�ʵĴ�Ƶ��һ
	return true;
}
//===============������ϣ����һ��=================================================//
PVocabularyTable Hash_Creat_VocabularyTable()            //����һ����ϣ��
{
	PVocabularyTable PVobTab=(PVocabularyTable)malloc(sizeof(VocabularyTable));   //�����ϣ��ռ�
	Inital_Vocabulary(PVobTab);                          //��ʼ����ϣ���е�����
	if(!PVobTab)                                         //�����ֵ��ռ�ʧ��
	{
		cerr<<"Have no enough space!"<<endl;
		cerr<<"Creat vocabulary_table failed!"<<endl;
		exit(-1);
	}
	char Vocab[50];                                      //��ʱ������ļ��ж���ĵ���
	FILE *fp;                                            //���ļ�
	fp=fopen("Vocabulary/vocabulary.txt","rt");
	if(!fp)                                              //�ļ���ʧ��
	{
		cerr<<"Open file \"vocabulary.txt\" failed!"<<endl;
		exit(0);
	}
	while(!feof(fp))                                     //ѭ����ȡ�����ļ�����
	{
		fscanf(fp,"%s",Vocab);                           //���뵥��
		Push_VocabularyTable(Vocab,PVobTab);             //�����ʴ����ϣ��
	}
	fclose(fp);
	//cout<<PVobTab->total<<endl;
	//cout<<PVobTab->kinds_num<<endl;
	return PVobTab;                                      //���ع�ϣ��ָ��
}
//=============================�ڶ���====================================================//
void SearchWordInVocabulary(PVocabularyTable PVobTab)    //�ڹ�ϣ���в��ҵ���
{
	FILE *search=fopen("SearchWordInVocabulary/SearchWordInVocabulary.txt","r");
	FILE *result=fopen("SearchWordInVocabulary/SearchWordInVocabulary_Result.txt","w");
	if(!search || !result)
	{
		cerr<<"Open SearchWordInVocabulary failed!"<<endl;
		exit(0);
	}
	int num,ID=1;                                        //��¼��Ҫ���ҵ��ʵı��
	char temp[50];                                       //������ʱ�����Ҫ���ҵĵ���
	PNode p=NULL;                                     
	while(!feof(search))                                 //������Ҫ���ҵĵ����ļ�
	{
		fprintf(result,"%s %d\n","CASE",ID);             //���Ƹ�ʽ
    	ID++;
		fscanf(search,"%s",temp);                        //����Ҫ���ҵĵ���
		num=Hash(temp);
		while(strcmp(PVobTab->Vocab[num].ch,"") && strcmp(PVobTab->Vocab[num].ch,temp))
	    {
			num=(num+3)%(MAX-1);                         //�ڹ�ϣ���а�������̽����ɢ�еķ�ʽ����
		}
		if(!strcmp(PVobTab->Vocab[num].ch,""))           //�ҵ�һ����λ��
		{
			fprintf(result,"%s\n","NO");                 //���ҵ��ʲ����ڣ������NO��
		}
		else
			fprintf(result,"%d\n",PVobTab->Vocab[num].count);  //���ҳɹ���������ʵĴ�Ƶ
	}
	fclose(search);                                      //�ر��ļ�
	fclose(result);
	
}
//================================���ڵ�����================================================//
int Q_Sort(PVocabularyTable PVobTab,int low,int high)    //��������
{
	int pivodkey;
	char ch[50];                                         //���������������ַ�������λ��
	int count;                                           //��������
	int i=low;
	pivodkey=PVobTab->Vocab[low].count;                  //���ŵĲ��սڵ���Ϣ
	while(low<high)                                      //ָ���ƶ����������������
	{
		while(low<high && PVobTab->Vocab[high].count<=pivodkey)  //�ҵ��Ȳ��մ�Ƶ��ģ����յ���low�ˣ�
			high--;
 
		strcpy(ch,PVobTab->Vocab[low].ch);                       //�ڵ㽻��
		strcpy(PVobTab->Vocab[low].ch,PVobTab->Vocab[high].ch);
		strcpy(PVobTab->Vocab[high].ch,ch);
		count=PVobTab->Vocab[low].count;
		PVobTab->Vocab[low].count=PVobTab->Vocab[high].count;
		PVobTab->Vocab[high].count=count;

		while(low<high && PVobTab->Vocab[low].count>=pivodkey)    //�ҵ��Ȳ��մ�ƵС�ģ����յ���high�ˣ�
			low++;

		strcpy(ch,PVobTab->Vocab[low].ch);                        //�ڵ㽻��
		strcpy(PVobTab->Vocab[low].ch,PVobTab->Vocab[high].ch);
		strcpy(PVobTab->Vocab[high].ch,ch);
		count=PVobTab->Vocab[low].count;
		PVobTab->Vocab[low].count=PVobTab->Vocab[high].count;
		PVobTab->Vocab[high].count=count;

	}
	return low;
}
//=================================���ڵ�����===============================================//
void Qick_Sort(PVocabularyTable PVobTab,int low,int high,int sign)   //��������
{
	if(low<high)
	{
		int pivotloc;
		pivotloc=Q_Sort(PVobTab,low,high);                  //���սڵ㣬����������һ��Ϊ��
		Qick_Sort(PVobTab,low,pivotloc-1,sign);             //����ǰ�벿��
		if(sign)
			Qick_Sort(PVobTab,pivotloc+1,high,sign);        //���ź�벿��
	}
}
//==================================������==============================================//
void MostFrequentWord(PVocabularyTable PVobTab)             //���Ҵ�Ƶ����ǰʮ������
{
	int j=0;
	Qick_Sort(PVobTab,0,MAX-1,0);                           //����ǰ�벿�ֿ���
	Qick_Sort(PVobTab,0,20,1);                              //ǰ20���ڴο���
	FILE *fp=fopen("MostFrequenceWord/MostFrequenceWord.txt","w");
	if(!fp)
	{
		cout<<"Open file \"MostFrequenceWord.txt\" failed!"<<endl;
		exit(-1);
	}
	while(j<10)                                             //��ǰʮ����Ƶ�������
	{
		fprintf(fp,"%s %d\n",PVobTab->Vocab[j].ch,PVobTab->Vocab[j].count);
		j++;
	}
	fclose(fp);
}
//================================================================================//
//================================================================================//
#endif