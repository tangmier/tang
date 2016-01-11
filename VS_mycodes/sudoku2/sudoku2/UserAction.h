#include <string>
#include "DBO.h"
using namespace std;
class UserAction  //此类成员函数参数未确定
{
	public:
		static bool start_service(int client_fd, char *buf);
		static string login(const string &id, const string &pwd, DBO &db);
	private:
		static string check_user_scores(const string &id, DBO &db);
		static string update_user_score(const string &id, const int &score, DBO &db);
		static string logoff(const string &id, DBO &db);
		static string check_rank(string &rank, DBO &db);
		static string insert_new_score(const string &uid, const int &score, DBO &db);
};