/*************************************************************************
	> File Name: ./include/process.h
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 28 Feb 2015 02:49:35 PM CST
 ************************************************************************/

#ifndef __PROCESS_H__
#define __PROCESS_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>

void sendFd(int socketFd, int fd);
void recvFd(int socketFd, int *fd);

#endif
