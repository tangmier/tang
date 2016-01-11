#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"block.h"
#include"inode.h"

void initBlock()
{
	FILE * stream;
	unsigned short block[TOTAL_BLOCK];

	block[0] = 0; //根目录所在的块的号码

	for (int i = 1; i < TOTAL_BLOCK; i++)
	{
		block[i] = BLOCK_UNUSED;
	}
	stream = fopen("/blockProfile", "w");
	fwrite(block, sizeof(int), TOTAL_BLOCK, stream);
	fclose(stream);
}

bool openBlock(unsigned short * block)
{
	FILE * stream;
	stream = fopen("/blockProfile", "r");
	fread(block, sizeof(unsigned short), TOTAL_BLOCK, stream);
	fclose(stream);
	if (block != NULL)
		return true;
	else
		return false;
}

void saveBlock(unsigned short * block)
{
	FILE * stream;
	stream = fopen("/blockProfile", "w");
	fwrite(block, sizeof(int), TOTAL_BLOCK, stream);
	fclose(stream);
}

bool applyBlocks(unsigned short * b, unsigned short * block, int num)
{
	int j = 0;
	for (int i = 1; i < TOTAL_BLOCK; i++)
	{
		if (block[i] == BLOCK_UNUSED)
		{
			block[i] = i;
			b[j] = block[i];
			j++;
			if (j == num)
				return true;
		}
	}
	return false;
}

bool retrieveBlocks(unsigned short * b, unsigned short * block)
{
	if (b != NULL && block != NULL)
	{
		for (int i = 0; i < INODE_TO_BLOCK; i++)
		{
			if (b[i] == BLOCK_UNUSED)
				break;
			block[b[i]] = BLOCK_UNUSED;
		}
		return true;
	}
	return false;
}

bool deleteBlock(unsigned short * b)
{
	if (b != NULL)
	{
		for (int i = 0; i < INODE_TO_BLOCK; i++)
		{
			if (b[i] == BLOCK_UNUSED)
				break;
			char block_file[7] = "";
			sprintf(block_file, "/%d", b[i]);
			remove(block_file);
		}
		return true;
	}
	return false;

}
