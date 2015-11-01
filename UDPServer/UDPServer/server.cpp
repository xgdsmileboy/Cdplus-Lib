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
 int Port=8000;//�˿ڿ��Լ���

 WSAStartup(MAKEWORD(2,2), &wsaData);
 udpSocket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
 udpAddr.sin_family=AF_INET;
 udpAddr.sin_port=htons(Port);
 printf("Running in service mode...\n");

 bind(udpSocket,(SOCKADDR*)&udpAddr,sizeof(udpAddr));//�󶨶˿�
 int size=sizeof(udpAddr);
 while(1)//ѭ������
 {
	  if(udpSocket==INVALID_SOCKET){
	   Sleep(1000);//�ȴ���Ϊ����˿���Ϣ����ʱ��
	   continue;//������һ��while����������һ�����
	  }
	  int rslt = recvfrom(udpSocket,RecvBuf,BufLen,0,(SOCKADDR*)&udpAddr,&size);//������Ϣ
	  printf("Received:%s\n",RecvBuf);
 }
 closesocket(udpSocket);
 WSACleanup();   //�ͷ��׽�����Դ;
 return 1;
}