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
// 	cout<<"�����ֵ�������ʱ��Ϊ  "<<time[1]-time[0]<<"ms"<<endl; 
// 
// 	TotPrefixWord(Dictionary);
// 	time[2]=clock();
// 	cout<<"����ǰ׺��������ʱ��Ϊ"<<time[2]-time[1]<<"ms"<<endl;
// 
// 	PrefixFrequence(Dictionary);
// 	time[3]=clock();
// 	cout<<"��ѯǰ׺��ߴ�Ƶǰʮ����ʱ��Ϊ��"<<time[3]-time[2]<<"ms"<<endl;
// }