/*************************************************************************
	> File Name: ./src/client_1.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Wed 04 Feb 2015 03:45:03 PM CST
 ************************************************************************/

#include"client.h"
#include<sys/stat.h>
#include<fcntl.h>

#define PATH "/home/liruicheng/pipe"
#define SER_NAME "server.fifo"

int main(int argc, char *argv[])
{
	pCLIM c_p;
	key_t k_shm, k_sem;
	int c_shm, c_sem;
	char buf[1024];

	//create pipe and connect serpipe
	int ser_pipe, fp_clirpipe, fp_cliwpipe;
	char ser_path[128];
	char cli_rpath[128];
	char cli_wpath[128];
	char ser_msg[32];

	memset(cli_rpath, 0, 128);
	memset(cli_wpath, 0, 128);

	sprintf(cli_rpath, "%s/%d_r.fifo", PATH, getpid());
	sprintf(cli_wpath, "%s/%d_w.fifo", PATH, getpid());

	mkfifo(cli_rpath, 0660);
	mkfifo(cli_wpath, 0660);

	memset(ser_path, 0, 128);
	sprintf(ser_path, "%s/%s", PATH, SER_NAME);

	ser_pipe = open(ser_path, O_WRONLY);
	if(ser_pipe == -1)
	{
		perror("open serpipe failed");
		exit(1);
	}

	printf("/---------------------------------------\n");
	printf("open serpipe \033[32msuccessed\033[0m\n");
	printf("---------------------------------------/\n");

	memset(ser_msg, 0, 32);
	sprintf(ser_msg, "%d\n", getpid());
	printf("%s", ser_msg);
	write(ser_pipe, ser_msg, strlen(ser_msg));


	fp_clirpipe = open(cli_rpath, O_RDONLY);
	fp_cliwpipe = open(cli_wpath, O_WRONLY);
	printf("/---------------------------------------\n");

	if(fp_clirpipe == -1 || fp_cliwpipe == -1)
	{
		perror("open clipipe failed");
		exit(1);
	}
	
	printf("/---------------------------------------\n");
	printf("open w&r pipe \033[32msuccessed\033[0m\n");
	printf("---------------------------------------/\n");

	// pv option
	k_shm = atoi(argv[1]);
	k_sem = atoi(argv[2]);

	c_shm = shmget(k_shm, sizeof(CLIM), IPC_CREAT | 0660);
	c_sem = semget(c_sem, 1, IPC_CREAT | 0660);

	c_p = (pCLIM)shmat(c_shm, NULL, 0);

	semctl(c_sem, 0, SETVAL, 1);

	memset(c_p, 0, sizeof(CLIM));

	while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL)
	{

		write(fp_cliwpipe, buf, strlen(buf));
		memset(buf, 0, 1024);
		read(fp_clirpipe, buf, 1024);


		while(P(c_sem), c_p -> c_flag == 1)
		{
			V(c_sem);
			sleep(1);
		}

		strcpy(c_p -> c_msgbuf, buf);
		c_p -> c_flag = 1;
		V(c_sem);
	}

	while(P(c_sem), c_p -> c_flag == 1)
	{
		V(c_sem);
		sleep(1);
	}

	strcpy(c_p -> c_msgbuf, "quit");
	c_p -> c_flag = 1;
	V(c_sem);

	sleep(5);
	shmdt(c_p);
	shmctl(c_shm, IPC_RMID, NULL);
	semctl(c_sem, 0, IPC_RMID);

	return 0;
}

