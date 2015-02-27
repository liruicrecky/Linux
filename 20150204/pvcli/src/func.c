/*************************************************************************
	> File Name: ./src/func.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Wed 04 Feb 2015 04:07:21 PM CST
 ************************************************************************/

#include"client.h"

void V(int sem_id)
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = 1;
	buf.sem_flg = SEM_UNDO;
	semop(sem_id, &buf, 1);
}

void P(int sem_id)
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = -1;
	buf.sem_flg = SEM_UNDO;
	semop(sem_id, &buf, 1);
}

