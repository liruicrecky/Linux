/*************************************************************************
	> File Name: pv.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Wed 04 Feb 2015 01:27:36 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

void v(int sem_id)
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = 1;
	buf.sem_flg = SEM_UNDO;
	semop(sem_id, &buf, 1);
}

void p(int sem_id)
{
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = -1;
	buf.sem_flg = SEM_UNDO;
	semop(sem_id, &buf, 1);
}


int main(int argc, char *argv[])
{
	key_t s_key = 12345;

	int my_semget;

	my_semget = semget(s_key, 1, 0660);

	printf("the value:%d\n", semctl(my_semget, 0, GETVAL));

	p(my_semget);
	v(my_semget);
	printf("now ped the value:%d\n", semctl(my_semget, 0, GETVAL));

	return 0;
}
