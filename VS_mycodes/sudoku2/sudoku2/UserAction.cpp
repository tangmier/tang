#include "UserAction.h"
#include "Config.h"
#include "stdlib.h"
#include "soapH.h"
#include "ServerBPortBinding.nsmap"
#include <iostream>
#include "PacketWrapper.h"
bool UserAction::start_service(int client_fd, char *buf)
{
	bool terminate = false;
	DBO *db = new DBO();
	db -> ini();
	char *sbuf = NULL;
	switch (atoi(strtok_s(buf, DELIMITER, &sbuf)))
	{
		case LOG_OFF:
		{
			string id(strtok_s(NULL, DELIMITER, &sbuf));
			cout << "now user " << id << " log off!" << endl;
			logoff(id, *db);
			terminate = true;
			break;
		}
		case INSERT_NEW_SCORE_AND_CHECK_RANKS:
		{
			cout << "now insert new score and check rank" << endl;

			//insert new score
			string uid(strtok_s(NULL, DELIMITER, &sbuf));
			int score = atoi(strtok_s(NULL, DELIMITER, &sbuf));
			if (insert_new_score(uid, score, *db) == OPERATION_SUCCESS)
			{
				string rank;
			    //check_rank
			    check_rank(rank, *db);
				rank+="$";

				PacketWrapper::send_packet(rank, client_fd);

			}
			
			break;
		}
		default:
		{
			cout<<"读取了空的请求符！"<<endl;
			break;
		}

	}

	return terminate;
}

string UserAction::login(const string &id, const string &pwd, DBO &db)
{
	string true_pwd;
	if (db.user_login(id, true_pwd))
	{
		if (pwd == true_pwd)
		{
			if (db.update_user_online_state(id, 1))
			{
				return OPERATION_SUCCESS;
			}
		}
		else
		{
			return WRONG_ID_OR_PWD;
		}
		
	}
	return OPERATION_FAILURE;
}

string UserAction::logoff(const string &id, DBO &db)
{
	if (db.update_user_online_state(id, 0))
	{
		return OPERATION_SUCCESS;
	}
	return OPERATION_FAILURE;
}

string UserAction::check_rank(string &rank, DBO &db)
{
	soap *soap_client = soap_new();  //初始化访问服务客户端
	soap_init(soap_client);
	ns1__checkRankService *check_rank_service = new ns1__checkRankService();
	check_rank_service->arg0 = "from cqw";  //服务所需参数
	ns1__checkRankServiceResponse *check_rank_response = new ns1__checkRankServiceResponse();
	soap_call___ns1__checkRankService(soap_client, NULL, NULL, check_rank_service, *check_rank_response);  //访问服务
	rank = *check_rank_response->return_;  //服务返回结果
	string my_rank;
	db.check_ranks(my_rank);
	rank += my_rank;
	cout << "rank:" << rank << "\tmyrank:" << my_rank;
	return OPERATION_SUCCESS;
}

string UserAction::insert_new_score(const string &uid, const int &score, DBO &db)
{
	if (db.insert_new_score(uid, score))
	{
		return OPERATION_SUCCESS;
	}
	return OPERATION_FAILURE;
}