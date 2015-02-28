/*************************************************************************
	> File Name: src/localsock.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 28 Feb 2015 02:49:00 PM CST
 ************************************************************************/

#include"process.h"

int main(int argc, char *argv[])
{
	int socketPair[2];

	int serverSocketPair = socketpair(AF_LOCAL, SOCK_STREAM, 0, socketPair);
	if(serverSocketPair == -1)
	{
		perror("serversocketpair");
		exit(1);
	}

	if(fork() == 0)
	{
		int fd;
		recvFd(socketPair[1], &fd);
		char buf[1024] = "";
		read(fd, buf, 1024);
		printf("from father: %s\n", buf);
		exit(1);
	}
	int fileFd = open(argv[1], O_RDONLY);
	if(fileFd == -1)
	{
		perror("open file");
		exit(1);
	}
	sendFd(socketPair[0], fileFd);
	wait(NULL);

	return 0;
}
