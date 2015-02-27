/*************************************************************************
	> File Name: ../include/tcp.h
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Tue 10 Feb 2015 02:36:25 PM CST
 ************************************************************************/

#ifndef __TCP_H__
#define __TCP_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include<sys/mman.h>

int socketInit(char *ip, int port);
int acceptSocket(int sock);
int connectServer(char *ip, int port);
unsigned long fsendBuf(int sock, char *buf, unsigned long len);
unsigned long frecvBuf(int sock, char *buf, unsigned long len);

unsigned long getFileSize(char *path);
#endif
