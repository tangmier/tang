#include <iostream>
#include "DBO.h"
//#include "winsock.h"
using namespace std;

DBO::DBO()
{
	connection = mysql_init(NULL);
	if (!connection)
	{
		perror("mysql ini");
		exit(1);
	}
}

bool DBO::ini()
{
	connection = mysql_real_connect(connection, "127.0.0.1", "root", "wujiechu", "sudoku", 3306, NULL, 0);
	if (connection == NULL)
	{
		perror("mysql real connect");
		exit(1);
	}
	return true;
}

bool DBO::executeSQL(string str)  //不带回滚操作的sql执行
{
	if (mysql_query(connection, str.c_str()))
	{
		cout << "Error making query:" << mysql_errno(connection)<< "：" << mysql_error(connection) << endl;
		return false;
	}
	else
	{
		return true;
	}
}

bool DBO::executeTranscation(vector<string> str_list)  //带回滚操作的sql执行 有时间再写吧
{
	return true;
}

bool DBO::user_login(const string &uid, string &pwd)
{
	string str = "select pwd from user where uid = '" + uid + "';";
	int t = mysql_query(connection, str.c_str());
	if (t)
	{
		printf("Error making query: %s\n", mysql_error(connection));
		return false;
	}
	else
	{
	    MYSQL_RES *res = mysql_use_result(connection);
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row <= 0)
		{
			cout << "no such an ID" << endl;
			mysql_free_result(res);
			return false;
		}
		pwd = row[0];
		mysql_free_result(res);
	}
	return true;
}

bool DBO::update_user_online_state(const string &uid, const int &state)
{

	string str = "update user set isonline = ";
	if (state == 1)
	{
		str += "1";
	}
	else
	{
		str += "0";
	}
	str += " where uid = '";
	str += uid;
	str += "';";
	return executeSQL(str);
}


bool DBO::insert_new_score(const string &uid, const int &score)
{
	//写下插入新分数的sql什么的
	string str = "insert into data values ('";
	str += uid;
	str += "',";
	char buf[500];
	_itoa_s(score, buf, 10);
	string s(buf);
	str += s;
	str += ",now());";
	executeSQL(str);
	return true;
}

bool DBO::check_ranks(string &rank)
{
	//写下查看所有分数并且排序，用 "用户ID1#分数1$用户ID2#分数2" 这种格式保存在rank
	string str = "select `user`.uid, MAX(`data`.score) score from `user`,`data` where `user`.uid=`data`.uid GROUP BY(`user`.uid)";
	int t = mysql_query(connection, str.c_str());
	if (t)
	{
		printf("Error making query: %s\n", mysql_error(connection));
		return false;
	}
	else
	{
		MYSQL_RES *res = mysql_use_result(connection);
		MYSQL_ROW row;
		while (row = mysql_fetch_row(res)){
			rank += row[0];
			rank += '#';
			rank += row[1];
			rank = rank.append("$");
		}
		mysql_free_result(res);
	}
	return true;
}

