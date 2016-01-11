#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"user.h"
#include"inode.h"
#include"dirent.h"
#include"block.h"

//创建根目录的目录文件--------------
//根目录必须先确定。。。。。。。。。
//将文件名命名为编号，以此作为磁盘块的块地址。。。。。。。。。
void initRootD()
{
	FILE * stream;
	struct dirent d[TOTAL_DIRENT];

	for (int i = 0; i < TOTAL_DIRENT; i++)
	{
		if (i == 0)
		{
			d[i].inode_num = 0; //0号inode用于存放根目录文件
			d[i].dirent_type = DIRENT_TYPE;
			strcpy(d[i].dirent_name, ".");
		}
		else if (i == 1)
		{
			d[i].inode_num = 0; //0号inode用于存放根目录文件
			d[i].dirent_type = DIRENT_TYPE;
			strcpy(d[i].dirent_name, "..");
		}
		else
		{
			d[i].inode_num = INODE_UNUSERD;
			d[i].dirent_type = UNDEFIEN;
			strcpy(d[i].dirent_name, "");
		}
	}
	stream = fopen("/0", "w"); //根目录存放在第0个块地址中
	fwrite(d, sizeof(struct dirent), TOTAL_DIRENT, stream);
	fclose(stream);
}
//创建dirent的目录项
bool createDirentD(struct dirent * allDirents, const char * name,
		unsigned short inode_num)
{
	for (int i = 2; i < TOTAL_DIRENT; i++)
	{
		if (allDirents[i].inode_num == INODE_UNUSERD)
		{
			allDirents[i].inode_num = inode_num;
			allDirents[i].dirent_type = DIRENT_TYPE;
			strcpy(allDirents[i].dirent_name, name);
			return true;
		}
	}
	return false;
}

//测试目录是否不包含子目录或者子文件
bool isDirentEmpty(struct dirent * allDirents, struct inode * node, int index)
{

	int i = allDirents[index].inode_num;

	int block_num = node[i].disk_add[0];
	char block_file[7] = "";
	struct dirent dirent_c[TOTAL_DIRENT];
	sprintf(block_file, "/%d", block_num);
	FILE * stream;
	stream = fopen(block_file, "r");
	fread(dirent_c, sizeof(struct dirent), TOTAL_DIRENT, stream);
	fclose(stream);
	for (int i = 2; i < TOTAL_DIRENT; i++)
	{
		if (dirent_c[i].inode_num != INODE_UNUSERD)
		{
			return false;
		}
	}
	return true;
}

bool creatFileD(struct dirent * allDirents, const char * name,
		unsigned short inode_num)
{
	for (int i = 2; i < TOTAL_DIRENT; i++)
	{
		if (allDirents[i].inode_num == INODE_UNUSERD)
		{
			allDirents[i].inode_num = inode_num;
			allDirents[i].dirent_type = FILE_TYPE;
			strcpy(allDirents[i].dirent_name, name);
			return true;
		}
	}
	return false;
}

//删除目录项的时候使用，同时返回目录项所指向的i节点序号
unsigned short deleteDir(struct dirent * allDirents, int index)
{
	if (allDirents != NULL && index != DIRENT_UNDEFIEN)
	{
		unsigned short inode_num = allDirents[index].inode_num;
		allDirents[index].inode_num = INODE_UNUSERD;
		allDirents[index].dirent_type = UNDEFIEN;
		strcpy(allDirents[index].dirent_name, "");
		return inode_num;
	}
	return INODE_UNUSERD;
}

void listDirent(struct dirent * allDirents, struct inode * allInodes,
		struct user * nowUser)
{
	printf("目录名称\ti节点序号\t用户的id\t文件大小\t文件类型\t连接数\t保护类型\t磁盘块号\t创建时间\n");
	for (int i = 0; i < TOTAL_DIRENT; i++)
	{
		if (allDirents[i].inode_num != INODE_UNUSERD)
		{
			//i<2是因为前面定义到时候前一二项目录是自己和上一级目录的目录项
//			if(i<2||allInodes[allDirents[i].inode_num].user_id==nowUser->user_id||nowUser->user_id==SUPERUSER)
//			{
			printf("%s\t", allDirents[i].dirent_name);
			printf("%d\t", allDirents[i].inode_num);
			printf("%d\t", allInodes[allDirents[i].inode_num].user_id);
			printf("%ld\t", allInodes[allDirents[i].inode_num].file_size);
			if (allInodes[allDirents[i].inode_num].file_type == 1)
				printf("%s\t", "文件夹");
			else
				printf("%s\t", "文本文件");
//				printf(" %d\t",allInodes[allDirents[i].inode_num].file_type);
			printf(" %d\t", allInodes[allDirents[i].inode_num].link_num);
//				printf(" %hu\n",allInodes[allDirents[i].inode_num].protection);
			if (allInodes[allDirents[i].inode_num].protection == 1)
				printf("%s\t", "只写");
			else if (allInodes[allDirents[i].inode_num].protection == 2)
				printf("%s\t", "只读");
			else
				printf("%s\t", "可读可写");
			printf("%hu\t", allInodes[allDirents[i].inode_num].disk_add[0]);
			printf("%s",
					ctime(&allInodes[allDirents[i].inode_num].create_time));
//			}
		}
	}
}

bool openRoot(struct dirent * d)
{
	FILE * stream;
	stream = fopen("/0", "r");
	fread(d, sizeof(struct dirent), TOTAL_DIRENT, stream);
	fclose(stream);
	if (d != NULL)
		return true;
	else
		return false;
}

