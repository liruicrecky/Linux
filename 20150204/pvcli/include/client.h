/*************************************************************************
	> File Name: ./include/client.h
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Wed 04 Feb 2015 03:46:15 PM CST
 ************************************************************************/

#ifndef __CLIENT_H__
#define __CLIENT_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>

typedef struct _Client_Msg
{
	int c_flag;
	char c_msgbuf[1024];

}CLIM, *pCLIM;

void P(int sem_id);
void V(int sem_id);

#endif
