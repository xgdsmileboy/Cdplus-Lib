
#include "winsocket.h"

void Client::init(int inet_type,char*addr,unsigned short port)
{
	
	int rslt;
	m_Protocaltype=inet_type;
	if(m_Protocaltype==TCP_DATA)//TCP数据
		m_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//创建TCP套接字
	else if(m_Protocaltype==UDP_DATA)//UDP数据
		m_socket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);//创建UDP套接字
	    //m_socket=socket(AF_INET,SO_BROADCAST,IPPROTO_UDP);//创建UDP套接字
	assert(m_socket!=INVALID_SOCKET);
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.S_un.S_addr=inet_addr(addr);
	serverAddr.sin_port=htons(port);
	memset(serverAddr.sin_zero,0,8);
	if(m_Protocaltype==TCP_DATA)//TCP数据
	{
		rslt=connect(m_socket,(sockaddr*)&serverAddr,sizeof(sockaddr));//客户端连接请求
		if (rslt!=0)
		{
			cout<<"TCP客户端连接请求失败！"<<endl;
		}
		assert(rslt==0);
	}
	else
	{////////////////////////////////////////////////////////////////
		SOCKADDR_IN addrClient;//定义地址结构体变量addrSrv
		addrClient.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//本机接收来自任何IP，但是端口必须设定好。
		addrClient.sin_family=AF_INET;//指定该地址家族，在这里必须设为AF_INET。
		addrClient.sin_port=htons(port); //（u_short）从主机字节序转换为网络字节序 ，注意要用1024以上的端口号。

		int nRecvBuf=60*1024;//设置为60K
		setsockopt(m_socket,SOL_SOCKET,SO_BROADCAST,(const char*)&nRecvBuf,sizeof(int));

		bind(m_socket,(SOCKADDR*)&addrClient,sizeof(addrClient));//绑定到本地地址和端口上。

	}
}

void Client::sendData(const char * buff,const int len)//发送数据
{
	int rslt;
	int addrLen=sizeof(sockaddr_in);
	
	if(m_Protocaltype==TCP_DATA)//TCP数据
	{
		rslt=send(m_socket,buff,len,0);
	}
	else if(m_Protocaltype==UDP_DATA)//UDP数据
	{
		rslt=sendto(m_socket,buff,len,0,(sockaddr*)&serverAddr,addrLen);
	}
	if (rslt<=0)
	{
		cout<<"发送失败！"<<endl;
	}
	assert(rslt>0);
	
}


long Client::getData(char * buff,const int len)
{
	int rslt;
	int addrLen=sizeof(sockaddr_in);
	memset(buff,0,len);
	if(m_Protocaltype==TCP_DATA)//TCP数据
	{
		rslt=recv(m_socket,buff,len,0);
	}
	else if(m_Protocaltype==UDP_DATA)//UDP数据
	{
		rslt=recvfrom(m_socket,buff,len,0,(sockaddr*)&serverAddr,&addrLen);
	}
	else
	{
		abort();
	}
	if (rslt<=0)
	{
		cout<<"接收失败！"<<endl;
	}
	assert(rslt>0);
	return rslt;
}

char* Client::getProto()
{
	if(m_Protocaltype==TCP_DATA)
		return "TCP";
	else if(m_Protocaltype==UDP_DATA)
		return "UDP";
	else
		return "";
}

char* Client::getIP()
{
	return inet_ntoa(serverAddr.sin_addr);
}

unsigned short Client::getPort()
{
	return ntohs(serverAddr.sin_port);
}

Client::Client()
{
	WSADATA wsa;
	m_Protocaltype = UDP_DATA;//默认为UDP
	int rslt=WSAStartup(WINSOCK_VERSION,&wsa);//加载WinSock DLL
	if (rslt!=0)
	{
		cout<<"加载WinSock DLL失败!"<<endl;
	}
	assert(rslt==0);
}
Client::~Client(void)
{
	if(m_socket!=INVALID_SOCKET)
		closesocket(m_socket);
	WSACleanup();//卸载WinSock DLL
}

void Server::init(int inet_type,char*addr,unsigned short port)
{
	int rslt;
	m_Protocaltype=inet_type;
	if(m_Protocaltype==TCP_DATA)//TCP数据
		m_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//创建TCP套接字
	else if(m_Protocaltype==UDP_DATA)//UDP数据
		//m_socket=socket(AF_INET,SO_BROADCAST,IPPROTO_UDP);//创建UDP套接字
	    m_socket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);//创建UDP套接字
	if (m_socket==INVALID_SOCKET)
	{
		cout<<"套接字创建失败！"<<endl;
	}
	assert(m_socket!=INVALID_SOCKET);
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.S_un.S_addr=inet_addr(addr);
	serverAddr.sin_port=htons(port);
	memset(serverAddr.sin_zero,0,8);
	rslt=bind(m_socket,(sockaddr*)&serverAddr,sizeof(serverAddr));//绑定地址和端口
	if (rslt!=0)
	{
		cout<<"服务器绑定失败！"<<endl;
	}
	assert(rslt==0);
	if(m_Protocaltype==TCP_DATA)//TCP需要侦听
	{
		rslt=listen(m_socket,MAX_TCP_CONNECT);//监听客户端连接
		if (rslt!=0)
		{
			cout<<"TCP侦听失败！"<<endl;
		}
		assert(rslt==0);
	}
}