//已废弃接口，修改的请参考saveDir
void saveRoot(struct dirent * d)
{
	FILE * stream;
	stream = fopen("/0", "w");
	fwrite(d, sizeof(struct dirent), TOTAL_DIRENT, stream);
	fclose(stream);
}

void readFile(struct dirent * allDirents, struct inode * node, int index)
{
	if (allDirents != NULL && node != NULL)
	{
		if (node[allDirents[index].inode_num].file_type != FILE_TYPE)
		{
			printf("该文件不是文件类型\n");
			return;
		}
		for (int i = 0; i < INODE_TO_BLOCK; i++)
		{
			if (node[allDirents[index].inode_num].protection == WRITE_ONLY)
			{
				printf("该文件是只写文件类型，不允许读取\n");
				return;
			}

			time_t accessTime;
			time(&accessTime);
			node[allDirents[index].inode_num].access_time = accessTime;

			int dis_add = node[allDirents[index].inode_num].disk_add[i];
			char block_file[7] = "";
			char content[FILE_BLOCK_MAX_LENGTH + 1] = "";
			if (dis_add == BLOCK_UNUSED)
			{
				printf("\n");
				return;
			}
			FILE * stream;
			sprintf(block_file, "/%d", dis_add);
			stream = fopen(block_file, "r");
			fread(content, sizeof(char), FILE_BLOCK_MAX_LENGTH, stream);
			fclose(stream);
			printf("%s", content);
		}
		printf("\n"); //输出格式调整
	}
}

bool openDir(struct dirent * allDirents, struct inode * node, int index)
{
	if (allDirents != NULL)
	{
		int i = allDirents[index].inode_num;
		if (i != INODE_UNUSERD)
		{
			int block_num = node[i].disk_add[0];
			char block_file[7] = "";
			sprintf(block_file, "/%d", block_num);
			FILE * stream;
			stream = fopen(block_file, "r");
			fread(allDirents, sizeof(struct dirent), TOTAL_DIRENT, stream);
			fclose(stream);
			return true;
		}
	}
	return false;
}

//用来保存新创建或者修改到目录项
void saveDir(struct dirent * allDirents, struct inode * allInodes)
{
	FILE * stream;
	char block_file[7] = "";
	unsigned short block_num = allInodes[allDirents[0].inode_num].disk_add[0];
	sprintf(block_file, "/%d", block_num);
	stream = fopen(block_file, "w");
	fwrite(allDirents, sizeof(struct dirent), TOTAL_DIRENT, stream);
	fclose(stream);
}

bool closeDir(struct dirent * allDirents, int index, struct inode * node)
{
	if (allDirents != NULL)
	{
		int i = allDirents[index].inode_num;
		if (i != INODE_UNUSERD)
		{
//			int block_num=node[i].disk_add[0];
//			char * block_file;
//			sprintf(block_file,"/dir_%d",block_num);
//			FILE * stream;
//			struct dirent d[TOTAL_DIRENT];
//			stream=fopen(block_file,"W");

		}
	}
	return true;
}

void createChildF(unsigned short * disk_add, char * file_content)
{
	for (int i = 0; i < INODE_TO_BLOCK; i++)
	{
		if (disk_add[i] != BLOCK_UNUSED)
		{
			char p = file_content[0];
			char division[FILE_BLOCK_MAX_LENGTH];

			FILE * stream;
			char block_file[7] = "";
			sprintf(block_file, "/%d", disk_add[i]);
			stream = fopen(block_file, "w");
			for (int j = 0; j < FILE_BLOCK_MAX_LENGTH; j++)
			{
				division[j] = file_content[j + i * FILE_BLOCK_MAX_LENGTH];
				p = file_content[j + i * FILE_BLOCK_MAX_LENGTH];
				if (p == '\0')
				{
					for (; j < FILE_BLOCK_MAX_LENGTH; j++)
					{
						division[j] = '\0';
						break;
					}

				}
			}
			fwrite(division, sizeof(char), FILE_BLOCK_MAX_LENGTH, stream);
			fclose(stream);
		}
	}
}

//inode确定后和磁盘块确定后才能调用到函数
void createChildD(unsigned short father_inode_num,
		unsigned short child_inode_num, unsigned short * disk_add)
{
	FILE * stream;
	struct dirent d[TOTAL_DIRENT];

	for (int i = 0; i < TOTAL_DIRENT; i++)
	{
		if (i == 0)
		{
			d[i].inode_num = child_inode_num; //0号inode用于存放根目录文件
			d[i].dirent_type = DIRENT_TYPE;
			strcpy(d[i].dirent_name, ".");
		}
		else if (i == 1)
		{
			d[i].inode_num = father_inode_num; //0号inode用于存放根目录文件
			d[i].dirent_type = DIRENT_TYPE;
			strcpy(d[i].dirent_name, "..");
		}
		else
		{
			d[i].inode_num = INODE_UNUSERD;
			d[i].dirent_type = UNDEFIEN;
			strcpy(d[i].dirent_name, "");
		}
	}
	char block_file[7] = "";
	sprintf(block_file, "/%d", disk_add[0]);
	stream = fopen(block_file, "w"); //根目录存放在第0个块地址中
	fwrite(d, sizeof(struct dirent), TOTAL_DIRENT, stream);
	fclose(stream);

}

int checkDir(struct dirent * allDirents, const char * name)
{
	for (int i = 0; i < TOTAL_DIRENT; i++)
	{
		if (allDirents[i].inode_num != INODE_UNUSERD)
		{
			if (strcmp(allDirents[i].dirent_name, name) == 0)
				return i;
		}
	}
	return DIRENT_UNDEFIEN;
}

