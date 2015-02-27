/*************************************************************************
	> File Name: my_fork.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Mon 02 Feb 2015 09:05:51 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[])
{
	int i, sum;
	int fd_pipe[2];
	int c_num;
	char buf[1024];
	pid_t pid;

	if(pipe(fd_pipe) < 0){
		perror("Error:");
		exit(1);
	}

	sum = 0;
	pid = fork();

	if(pid == 0){
		printf("child process start work!\n");
		close(fd_pipe[0]);
		for(i = 0;i < 100;i++)
			sum += i;
		memset(buf, 0, 1024);
		sprintf(buf, "%d", sum);
	//	if(write(fd_pipe[1], buf, sizeof(buf)) != -1)
		if(write(fd_pipe[1], &sum, sizeof(&sum)) != -1)
			printf("write to pipe success\n");
		close(fd_pipe[1]);
		exit(0);
	}else{
		printf("main process start work!\n");
		close(fd_pipe[1]);
		memset(buf, 0, 1024);
		sleep(1);
		if(read(fd_pipe[0], &sum, sizeof(&sum)) != -1)
			printf("read from pipe success\n");
	//	puts(buf);
		printf("%d\n", sum);
		close(fd_pipe[0]);
		waitpid(pid, NULL, 0);
		exit(0);
	}

	return 0;
}

