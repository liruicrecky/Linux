/*************************************************************************
	> File Name: ./include/epoll.h
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Fri 27 Feb 2015 11:09:35 AM CST
 ************************************************************************/

#ifndef __EPOLL_H__
#define __EPOLL_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<fcntl.h>

int initServerSocket(char *ip, int port);
int serverSockAccept(int serverSocket);
int clientConnectServer(char *ip, int port);
unsigned long fsendBuf(int socket, char *buf, unsigned long size);
unsigned long frecvBuf(int socket, char *buf, unsigned long size);
void setNoneBlock(int sfd);

#endif

