#include <iostream>
#include<fstream>
#include "winsocket.h"
#define LEN 500
using namespace std;
char buf1[LEN] = {};
char buf2[LEN] = {};

DWORD WINAPI threadProcess(LPVOID lpParam)
{
	ifstream myFile;
	Client UDP1;
	Client UDP2;
	
	//与数据发送机一致

	UDP1.init(UDP_DATA,"127.0.0.1",5000);
	UDP2.init(UDP_DATA,"127.0.0.1",8000);
while (1)
{
	
    UDP1.getData(buf1,LEN);
	UDP2.getData(buf2,LEN);
	
}
}
void main()
{
	HANDLE thread_rec=CreateThread(NULL,0,threadProcess,NULL,0,NULL);//创建接收线程
	if (thread_rec==NULL)
			{
				cout<<"创建接收线程失败！"<<endl;
			}
	assert(thread_rec!=NULL);
	CloseHandle(thread_rec);//关闭线程
	while(thread_rec!=NULL)
	{
		cout<<buf1<<endl;
		cout<<buf2<<endl;
	}
}