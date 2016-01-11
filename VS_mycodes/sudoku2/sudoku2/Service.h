#include "winsock2.h"
#include "Windows.h"
#include "stdsoap2.h"
//#include "MyWebService\check_ranks.nsmap"
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"wsock32.lib")

DWORD WINAPI process_user_request(LPVOID arg);
DWORD WINAPI start_WebService(LPVOID arg);

class Service 
{
	public:
		void start_service();
	private:
		sockaddr_in server_addr;
		int sock_fd;
};

struct TCP_KEEPALIVE1 {
	u_long onoff;
	u_long keepalivetime;
	u_long keepaliveinterval;
};