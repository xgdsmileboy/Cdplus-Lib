#include <stdio.h>
#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")//���������⣨����������Ŀ����-������-����-�������������ws2_32.lib��

SOCKET udp_socket;
sockaddr_in udpAddr;
const int BufLen=1024;
char SendBuf[BufLen];

int main(int argc,char** argv)
{
 WSADATA wsaData;
 long int Addr;
 int Port;

// if(argc!=3){printf("Usage:%s [<IP> <Port>]\n",argv[0]);return 0;}
 Addr=inet_addr("127.0.0.1");
 Port=atoi("8000");

 WSAStartup(MAKEWORD(2,2), &wsaData);//���ݰ汾֪ͨ����ϵͳ������SOCKET��DLL�⣬�����
 udp_socket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);//����socket
 printf("Running in client mode...\n");

 udpAddr.sin_family=AF_INET;
 udpAddr.sin_port=htons(Port);
 udpAddr.sin_addr.s_addr=Addr;
 while(1)//ѭ������
 {
  gets_s(SendBuf,BufLen);
  sendto(udp_socket,SendBuf,BufLen,0,(sockaddr*)&udpAddr,sizeof(udpAddr));//��ָ��IP��ָ���˿ڷ�������
 }
 closesocket(udp_socket);//�ر�socket
 WSACleanup();   //�ͷ��׽�����Դ;
 return 1;
}