#include <iostream>
#include<fstream>
#include<string.h>
#include "winsocket.h"
#define LEN 50
using namespace std;
char buf4[LEN] = {};

struct UDPHeader
{
	 char msg_type; //包类型  命令或者数据
	 char msg;      //数据
     int  total;    //总包数
     int  curr;     //当前包数
     int  len;      //数据部分的长度
};

DWORD WINAPI threadProcess(LPVOID lpParam)
{
	UDPHeader udpheader;
	udpheader.msg_type = (char)"1";
	udpheader.total = 100;
	udpheader.curr = 5;
	udpheader.len = 1024;
	//udpheader.msg;
	ifstream myFile;
	Client UDP1;
	
	//与数据发送机一致

	UDP1.init(UDP_DATA,"127.0.0.1",8000);
myFile.open("F:\\test.txt",ios::binary);
if (myFile.is_open()){
		while (!myFile.eof())
		{
			myFile.read(buf4,LEN);
			memcpy((char*) udpheader.msg,buf4,strlen(buf4));
			cout<<udpheader.msg;
		}
	}
	myFile.close();
while (1)
{
	
    UDP1.sendData(buf4,LEN);
	
}
}
void main()
{
	HANDLE thread_send=CreateThread(NULL,0,threadProcess,NULL,0,NULL);//创建接收线程
	if (thread_send==NULL)
			{
				cout<<"创建接收线程失败！"<<endl;
			}
	assert(thread_send!=NULL);
	CloseHandle(thread_send);//关闭线程
	while(1)
	{
		//cout<<buf4<<endl;
	}
}