#include <iostream>
#include<fstream>
#include "winsocket.h"
#define LEN 50
using namespace std;
char buf3[LEN] = {};

DWORD WINAPI threadProcess(LPVOID lpParam)
{
	ifstream myFile;
	Client UDP1;

	//�����ݷ��ͻ�һ��

	UDP1.init(UDP_DATA,"127.0.0.1",5000);
myFile.open("F:\\test.txt",ios::binary);
if (myFile.is_open()){
		while (!myFile.eof()) {
			//myFile>>buf;
			//myFile.getline(buf,500);
			myFile.read(buf3,LEN);
		}
	}
	myFile.close();
while (1)
{
    UDP1.sendData(buf3,LEN);
}
}

void main()
{
	HANDLE thread_send=CreateThread(NULL,0,threadProcess,NULL,0,NULL);//���������߳�
	if (thread_send==NULL)
			{
				cout<<"���������߳�ʧ�ܣ�"<<endl;
			}
	assert(thread_send!=NULL);
	CloseHandle(thread_send);//�ر��߳�
	while(1)
	{
		cout<<buf3<<endl;
	}
}