// #include"Trie_Structure.h"
// #include<iostream>
// using namespace std;
// #include<time.h>
// 
// int main()
// {
// 	clock_t time[5];
// 	PVcabularyTree Dictionary=new Node;
// 	time[0]=clock();
// 	Creat_VocabularyTree(Dictionary);
// 	time[1]=clock();
// 	cout<<"建立字典树所用时间为  "<<time[1]-time[0]<<"ms"<<endl; 
// 
// 	TotPrefixWord(Dictionary);
// 	time[2]=clock();
// 	cout<<"查找前缀单词所用时间为"<<time[2]-time[1]<<"ms"<<endl;
// 
// 	PrefixFrequence(Dictionary);
// 	time[3]=clock();
// 	cout<<"查询前缀最高词频前十所用时间为："<<time[3]-time[2]<<"ms"<<endl;
// }