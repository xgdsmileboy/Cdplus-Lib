#include <stdio.h>
#include "winsock2.h"
#pragma comment(lib, "ws2_32.lib")//加载依赖库（方法二：项目属性-链接器-输入-附加依赖项：填入ws2_32.lib）

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

 WSAStartup(MAKEWORD(2,2), &wsaData);//根据版本通知操作系统，启用SOCKET的DLL库，必须的
 udp_socket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);//创建socket
 printf("Running in client mode...\n");

 udpAddr.sin_family=AF_INET;
 udpAddr.sin_port=htons(Port);
 udpAddr.sin_addr.s_addr=Addr;
 while(1)//循环发送
 {
  gets_s(SendBuf,BufLen);
  sendto(udp_socket,SendBuf,BufLen,0,(sockaddr*)&udpAddr,sizeof(udpAddr));//往指定IP的指定端口发送数据
 }
 closesocket(udp_socket);//关闭socket
 WSACleanup();   //释放套接字资源;
 return 1;
}