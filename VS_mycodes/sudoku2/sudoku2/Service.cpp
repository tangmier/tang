#include "Service.h"
#include "Config.h"
#include "UserAction.h"
#include "PacketWrapper.h"
#include <string>
#include <iostream>
//#include "MyWebService\WebService.h"
using namespace std;

void Service::start_service()
{
	WSADATA wsaD;
	WSAStartup(MAKEWORD(1, 1), &wsaD);  //�����׽��ֿ�
	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  //�����׽���
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	memset(&(server_addr.sin_zero),0, 8);
	bind(server_socket, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));  //���׽��ֵ��ض�IP�Ͷ˿�
	listen(server_socket, 5);  //���׽�������Ϊ����ģʽ�ȴ���������

	DBO *db = new DBO();  //�½�һ�����ݿ����Ӵ����û���¼
	db -> ini();

	//WebService code begin
	HANDLE WebHandle = CreateThread(NULL, 0, start_WebService, 0 , 0, NULL); 
	CloseHandle(WebHandle);
	//WebService code end


	while (true)
	{
		sockaddr_in client_addr;
		int client_addr_len = sizeof(client_addr);
		int client_fd = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);  //���������󣬽����������󣬷���һ����Ӧ�ڴ˴����ӵ��׽���
		if (client_fd < 0)
		{
			perror("accept error");
		}
		cout << "now accept a user request from:" << client_fd << endl;
		

		/* ���ܵ�¼���� */
		char *buf = new char[500];
		int ret = recv(client_fd, buf, sizeof(buf)+1, 0);  
		if (ret <= 0)
		{
			cout << "Socket connection close unexpectedly!" << endl;
			break;
		}
		cout << "Now get pacakage:" << buf << endl;
		char *sbuf = NULL;
		string id(strtok_s(buf, DELIMITER, &sbuf));
		string pwd(strtok_s(NULL, DELIMITER, &sbuf));

		if (UserAction::login(id, pwd, *db) == OPERATION_SUCCESS)
		{
			cout << "user " << id << " logon successfully!" << endl;
			string s=OPERATION_SUCCESS;
			s+="$";
			PacketWrapper::send_packet(s, client_fd);
			HANDLE handle = CreateThread(NULL, 0, process_user_request, (LPVOID)client_fd, 0, NULL);  //�����߳�,�������û�����
			CloseHandle(handle);
		}
		else
		{
			string s=WRONG_ID_OR_PWD;
			s+="$";
			PacketWrapper::send_packet(s, client_fd);
		}
	}
	closesocket(server_socket);
}

DWORD WINAPI  process_user_request(LPVOID arg)
{
	int client_fd = (int)arg;
	cout << "new thread to process user " << client_fd  << endl;

	
	//KeepAliveʵ��
	TCP_KEEPALIVE1 inKeepAlive = { 0 }; //�������
	unsigned long ulInLen = sizeof(TCP_KEEPALIVE1);

	TCP_KEEPALIVE1 outKeepAlive = { 0 }; //�������
	unsigned long ulOutLen = sizeof(TCP_KEEPALIVE1);

	unsigned long ulBytesReturn = 100;

	//����socket��keep aliveΪ5�룬���ҷ��ʹ���Ϊ3��
	inKeepAlive.onoff = 1;
	inKeepAlive.keepaliveinterval = 5000; //����KeepAlive̽����ʱ����
	inKeepAlive.keepalivetime = 5000; //��ʼ�״�KeepAlive̽��ǰ��TCP�ձ�ʱ��

	if (WSAIoctl(client_fd, SIO_KEEPALIVE_VALS,
		(LPVOID)&inKeepAlive, ulInLen,
		(LPVOID)&outKeepAlive, ulOutLen,
		&ulBytesReturn, NULL, NULL) == SOCKET_ERROR)
	{
		cout<<"WSAIoctl failed.Error code:" << WSAGetLastError() << endl; //just test
	}
	
	while (true)  //ѭ�������û�����
	{
		char *buf = new char[500];
		int ret = recv(client_fd, buf, sizeof(buf)+1, 0);
		if (ret <= 0)
		{
			cout << "Socket connection close unexpectedly!" <<endl;
			break;
		}
		string s=buf;

		if(s!="")
		{
		cout << "Now get pacakage:" << buf << endl;

		if (UserAction::start_service(client_fd, buf))  //�����û���½���������
		{
			break;  //�û��˳�ʱ����ѭ����ֹ�߳�
		}
		}
		else{
			cout<<"\n��buf"<<endl;
		}
	}
	cout << "now exit thread processing " << client_fd << endl;
	return 0;
}


DWORD WINAPI start_WebService(LPVOID arg)
{
	system("WebService.exe");
	return 0;
}