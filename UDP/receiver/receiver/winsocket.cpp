
#include "winsocket.h"

void Client::init(int inet_type,char*addr,unsigned short port)
{
	
	int rslt;
	m_Protocaltype=inet_type;
	if(m_Protocaltype==TCP_DATA)//TCP����
		m_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//����TCP�׽���
	else if(m_Protocaltype==UDP_DATA)//UDP����
		m_socket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);//����UDP�׽���
	    //m_socket=socket(AF_INET,SO_BROADCAST,IPPROTO_UDP);//����UDP�׽���
	assert(m_socket!=INVALID_SOCKET);
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.S_un.S_addr=inet_addr(addr);
	serverAddr.sin_port=htons(port);
	memset(serverAddr.sin_zero,0,8);
	if(m_Protocaltype==TCP_DATA)//TCP����
	{
		rslt=connect(m_socket,(sockaddr*)&serverAddr,sizeof(sockaddr));//�ͻ�����������
		if (rslt!=0)
		{
			cout<<"TCP�ͻ�����������ʧ�ܣ�"<<endl;
		}
		assert(rslt==0);
	}
	else
	{////////////////////////////////////////////////////////////////
		SOCKADDR_IN addrClient;//�����ַ�ṹ�����addrSrv
		addrClient.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//�������������κ�IP�����Ƕ˿ڱ����趨�á�
		addrClient.sin_family=AF_INET;//ָ���õ�ַ���壬�����������ΪAF_INET��
		addrClient.sin_port=htons(port); //��u_short���������ֽ���ת��Ϊ�����ֽ��� ��ע��Ҫ��1024���ϵĶ˿ںš�

		int nRecvBuf=60*1024;//����Ϊ60K
		setsockopt(m_socket,SOL_SOCKET,SO_BROADCAST,(const char*)&nRecvBuf,sizeof(int));

		bind(m_socket,(SOCKADDR*)&addrClient,sizeof(addrClient));//�󶨵����ص�ַ�Ͷ˿��ϡ�

	}
}

void Client::sendData(const char * buff,const int len)//��������
{
	int rslt;
	int addrLen=sizeof(sockaddr_in);
	
	if(m_Protocaltype==TCP_DATA)//TCP����
	{
		rslt=send(m_socket,buff,len,0);
	}
	else if(m_Protocaltype==UDP_DATA)//UDP����
	{
		rslt=sendto(m_socket,buff,len,0,(sockaddr*)&serverAddr,addrLen);
	}
	if (rslt<=0)
	{
		cout<<"����ʧ�ܣ�"<<endl;
	}
	assert(rslt>0);
	
}


long Client::getData(char * buff,const int len)
{
	int rslt;
	int addrLen=sizeof(sockaddr_in);
	memset(buff,0,len);
	if(m_Protocaltype==TCP_DATA)//TCP����
	{
		rslt=recv(m_socket,buff,len,0);
	}
	else if(m_Protocaltype==UDP_DATA)//UDP����
	{
		rslt=recvfrom(m_socket,buff,len,0,(sockaddr*)&serverAddr,&addrLen);
	}
	else
	{
		abort();
	}
	if (rslt<=0)
	{
		cout<<"����ʧ�ܣ�"<<endl;
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
	m_Protocaltype = UDP_DATA;//Ĭ��ΪUDP
	int rslt=WSAStartup(WINSOCK_VERSION,&wsa);//����WinSock DLL
	if (rslt!=0)
	{
		cout<<"����WinSock DLLʧ��!"<<endl;
	}
	assert(rslt==0);
}
Client::~Client(void)
{
	if(m_socket!=INVALID_SOCKET)
		closesocket(m_socket);
	WSACleanup();//ж��WinSock DLL
}

void Server::init(int inet_type,char*addr,unsigned short port)
{
	int rslt;
	m_Protocaltype=inet_type;
	if(m_Protocaltype==TCP_DATA)//TCP����
		m_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//����TCP�׽���
	else if(m_Protocaltype==UDP_DATA)//UDP����
		//m_socket=socket(AF_INET,SO_BROADCAST,IPPROTO_UDP);//����UDP�׽���
	    m_socket=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);//����UDP�׽���
	if (m_socket==INVALID_SOCKET)
	{
		cout<<"�׽��ִ���ʧ�ܣ�"<<endl;
	}
	assert(m_socket!=INVALID_SOCKET);
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.S_un.S_addr=inet_addr(addr);
	serverAddr.sin_port=htons(port);
	memset(serverAddr.sin_zero,0,8);
	rslt=bind(m_socket,(sockaddr*)&serverAddr,sizeof(serverAddr));//�󶨵�ַ�Ͷ˿�
	if (rslt!=0)
	{
		cout<<"��������ʧ�ܣ�"<<endl;
	}
	assert(rslt==0);
	if(m_Protocaltype==TCP_DATA)//TCP��Ҫ����
	{
		rslt=listen(m_socket,MAX_TCP_CONNECT);//�����ͻ�������
		if (rslt!=0)
		{
			cout<<"TCP����ʧ�ܣ�"<<endl;
		}
		assert(rslt==0);
	}
}

