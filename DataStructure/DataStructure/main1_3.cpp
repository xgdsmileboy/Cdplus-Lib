// #include"Vocabulary_structure.h"
// #include<time.h>
// #include<iostream>
// using namespace std;
// 
// //======================������===========================================//
// int main()
// {
// 	clock_t time[4];
// 	time[0]=clock();
// 	PVocabularyTable PVobTab;
// 	PVobTab=Hash_Creat_VocabularyTable();
// 	time[1]=clock();
// 	cout<<"������ϣ������ʱ�䣺"<<time[1]-time[0]<<"ms"<<endl;
// 
// 	SearchWordInVocabulary(PVobTab);
// 	time[2]=clock();
// 	cout<<"���ҵ�������ʱ�䣺  "<<time[2]-time[1]<<"ms"<<endl;
// 
// 	MostFrequentWord(PVobTab);
// 	time[3]=clock();
// 	cout<<"������������ʱ�䣺  "<<time[3]-time[2]<<"ms"<<endl;
// }