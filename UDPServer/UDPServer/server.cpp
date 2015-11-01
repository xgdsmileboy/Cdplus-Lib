#include <stdio.h>
#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")

SOCKET udpSocket=INVALID_SOCKET;
sockaddr_in udpAddr;
const int BufLen=1024;
char RecvBuf[BufLen];

int main()
{
 WSADATA wsaData;
 int Port=8000;//端口可自己改

 WSAStartup(MAKEWORD(2,2), &wsaData);
 udpSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
 udpAddr.sin_family=AF_INET;
 udpAddr.sin_port=htons(Port);
 printf("Running in service mode...\n");

 bind(udpSocket,(SOCKADDR*)&udpAddr,sizeof(udpAddr));//绑定端口
 int size=sizeof(udpAddr);
 while(1)//循环接收
 {
	  if(udpSocket==INVALID_SOCKET){
	   Sleep(1000);//等待，为处理端口信息留出时间
	   continue;//跳到下一次while，而不是下一行语句
	  }
	  int rslt = recvfrom(udpSocket,RecvBuf,BufLen,0,(SOCKADDR*)&udpAddr,&size);//接收信息
	  printf("Received:%s\n",RecvBuf);
 }
 closesocket(udpSocket);
 WSACleanup();   //释放套接字资源;
 return 1;
}