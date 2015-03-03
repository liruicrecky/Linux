/*************************************************************************
	> File Name: ./include/ftp.h
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 28 Feb 2015 08:28:29 PM CST

 ************************************************************************/

#ifndef __FTP_H__
#define __FTP_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/epoll.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<dirent.h>
#include<sys/mman.h>
#include<signal.h>
#include<sys/stat.h>

#define FREE 1
#define BUSY 0

typedef struct _CHILD
{
	int socketFd;
	pid_t childPid;
	int stat;
	int alreadyDone;
}CHILD, *pCHILD;

typedef struct _MSG
{
	int msgLen;
	char buf[1024];
}MSG, *pMSG;

void makeChild(pCHILD pChi, int numChi);
void sendFd(int sockFd, int fd);
void recvFd(int sockFd, int *fd);
void handleRequest(int sockFd);

//command

void judgeCommand(char *comm, char *para, int sockFd);
void serverLs(int clientFd);
void serverPwd(int clientFd);
void serverCd(int clientFd, char *para);
void serverGetFiles(int clientFd, char *para);
void serverPutFiles(int clientFd, char *para);
void serverRemove(int clientFd, char *para);
void clientSoenLoadFile(int clientSocket, char *buf, int flag);
void recvFork(int signum);

//file

unsigned long getFileSize(char *path);
unsigned long fsendBuf(int socket, char *buf, int len);
unsigned long frecvBuf(int socket, char *buf, int len);
void delSpace(char *str);
int getWordNum(char *str);
int isDir(char *path);

#endif

