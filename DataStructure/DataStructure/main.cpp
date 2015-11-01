#include"Vocabulary_structure.h"
#include"Trie_Structure.h"
#include"Document_Structure.h"
#include<time.h>
#include<iostream>
using namespace std;

//======================主函数===========================================//
int main()
{
	clock_t time[5];
	time[0]=clock();
	PVocabularyTable PVobTab;
	PVobTab=Hash_Creat_VocabularyTable();
	time[1]=clock();
	cout<<"建立哈希表所用时间："<<time[1]-time[0]<<"ms"<<endl;

	SearchWordInVocabulary(PVobTab);
	time[2]=clock();
	cout<<"查找单词所用时间：  "<<time[2]-time[1]<<"ms"<<endl;

	MostFrequentWord(PVobTab);
	time[3]=clock();
	cout<<"单词排序所用时间：  "<<time[3]-time[2]<<"ms"<<endl;

	PVcabularyTree Dictionary=new Node1;
	time[0]=clock();
	Creat_VocabularyTree(Dictionary);
	time[1]=clock();
	cout<<"建立字典树所用时间为  "<<time[1]-time[0]<<"ms"<<endl; 

	TotPrefixWord(Dictionary);
	time[2]=clock();
	cout<<"查找前缀单词所用时间为"<<time[2]-time[1]<<"ms"<<endl;

	PrefixFrequence(Dictionary);
	time[3]=clock();
	cout<<"查询前缀最高词频前十所用时间为："<<time[3]-time[2]<<"ms"<<endl;

	time[0]=clock();
	PTree DocumentTree = new Tree;
	InitialTNode2(DocumentTree,'\0');
	CreatDocumentTree(DocumentTree);
	time[1] = clock();
	cout<<"建立树所用时间为:"<<time[1] - time[0]<<"ms"<<endl;

	SearchInDocumentTree(DocumentTree);
	time[2] = clock();
	cout<<"查询一个单词所用时间为:"<<time[2]-time[1]<<"ms"<<endl;

	FILE *TwoWorld = fopen("TwoWordInDocument/TwoWordInDocument.txt","r");
	FILE *TwoWorld_Res = fopen("TwoWordInDocument/TwoWordInDocument_Result.txt","w");
	TwoAndMultiWordInDoc(DocumentTree,TwoWorld, TwoWorld_Res,2,true);	
	time[3] = clock();
	cout<<"查询两个连续单词所用时间为:"<<time[3]-time[2]<<"ms"<<endl;

	FILE *MultiWordInDoc = fopen("MultiWordInDocument/MultiWordInDocument.txt","r");
	FILE *MultiWordInDoc_Res = fopen("MultiWordInDocument/MultiWordInDocument_Result.txt","w");
	TwoAndMultiWordInDoc(DocumentTree,MultiWordInDoc,MultiWordInDoc_Res,0,false);
	time[4] = clock();
	cout<<"查询多个单词所用时间为:"<<time[4]-time[3]<<"ms"<<endl;

}