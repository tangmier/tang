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
	WSAStartup(MAKEWORD(1, 1), &wsaD);  //加载套接字库
	SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  //创建套接字
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	memset(&(server_addr.sin_zero),0, 8);
	bind(server_socket, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));  //绑定套接字到特定IP和端口
	listen(server_socket, 5);  //将套接字设置为监听模式等待连接请求

	DBO *db = new DBO();  //新建一个数据库连接处理用户登录
	db -> ini();

	//WebService code begin
	HANDLE WebHandle = CreateThread(NULL, 0, start_WebService, 0 , 0, NULL); 
	CloseHandle(WebHandle);
	//WebService code end


	while (true)
	{
		sockaddr_in client_addr;
		int client_addr_len = sizeof(client_addr);
		int client_fd = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);  //：请求到来后，接受连接请求，返回一个对应于此次连接的套接字
		if (client_fd < 0)
		{
			perror("accept error");
		}
		cout << "now accept a user request from:" << client_fd << endl;
		

		/* 接受登录请求 */
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
			HANDLE handle = CreateThread(NULL, 0, process_user_request, (LPVOID)client_fd, 0, NULL);  //创建线程,处理单个用户请求
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

	
	//KeepAlive实现
	TCP_KEEPALIVE1 inKeepAlive = { 0 }; //输入参数
	unsigned long ulInLen = sizeof(TCP_KEEPALIVE1);

	TCP_KEEPALIVE1 outKeepAlive = { 0 }; //输出参数
	unsigned long ulOutLen = sizeof(TCP_KEEPALIVE1);

	unsigned long ulBytesReturn = 100;

	//设置socket的keep alive为5秒，并且发送次数为3次
	inKeepAlive.onoff = 1;
	inKeepAlive.keepaliveinterval = 5000; //两次KeepAlive探测间的时间间隔
	inKeepAlive.keepalivetime = 5000; //开始首次KeepAlive探测前的TCP空闭时间

	if (WSAIoctl(client_fd, SIO_KEEPALIVE_VALS,
		(LPVOID)&inKeepAlive, ulInLen,
		(LPVOID)&outKeepAlive, ulOutLen,
		&ulBytesReturn, NULL, NULL) == SOCKET_ERROR)
	{
		cout<<"WSAIoctl failed.Error code:" << WSAGetLastError() << endl; //just test
	}
	
	while (true)  //循环接收用户请求
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

		if (UserAction::start_service(client_fd, buf))  //处理用户登陆后各种请求
		{
			break;  //用户退出时跳出循环终止线程
		}
		}
		else{
			cout<<"\n空buf"<<endl;
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