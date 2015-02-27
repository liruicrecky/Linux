/*************************************************************************
	> File Name: ./src/file.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Fri 13 Feb 2015 01:30:37 PM CST
 ************************************************************************/

#include"tcp.h"

unsigned long getFileSize(char *path)
{
	struct stat fbFile;
	unsigned long fileSize;

	if(stat(path, &fbFile) == -1)
	{
		perror("getFileStat");
		exit(1);
	}

	fileSize = fbFile.st_size;

	return fileSize;
}

