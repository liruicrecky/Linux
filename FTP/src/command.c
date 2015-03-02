/*************************************************************************
	> File Name: ./src/command.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Mon 02 Mar 2015 10:28:17 AM CST
 ************************************************************************/

#include"ftp.h"

void judgeCommand(char *comm, char *para, int sockFd)
{
	if(strcmp(comm, "ls") == 0)
	{
		serverLs(sockFd);
	}
	else if(strcmp(comm, "pwd") == 0)
	{
		serverPwd(sockFd);
	}
	else if(strcmp(comm, "cd") == 0)
	{
		serverCd(sockFd, para);
	}
	else if(strcmp(comm, "gets") == 0)
	{
		serverGetFiles(sockFd, para);
	}
	else if(strcmp(comm, "puts") == 0)
	{
		serverPutFiles(sockFd, para);
	}
	else if(strcmp(comm, "remove") == 0)
	{
		serverRemove(sockFd, para);
	}

}

void recvFork(int signum)
{
	wait(NULL);
}
