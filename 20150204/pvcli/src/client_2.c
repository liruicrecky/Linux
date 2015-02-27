/*************************************************************************
	> File Name: ./src/client_2.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Wed 04 Feb 2015 03:45:22 PM CST
 ************************************************************************/

#include"client.h"

int main(int argc, char *argv[])
{
	pCLIM c_p;
	key_t k_shm, k_sem;
	int c_shm, c_sem;

	k_shm = atoi(argv[1]);
	k_sem = atoi(argv[2]);

	c_shm = shmget(k_shm, sizeof(CLIM), 0660);
	c_sem = semget(c_sem, 1, 0660);

	c_p = (pCLIM)shmat(c_shm, NULL, 0);

	while(1)
	{
		while(P(c_sem), c_p -> c_flag == 0)
		{
			V(c_sem);
			sleep(1);
		}

		printf("---------------------------------------\n");
		printf("message: %s", c_p -> c_msgbuf);
		c_p -> c_flag = 0;
		V(c_sem);

		if(strcmp("quit", c_p -> c_msgbuf) == 0)
		{
			shmdt(c_p);
			exit(0);
		}

	}
	
	return 0;
}
