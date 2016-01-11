#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"user.h"

int checkUser(struct user * allUsers, const char * name)
{
	for (int i = 0; i < TOTAL_USER; i++)
	{
		if (allUsers[i].user_id != USER_UNDEFINE) //id是用户存放到数组到下标，下标等于32表示该位置未存放用户
		{
			if (strcmp(allUsers[i].user_name, name) == 0)
				return allUsers[i].user_id;
		}
	}
	return USER_UNDEFINE;
}

struct user * login(struct user * allUsers, const char * name,
		const char * password)
{

	for (int i = 0; i < TOTAL_USER; i++)
	{
		if (allUsers[i].user_id != USER_UNDEFINE)
		{
			if (strcmp(allUsers[i].user_name, name) == 0)
				if (strcmp(allUsers[i].user_password, password) == 0)
					return &allUsers[i];
		}
	}
	return NULL;
}

bool createUser(struct user * allUsers, const char * name,
		const char * password)
{
	for (int i = 0; i < TOTAL_USER; i++)
	{
		if (allUsers[i].user_id == USER_UNDEFINE)
		{
			allUsers[i].user_id = i;
			strcpy(allUsers[i].user_name, name);
			strcpy(allUsers[i].user_password, password);
			return true;
		}
	}
	return false;
}

//用户只能删除自身到用户
bool deleteUser(struct user * allUsers, struct user * u)
{
	for (int i = 0; i < TOTAL_USER; i++)
	{
		if (allUsers[i].user_id == u->user_id)
		{
			allUsers[i].user_id = USER_UNDEFINE;
			strcpy(allUsers[i].user_name, "");
			strcpy(allUsers[i].user_password, "");
			return true;
		}
	}
	return false;
}

void initUser()
{
	FILE * stream;
	struct user u[TOTAL_USER];

	//0为超级管理员
	u[SUPERUSER].user_id = SUPERUSER;
	strcpy(u[SUPERUSER].user_name, "root");
	strcpy(u[SUPERUSER].user_password, "root");

	for (int i = 1; i < TOTAL_USER; i++)
	{
		u[i].user_id = USER_UNDEFINE;
		strcpy(u[i].user_name, "");
		strcpy(u[i].user_password, "");
	}

	stream = fopen("/userProfile", "w");
	fwrite(u, sizeof(struct user), TOTAL_USER, stream);
	fclose(stream);
}

bool openUser(struct user * u)
{
	FILE * stream;
	stream = fopen("/userProfile", "r");
	fread(u, sizeof(struct user), TOTAL_USER, stream);
	fclose(stream);
	if (u != NULL)
		return true;
	else
		return false;
}

void saveUser(struct user * u)
{
	FILE * stream;
	stream = fopen("/userProfile", "w");
	fwrite(u, sizeof(struct user), TOTAL_USER, stream);
	fclose(stream);
}

void listUser(struct user * u)
{
	for (int i = 0; i < TOTAL_USER; i++)
	{
		if (u[i].user_id != USER_UNDEFINE)
		{
			printf("id %d\t", u[i].user_id);
			printf("name %s\t", u[i].user_name);
			printf("password %s\n", u[i].user_password);
		}
	}
}