void Server::start()
{
	int rslt;
	sockaddr_in client;//客户端地址结构
	int addrLen=sizeof(client);
	SOCKET clientSock;//客户端socket
	char buff[MAX_BUFFER_LEN];//UDP数据缓存
	while(true)
	{
		if(m_Protocaltype==TCP_DATA)//TCP数据
		{
			clientSock=accept(m_socket,(sockaddr*)&client,&addrLen);//接收请求
			if(clientSock==INVALID_SOCKET)
				break;
			if (clientSock==INVALID_SOCKET)
			{
				cout<<"TCP客户端接收请求失败！"<<endl;
			}
			assert(clientSock!=INVALID_SOCKET);
			sockaddr_in*pc=addClient(client);//添加一个客户端
			connect(pc);//连接处理函数
			SockParam sp(clientSock,pc,this);//参数结构
			HANDLE thread=CreateThread(NULL,0,threadProc,(LPVOID)&sp,0,NULL);//创建连接线程
			if (thread==NULL)
			{
				cout<<"创建连接线程失败！"<<endl;
			}
			assert(thread!=NULL);
			CloseHandle(thread);//关闭线程
			cout<<"TCP连接服务器成功";
		}
		else if(m_Protocaltype==UDP_DATA)//UDP数据
		{
			/*memset(buff,0,MAX_BUFFER_LEN);
			rslt=recvfrom(m_socket,buff,MAX_BUFFER_LEN,0,(sockaddr*)&client,&addrLen);
			assert(rslt>0);
			char resp[MAX_BUFFER_LEN]={0};//接收处理后的数据
			rslt=procRequest(&client,buff,rslt,resp);//处理请求
			rslt=sendto(m_socket,resp,rslt,0,(sockaddr*)&client,addrLen);//发送udp数据
			*/
		 
		}
	}
}

DWORD WINAPI threadProc(LPVOID lpParam)//TCP线程处理函数
{
	SockParam sp=*(SockParam*)lpParam;
	Server*s=sp.pServer;
	SOCKET sock=s->m_socket;
	SOCKET clientSock=sp.rsock;
	sockaddr_in *clientAddr=sp.raddr;

	CRITICAL_SECTION*cs=s->cs;
	int rslt;
	char req[MAX_BUFFER_LEN+1]={0};//数据缓冲区,多留一个字节，方便输出
	do
	{//改写，主要是完成中转作用
		rslt=recv(clientSock,req,MAX_BUFFER_LEN,0);//接收数据
		if(rslt<=0)
			break;
		char resp[MAX_BUFFER_LEN]={0};//接收处理后的数据
		EnterCriticalSection(cs);
		rslt=s->procRequest(clientAddr,req,rslt,resp);//处理后返回数据的长度
		LeaveCriticalSection(cs);
		assert(rslt<=MAX_BUFFER_LEN);//不会超过MAX_BUFFER_LEN
		//rslt=send(clientSock,resp,rslt,0);//发送tcp数据
		rslt=send(clientSock,req,strlen(req)+1,0);//发送tcp数据
	}
	while(rslt!=0||rslt!=SOCKET_ERROR);
	s->delClient(clientAddr);
	s->disConnect(clientAddr);//断开连接后处理
	return 0;
}

/*******************用户自定义**************************/
//用户自定义服务器处理功能函数：连接请求，请求处理，连接关闭

/***
	以下三个函数的功能由使用者自行定义,头文件包含自行设计
***/
#include <iostream>
void Server::connect(sockaddr_in*client)
{
	cout<<"客户端"<<getIP(client)<<"["<<getPort(client)<<"]"<<"连接。"<<endl;
}

int Server::procRequest(sockaddr_in*client,const char* req,int reqLen,char*resp)
{
/*	cout<<getIP(client)<<"["<<getPort(client)<<"]:"<<req<<endl;
	if(m_Protocaltype==TCP_DATA)
		strcpy(resp,"TCP回复");
	else if(m_Protocaltype==UDP_DATA)
		strcpy(resp,"UDP回复");*/
	return 10;
}

void Server::disConnect(sockaddr_in*client)
{
	cout<<"客户端"<<getIP(client)<<"["<<getPort(client)<<"]"<<"断开。"<<endl;
}

Server::Server()
{
	cs=new CRITICAL_SECTION();
	InitializeCriticalSection(cs);//初始化临界区
	WSADATA wsa;
	int rslt=WSAStartup(WINSOCK_VERSION,&wsa);//加载WinSock DLL
	if (rslt!=0)
	{
		cout<<"加载WinSock DLL失败!"<<endl;
	}
	assert(rslt==0);
}
char* Server::getProto()
{
	if(m_Protocaltype==TCP_DATA)
		return "TCP";
	else if(m_Protocaltype==UDP_DATA)
		return "UDP";
	else
		return "";
}

char* Server::getIP(sockaddr_in*addr)
{
	if(addr==NULL)
		addr=&serverAddr;
	return inet_ntoa(addr->sin_addr);
}

unsigned short Server::getPort(sockaddr_in*addr)
{
	if(addr==NULL)
		addr=&serverAddr;
	return htons(addr->sin_port);
}

sockaddr_in* Server::addClient(sockaddr_in client)
{
	sockaddr_in*pc=new sockaddr_in(client);
	clientAddrs.push_back(pc);
	return pc;
}

void Server::delClient(sockaddr_in *client)
{
	assert(client!=NULL);
	delete client;
	clientAddrs.remove(client);
}

Server::~Server(void)
{
	for(list<sockaddr_in*>::iterator i=clientAddrs.begin();i!=clientAddrs.end();++i)//清空客户端地址结构
	{
		delete *i;
	}//这种删除有没有问题！！！！
	clientAddrs.clear();
	if(m_socket!=INVALID_SOCKET)
	closesocket(m_socket);//关闭服务器socket
	WSACleanup();//卸载WinSock DLL
	DeleteCriticalSection(cs);
	delete cs;
}




