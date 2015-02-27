/*************************************************************************
	> File Name: ./include/pipser.h
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Sun 01 Feb 2015 03:35:06 PM CST
 ************************************************************************/

#ifndef __PIPSER_H__
#define __PIPSER_H__

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/select.h>
#include<sys/time.h>

#define BUF_SIZE 1024
#define PIPE_PATH "/home/liruicheng/pipe"
#define SER_PIPE_NAME "serviceInterfac.fifo"

typedef struct _ClientData{
	int                  c_pid;
	int                  c_send;
	int		      	     c_recv;
	struct _ClientData   *next;
}CLIENT, *pCLIENT;


#endif
