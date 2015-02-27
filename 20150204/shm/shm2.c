/*************************************************************************
	> File Name: shm.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Wed 04 Feb 2015 10:02:01 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int main(int argc, char *argv[])
{
	key_t my_ftok;
	int my_shmget;
	char *str;


	my_ftok = ftok("./mem.c", 123);

	my_shmget = shmget(my_ftok, 1024, IPC_CREAT|0660);

	if(my_shmget == -1){
		perror("shmget error");
		exit(1);
	}

	str = (char *)shmat(my_shmget, NULL, 0);


	printf("%s\n", str);
	sleep(3);
	strcpy(str, "fine thankyou");

	return 0;
}
