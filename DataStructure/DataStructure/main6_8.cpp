// #include"Document_Structure.h"
// #include<iostream>
// #include<time.h>
// using namespace std;
// 
// int main()
// {
// 	clock_t time[5];
// 	time[0]=clock();
// 	PTree DocumentTree = new Tree;
// 	InitialTNode(DocumentTree,'\0');
// 	CreatDocumentTree(DocumentTree);
// 	time[1] = clock();
// 	cout<<"建立树所用时间为:"<<time[1] - time[0]<<"ms"<<endl;
// 
// 	SearchInDocumentTree(DocumentTree);
// 	time[2] = clock();
// 	cout<<"查询一个单词所用时间为:"<<time[2]-time[1]<<"ms"<<endl;
// 
// 	FILE *TwoWorld = fopen("TwoWordInDocument/TwoWordInDocument.txt","r");
// 	FILE *TwoWorld_Res = fopen("TwoWordInDocument/TwoWordInDocument_Result.txt","w");
// 	TwoAndMultiWordInDoc(DocumentTree,TwoWorld, TwoWorld_Res,2,true);	
// 	time[3] = clock();
// 	cout<<"查询两个连续单词所用时间为:"<<time[3]-time[2]<<"ms"<<endl;
// 
// 	FILE *MultiWordInDoc = fopen("MultiWordInDocument/MultiWordInDocument.txt","r");
// 	FILE *MultiWordInDoc_Res = fopen("MultiWordInDocument/MultiWordInDocument_Result.txt","w");
// 	TwoAndMultiWordInDoc(DocumentTree,MultiWordInDoc,MultiWordInDoc_Res,0,false);
// 	time[4] = clock();
// 	cout<<"查询多个单词所用时间为:"<<time[4]-time[3]<<"ms"<<endl;
// 
// 	return 0;
// }