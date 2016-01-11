#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>
#include"inode.h"
#include"user.h"
#include"block.h"
#include"dirent.h"

void initInode()
{
	FILE * stream;
	struct inode node[TOTAL_INODE];

	//第0个i节点指向到磁盘地址块到编号就是根目录
	time_t creatTime;
	time(&creatTime);

	node[0].file_size = sizeof(struct dirent) * TOTAL_DIRENT;
	node[0].user_id = SUPERUSER; //设置0为超级用户
	node[0].create_time = creatTime;
	for (int i = 0; i < INODE_TO_BLOCK; i++)
	{
		if (i == 0)
			node[i].disk_add[i] = 0;
		else
			node[i].disk_add[i] = BLOCK_UNUSED;
	}

	node[0].file_type = DIRENT_TYPE;
	node[0].protection = WRITE_AND_READ;
	node[0].link_num = 1;

	for (int i = 1; i < TOTAL_INODE; i++)
	{
		node[i].file_type = UNDEFIEN;
		node[i].protection = UNDEFIEN;
		node[i].link_num = UNDEFIEN;
		node[i].user_id = USER_UNDEFINE;
		node[i].file_size = UNDEFIEN;
		for (int j = 0; j < INODE_TO_BLOCK; j++)
		{
			node[i].disk_add[j] = BLOCK_UNUSED;
		}
	}

	stream = fopen("/inodeProfile", "w");
	fwrite(node, sizeof(struct inode), TOTAL_INODE, stream);
	fclose(stream);
}

bool openInode(struct inode * node)
{
	FILE * stream;
	stream = fopen("/inodeProfile", "r");
	fread(node, sizeof(struct inode), TOTAL_INODE, stream);
	fclose(stream);
	if (node != NULL)
		return true;
	else
		return false;
}
//通过i节点的序号删除要删除的文件的i节点的信息，同时通过block参数获取到所涉及到到磁盘块的序号
bool deleteInode(struct inode * node, unsigned short * block,
		unsigned short index)
{
	if (node != NULL && block != NULL)
	{
		node[index].file_type = UNDEFIEN;
		node[index].protection = UNDEFIEN;
		node[index].link_num = UNDEFIEN;
		node[index].user_id = USER_UNDEFINE;
		node[index].file_size = UNDEFIEN;
		for (int j = 0; j < INODE_TO_BLOCK; j++)
		{
			block[j] = node[index].disk_add[j];
			node[index].disk_add[j] = BLOCK_UNUSED;
		}
		return true;
	}
	return false;
}

//创建file到inode
//size文本的长度
unsigned short createFileI(struct inode * node, unsigned short * block,
		struct user * u, unsigned long size, unsigned short protection)
{
	if (node != NULL)
	{
		for (unsigned short i = 1; i < TOTAL_INODE; i++)
		{
			if (node[i].file_type == UNDEFIEN)
			{
				int num = 0;
				if (size % FILE_BLOCK_MAX_LENGTH == 0)
					num = size / FILE_BLOCK_MAX_LENGTH;
				else
					num = size / FILE_BLOCK_MAX_LENGTH + 1;
				if (!applyBlocks(node[i].disk_add, block, num))
				{
					return INODE_UNUSERD; //申请块失败
				}
				time_t createTime;
				time(&createTime);
				node[i].file_type = FILE_TYPE;
				node[i].create_time = createTime;
				node[i].modification_time = createTime;
				node[i].access_time = createTime;
				node[i].link_num = 1;
				node[i].file_size = size;
				node[i].protection = protection;
				node[i].user_id = u->user_id;
				return i; //获取inode的序号
			}
		}
	}
	return INODE_UNUSERD;
}

//创建dirent的inode
unsigned short createDirentI(struct inode * node, unsigned short * block,
		struct user * u)
{
	if (node != NULL)
	{
		for (unsigned short i = 1; i < TOTAL_INODE; i++)
		{
			if (node[i].file_type == UNDEFIEN)
			{
				time_t createTime;
				time(&createTime);
				if (!applyBlocks(node[i].disk_add, block, 1))
				{
					return INODE_UNUSERD; //申请块失败
				}
				node[i].file_type = DIRENT_TYPE;
				node[i].create_time = createTime;
				node[i].link_num = 1;
				node[i].file_size = sizeof(struct dirent) * TOTAL_DIRENT;
				node[i].protection = WRITE_AND_READ;
				node[i].user_id = u->user_id;
				return i; //获取inode的序号
			}
		}
	}
	return INODE_UNUSERD;
}

void saveInode(struct inode * node)
{
	FILE * stream;
	stream = fopen("/inodeProfile", "w");
	fwrite(node, sizeof(struct inode), TOTAL_INODE, stream);
	fclose(stream);
}

void listInode(struct inode * node)
{
	for (int i = 0; i < TOTAL_INODE; i++)
	{
		if (node[i].user_id != USER_UNDEFINE)
		{
			printf("id %d\t", node[i].user_id);
			printf("file_type %d\t", node[i].file_type);
			printf("file_size %ld\n", node[i].file_size);
		}
	}
}

struct inode * getInode(struct inode * allInodes, int index)
{

	if (allInodes != NULL)
		return &allInodes[index];
	else
		return NULL;
}

bool setProtection(struct inode * i, unsigned short p)
{
	if (i != NULL)
	{
		switch (p)
		{
		case 1:
			i->protection = WRITE_ONLY;
			break;
		case 2:
			i->protection = READ_ONLY;
			break;
		case 3:
			i->protection = WRITE_AND_READ;
			break;
		default:
			return false;
		}
		return true;
	}
	return false;
}

bool setCreateTime(struct inode * i, time_t time)
{
	if (i != NULL)
	{
		i->create_time = time;
		return true;
	}
	return false;
}

bool setAccessTime(struct inode * i, time_t time)
{
	if (i != NULL)
	{
		i->access_time = time;
		return true;
	}
	return false;
}

bool setModificationTime(struct inode * i, time_t time)
{
	if (i != NULL)
	{
		i->modification_time = time;
		return true;
	}
	return false;
}

