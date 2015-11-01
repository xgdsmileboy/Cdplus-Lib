#pragma once
/********************��������Ԥ����***************************/

//WinSock�����ͷ�ļ��Ϳ�
#include <WinSock2.h>
#include <iostream>
#pragma comment(lib,"ws2_32.lib")
//����ͷ�ļ�
#include <assert.h>

//������������
#define TCP_DATA 1
#define UDP_DATA 2

//TCP��������
#define MAX_TCP_CONNECT 10

//����������
#define MAX_BUFFER_LEN 1000

/*******************�ͻ���*************************/
//�ͻ�����
class Client
{
private:
	int m_Protocaltype;//ͨ��Э������
	SOCKET m_socket;//�����׽���
	sockaddr_in serverAddr;//��������ַ�ṹ

public:
	Client();
	void init(int inet_type,char*addr,unsigned short port);//��ʼ��ͨ��Э�飬��ַ���˿�
	char*getProto();//��ȡͨ��Э������
	char*getIP();//��ȡIP��ַ
	unsigned short getPort();//��ȡ�˿�
	void sendData(const char * buff,const int len);//��������
	long getData(char * buff,const int len);//��������
	int getProtocaltype(){return m_Protocaltype;}
	virtual ~Client(void);
};

/*********************������********************/
//��������

#include <list>
using namespace std;

class Server
{
	CRITICAL_SECTION *cs;//�ٽ�������
	int m_Protocaltype;//��¼���ݰ�����
	sockaddr_in serverAddr;//��������ַ
	list<sockaddr_in*> clientAddrs;//�ͻ��˵�ַ�ṹ�б�
	sockaddr_in* addClient(sockaddr_in client);//��ӿͻ��˵�ַ�ṹ
	void delClient(sockaddr_in *client);//ɾ���ͻ��˵�ַ�ṹ
	friend DWORD WINAPI threadProc(LPVOID lpParam);//�̴߳�������Ϊ��Ԫ����
	 SOCKET m_socket;//����socket
public:
	Server();
	void init(int inet_type,char*addr,unsigned short port);
	void start();//����������
	char* getProto();//��ȡЭ������
	char* getIP(sockaddr_in*serverAddr=NULL);//��ȡIP
	unsigned short getPort(sockaddr_in*serverAddr=NULL);//��ȡ�˿�
	virtual void connect(sockaddr_in*client);//����ʱ����
	virtual int procRequest(sockaddr_in*client,const char* req,int reqLen,char*resp);//����ͻ�������
	virtual void disConnect(sockaddr_in*client);//�Ͽ�ʱ����
	virtual ~Server(void);
};

//�������̴߳����������ṹ

struct SockParam
{
	SOCKET rsock;//Զ�̵�socket
	sockaddr_in *raddr;//Զ�̵�ַ�ṹ
	Server*pServer;//����������ָ��
	SockParam(SOCKET rs,sockaddr_in*ra,Server*ps)
	{
		rsock=rs;
		raddr=ra;
		pServer=ps;
	}
};


