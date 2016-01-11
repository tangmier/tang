#include <string>
#include <vector>
//#include <winsock.h>
#include <WinSock2.h>
#include "mysql.h"
#pragma comment(lib,"libmysql.lib") 
using namespace std;
class DBO
{
	private:
		MYSQL *connection;
	public:
		DBO();
		bool ini();
		bool executeSQL(string str);
		bool executeTranscation(vector<string> str_list);
		bool user_login(const string &uid, string &pwd);
		bool update_user_online_state(const string &uid, const int &state);
		bool insert_new_score(const string &uid, const int &score);
		bool check_ranks(string &rank);
};