void Server::start()
{
	int rslt;
	sockaddr_in client;//�ͻ��˵�ַ�ṹ
	int addrLen=sizeof(client);
	SOCKET clientSock;//�ͻ���socket
	char buff[MAX_BUFFER_LEN];//UDP���ݻ���
	while(true)
	{
		if(m_Protocaltype==TCP_DATA)//TCP����
		{
			clientSock=accept(m_socket,(sockaddr*)&client,&addrLen);//��������
			if(clientSock==INVALID_SOCKET)
				break;
			if (clientSock==INVALID_SOCKET)
			{
				cout<<"TCP�ͻ��˽�������ʧ�ܣ�"<<endl;
			}
			assert(clientSock!=INVALID_SOCKET);
			sockaddr_in*pc=addClient(client);//���һ���ͻ���
			connect(pc);//���Ӵ�����
			SockParam sp(clientSock,pc,this);//�����ṹ
			HANDLE thread=CreateThread(NULL,0,threadProc,(LPVOID)&sp,0,NULL);//���������߳�
			if (thread==NULL)
			{
				cout<<"���������߳�ʧ�ܣ�"<<endl;
			}
			assert(thread!=NULL);
			CloseHandle(thread);//�ر��߳�
			cout<<"TCP���ӷ������ɹ�";
		}
		else if(m_Protocaltype==UDP_DATA)//UDP����
		{
			/*memset(buff,0,MAX_BUFFER_LEN);
			rslt=recvfrom(m_socket,buff,MAX_BUFFER_LEN,0,(sockaddr*)&client,&addrLen);
			assert(rslt>0);
			char resp[MAX_BUFFER_LEN]={0};//���մ���������
			rslt=procRequest(&client,buff,rslt,resp);//��������
			rslt=sendto(m_socket,resp,rslt,0,(sockaddr*)&client,addrLen);//����udp����
			*/
		 
		}
	}
}

DWORD WINAPI threadProc(LPVOID lpParam)//TCP�̴߳�����
{
	SockParam sp=*(SockParam*)lpParam;
	Server*s=sp.pServer;
	SOCKET sock=s->m_socket;
	SOCKET clientSock=sp.rsock;
	sockaddr_in *clientAddr=sp.raddr;

	CRITICAL_SECTION*cs=s->cs;
	int rslt;
	char req[MAX_BUFFER_LEN+1]={0};//���ݻ�����,����һ���ֽڣ��������
	do
	{//��д����Ҫ�������ת����
		rslt=recv(clientSock,req,MAX_BUFFER_LEN,0);//��������
		if(rslt<=0)
			break;
		char resp[MAX_BUFFER_LEN]={0};//���մ���������
		EnterCriticalSection(cs);
		rslt=s->procRequest(clientAddr,req,rslt,resp);//����󷵻����ݵĳ���
		LeaveCriticalSection(cs);
		assert(rslt<=MAX_BUFFER_LEN);//���ᳬ��MAX_BUFFER_LEN
		//rslt=send(clientSock,resp,rslt,0);//����tcp����
		rslt=send(clientSock,req,strlen(req)+1,0);//����tcp����
	}
	while(rslt!=0||rslt!=SOCKET_ERROR);
	s->delClient(clientAddr);
	s->disConnect(clientAddr);//�Ͽ����Ӻ���
	return 0;
}

/*******************�û��Զ���**************************/
//�û��Զ�������������ܺ����������������������ӹر�

/***
	�������������Ĺ�����ʹ�������ж���,ͷ�ļ������������
***/
#include <iostream>
void Server::connect(sockaddr_in*client)
{
	cout<<"�ͻ���"<<getIP(client)<<"["<<getPort(client)<<"]"<<"���ӡ�"<<endl;
}

int Server::procRequest(sockaddr_in*client,const char* req,int reqLen,char*resp)
{
/*	cout<<getIP(client)<<"["<<getPort(client)<<"]:"<<req<<endl;
	if(m_Protocaltype==TCP_DATA)
		strcpy(resp,"TCP�ظ�");
	else if(m_Protocaltype==UDP_DATA)
		strcpy(resp,"UDP�ظ�");*/
	return 10;
}

void Server::disConnect(sockaddr_in*client)
{
	cout<<"�ͻ���"<<getIP(client)<<"["<<getPort(client)<<"]"<<"�Ͽ���"<<endl;
}

Server::Server()
{
	cs=new CRITICAL_SECTION();
	InitializeCriticalSection(cs);//��ʼ���ٽ���
	WSADATA wsa;
	int rslt=WSAStartup(WINSOCK_VERSION,&wsa);//����WinSock DLL
	if (rslt!=0)
	{
		cout<<"����WinSock DLLʧ��!"<<endl;
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
	for(list<sockaddr_in*>::iterator i=clientAddrs.begin();i!=clientAddrs.end();++i)//��տͻ��˵�ַ�ṹ
	{
		delete *i;
	}//����ɾ����û�����⣡������
	clientAddrs.clear();
	if(m_socket!=INVALID_SOCKET)
	closesocket(m_socket);//�رշ�����socket
	WSACleanup();//ж��WinSock DLL
	DeleteCriticalSection(cs);
	delete cs;
}




