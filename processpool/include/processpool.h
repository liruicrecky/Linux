/*************************************************************************
	> File Name: ./include/processpool.h
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 28 Feb 2015 08:28:29 PM CST

 ************************************************************************/

#ifndef __PROCESS_H__
#define __PROCESS_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define FREE 1
#define BUSY 0

typedef struct _CHILD
{
	int socketFd;
	pid_t childPid;
	int stat;
	int alreadyDone;
}CHILD, *pCHILD;

void makeChild(pCHILD pChi, int numChi);
void sendFd(int sockFd, int fd);
void recvFd(int sockFd, int *fd);
void handleRequest(int sockFd);
unsigned long fsendBuf(int socket, char *buf, int len);
unsigned long frecvBuf(int socket, char *buf, int len);

#endif

