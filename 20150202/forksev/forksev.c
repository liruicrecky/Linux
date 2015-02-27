/*************************************************************************
	> File Name: /home/liruicheng/LinuxCode/20150202/forksev/forksev.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Mon 02 Feb 2015 09:34:33 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>
#include<sys/select.h>

#define PATH "/home/liruicheng/pipe"
#define SIGTERM 15

int main(int argc, char *argv[])
{
	int fd_pipe[2];
	int fd_send, fd_recv;
	pid_t pid;

	if(pipe(fd_pipe) == -1){
		perror("create fd_pipe failed");
		exit(1);
	}

	printf("inter pipe create successed\n");
	

	printf("start fork!\n");

	pid = fork();
	char buf[1024];
	char msg[128];

	if(pid == 0){  //child process

		if((fd_recv = open("./recv", O_RDONLY)) == -1){
			perror("open recv pipe failed");
			exit(1);
		}
		printf("child process open read pipe successed\n");

		while(1){
			memset(buf, 0, 1024);
			memset(msg, 0, 128);

			if(read(fd_recv, buf, 1024) != 0){
				printf("Form other: %s", buf);
				continue;
			} 
			if(read(fd_pipe[0], msg, 128) != 0){
				printf("child process prepare to exit\n");
				if(strcmp(msg, "exit") == 0){
					close(fd_send);
					close(fd_recv);
					close(fd_pipe[0]);
					close(fd_pipe[1]);
					printf("child exit success!\n");
					exit(0);
				}
			}
		}

	}else{

		if((fd_send = open("./send", O_WRONLY)) == -1){
			perror("open send pipe failed");
			exit(1);
		}

		printf("main process open write pipe successed\n");
		while(1){
			memset(buf, 0, 1024);
			if(read(0, buf, 1024 - strlen(buf)) == 0){
				printf("exit now\n");
				kill(pid, SIGTERM);
				printf("send meg to child process\n");
				memset(msg, 0, 128);
				strcpy(msg, "exit");
				write(fd_pipe[1], msg, sizeof(msg));
				printf("write to child process success\n");
				waitpid(pid, NULL, 0);
				close(fd_pipe[1]);
				close(fd_pipe[0]);
				close(fd_send);
				close(fd_recv);
				exit(0);
			}else{
				write(fd_send, buf, sizeof(buf));
			}
		}
	}

	return 0;
}
