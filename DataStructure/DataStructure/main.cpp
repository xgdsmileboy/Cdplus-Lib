#include"Vocabulary_structure.h"
#include"Trie_Structure.h"
#include"Document_Structure.h"
#include<time.h>
#include<iostream>
using namespace std;

//======================������===========================================//
int main()
{
	clock_t time[5];
	time[0]=clock();
	PVocabularyTable PVobTab;
	PVobTab=Hash_Creat_VocabularyTable();
	time[1]=clock();
	cout<<"������ϣ������ʱ�䣺"<<time[1]-time[0]<<"ms"<<endl;

	SearchWordInVocabulary(PVobTab);
	time[2]=clock();
	cout<<"���ҵ�������ʱ�䣺  "<<time[2]-time[1]<<"ms"<<endl;

	MostFrequentWord(PVobTab);
	time[3]=clock();
	cout<<"������������ʱ�䣺  "<<time[3]-time[2]<<"ms"<<endl;

	PVcabularyTree Dictionary=new Node1;
	time[0]=clock();
	Creat_VocabularyTree(Dictionary);
	time[1]=clock();
	cout<<"�����ֵ�������ʱ��Ϊ  "<<time[1]-time[0]<<"ms"<<endl; 

	TotPrefixWord(Dictionary);
	time[2]=clock();
	cout<<"����ǰ׺��������ʱ��Ϊ"<<time[2]-time[1]<<"ms"<<endl;

	PrefixFrequence(Dictionary);
	time[3]=clock();
	cout<<"��ѯǰ׺��ߴ�Ƶǰʮ����ʱ��Ϊ��"<<time[3]-time[2]<<"ms"<<endl;

	time[0]=clock();
	PTree DocumentTree = new Tree;
	InitialTNode2(DocumentTree,'\0');
	CreatDocumentTree(DocumentTree);
	time[1] = clock();
	cout<<"����������ʱ��Ϊ:"<<time[1] - time[0]<<"ms"<<endl;

	SearchInDocumentTree(DocumentTree);
	time[2] = clock();
	cout<<"��ѯһ����������ʱ��Ϊ:"<<time[2]-time[1]<<"ms"<<endl;

	FILE *TwoWorld = fopen("TwoWordInDocument/TwoWordInDocument.txt","r");
	FILE *TwoWorld_Res = fopen("TwoWordInDocument/TwoWordInDocument_Result.txt","w");
	TwoAndMultiWordInDoc(DocumentTree,TwoWorld, TwoWorld_Res,2,true);	
	time[3] = clock();
	cout<<"��ѯ����������������ʱ��Ϊ:"<<time[3]-time[2]<<"ms"<<endl;

	FILE *MultiWordInDoc = fopen("MultiWordInDocument/MultiWordInDocument.txt","r");
	FILE *MultiWordInDoc_Res = fopen("MultiWordInDocument/MultiWordInDocument_Result.txt","w");
	TwoAndMultiWordInDoc(DocumentTree,MultiWordInDoc,MultiWordInDoc_Res,0,false);
	time[4] = clock();
	cout<<"��ѯ�����������ʱ��Ϊ:"<<time[4]-time[3]<<"ms"<<endl;

}