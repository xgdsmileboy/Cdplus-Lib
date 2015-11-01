// #include"Vocabulary_structure.h"
// #include<time.h>
// #include<iostream>
// using namespace std;
// 
// //======================主函数===========================================//
// int main()
// {
// 	clock_t time[4];
// 	time[0]=clock();
// 	PVocabularyTable PVobTab;
// 	PVobTab=Hash_Creat_VocabularyTable();
// 	time[1]=clock();
// 	cout<<"建立哈希表所用时间："<<time[1]-time[0]<<"ms"<<endl;
// 
// 	SearchWordInVocabulary(PVobTab);
// 	time[2]=clock();
// 	cout<<"查找单词所用时间：  "<<time[2]-time[1]<<"ms"<<endl;
// 
// 	MostFrequentWord(PVobTab);
// 	time[3]=clock();
// 	cout<<"单词排序所用时间：  "<<time[3]-time[2]<<"ms"<<endl;
// }