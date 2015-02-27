/*************************************************************************
      > File Name: 1.c
      > Author: Reacky
      > Mail:327763224@qq.com 
      > Created Time: Fri 30 Jan 2015 09:10:52 AM CST
 ************************************************************************/

#include"pipser.h"

int main(int argc, char *argv[])
{
	int res;
	char buf[1024];

	//create pipe

	char path_send[128], path_recv[128];

	sprintf(path_send, "%s/%u_send.fifo", PIPE_PATH, getpid());
	sprintf(path_recv, "%s/%u_recv.fifo", PIPE_PATH, getpid());

	int fp_send, fp_recv;
	printf("--------------------------------------\n");

	if(access(path_send, F_OK) == -1){
		mkfifo(path_send, 0666);	
	}

	if(access(path_recv, F_OK) == -1){
		mkfifo(path_recv, 0666);
	}
	
	printf("pipe \033[32mready!\033[0m\n");

	//connect ser	
	char ser_path[128];
	char ser_msg[1024] = "";
	
	sprintf(ser_path, "%s/%s", PIPE_PATH, SER_PIPE_NAME);

	res = open(ser_path, O_WRONLY);
	if(res == -1){
		perror("connect server failed:");
		exit(1);
	}
	printf("open ser_pipe \033[32msuccess\033[0m\n");

	sprintf(ser_msg, "on %u", getpid());
	write(res, ser_msg, sizeof(ser_msg));

	close(res);

	printf("%d client connect server \033[32msuccess\033[0m\n", getpid());


	fp_send = open(path_send, O_WRONLY);
	if(fp_send == -1){
		perror("open send_pipe failed:");
		exit(1);
	}

	fp_recv = open(path_recv, O_RDONLY);
	if(fp_recv == -1){
		perror("open send_pipe failed:");
		exit(1);
	}
	//pipe listeh
	
	fd_set cli_survilliance;

	char msg[1024];
	memset(msg, 0, 1024);

	printf("\n-------------------------------\n");
	while(1){

		FD_ZERO(&cli_survilliance);
		FD_SET(0, &cli_survilliance);
		FD_SET(fp_recv, &cli_survilliance);

		char msg[1024];

		select(1024, &cli_survilliance, NULL, NULL, NULL);

		if(FD_ISSET(0, &cli_survilliance)){
			
			memset(msg, 0, 1024);
			sprintf(msg, "form \033[33m%d\033[0m : ", getpid());

			if(read(0, msg + strlen(msg), 1024 - strlen(msg)) == 0)
			{

				res = open(ser_path, O_WRONLY);
				if(res == -1){
					perror("connect server failed:");
					exit(1);
				}

				memset(ser_msg, 0, 128);
				sprintf(ser_msg, "off %d", getpid());
				write(res, ser_msg, sizeof(ser_msg));

				close(res);
				close(fp_send);
				close(fp_recv);
				unlink(path_send);
				unlink(path_recv);
				exit(0);
			}

			write(fp_send, msg, sizeof(msg));
		}
		if(FD_ISSET(fp_recv, &cli_survilliance)){

			memset(buf, 0, 1024);
			read(fp_recv, buf, 1024);
			printf("\n/--------------------------------/\n");
			printf("%s\n", buf);
		}
	}
		
	return 0;
}

