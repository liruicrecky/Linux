/*************************************************************************
	> File Name: ./src/func.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 28 Feb 2015 08:28:07 PM CST
 ************************************************************************/

#include"ftp.h"

void makeChild(pCHILD pChi, int numChi)
{
	int cnt;
	int index = 0;

	for(cnt = 0;cnt < numChi;cnt++)
	{
		int sockPair[2];
		if(socketpair(AF_LOCAL, SOCK_STREAM, 0, sockPair) == -1)
		{
			perror("sockpair");
			exit(1);
		}

		pid_t childPid = fork();
		if(childPid == 0)
		{
			close(sockPair[1]);
			int clientFd;
			while(1)
			{
				recvFd(sockPair[0], &clientFd);		
				handleRequest(clientFd);
				write(sockPair[0], &childPid, sizeof(childPid));
			}
			exit(1);
		}
		close(sockPair[0]);
		pChi[index].socketFd = sockPair[1];
		pChi[index].childPid = childPid;
		pChi[index].stat = FREE;
		pChi[index].alreadyDone = 0;
		++index;
	}
}

void handleRequest(int sockFd)
{
	char buf[1024];
	char comm[10], para[10];
	memset(buf, 0, 1024);

	strcpy(buf, "welcome to the server!");
	send(sockFd, buf, strlen(buf), 0);

	while(1)
	{
		memset(buf, 0, 1024);
		recv(sockFd, buf, 1024, 0);
		memset(comm, 0, 10);
		memset(para, 0, 10);
		sscanf(buf, "%s %s", comm, para);
		printf("%s %s\n", comm, para);
		judgeCommand(comm, para, sockFd);
		
		printf("client says: %s\n", buf);
		if(buf[0] == 'q')
			break;
	}

}

void sendFd(int sockFd, int fd)
{
	struct msghdr myMsg;
	struct iovec iovs[1];
	struct cmsghdr *pcmsg;

	memset(&myMsg, 0, sizeof(myMsg));
	
	myMsg.msg_name = NULL;
	myMsg.msg_namelen = 0;

	char sendBuf[1024];
	memset(sendBuf, 0, 1024);

	iovs[0].iov_base = &sendBuf;
	iovs[0].iov_len = sizeof(sendBuf);

	myMsg.msg_iov = iovs;
	myMsg.msg_iovlen = 1;
	myMsg.msg_flags = 0;

	int cmsgLen = CMSG_LEN(sizeof(int));

	pcmsg = (struct cmsghdr *)calloc(1, sizeof(struct cmsghdr));

	pcmsg -> cmsg_len = cmsgLen;
	pcmsg -> cmsg_level = SOL_SOCKET;
	pcmsg -> cmsg_type = SCM_RIGHTS;

	*(int *)CMSG_DATA(pcmsg) = fd;

	myMsg.msg_control = pcmsg;
	myMsg.msg_controllen = cmsgLen;

	sendmsg(sockFd, &myMsg, 0);
}

void recvFd(int sockFd, int *fd)
{
	struct msghdr myMsg;
	struct iovec iovr[1];
	struct cmsghdr *pcmsg;

	memset(&myMsg, 0, sizeof(myMsg));

	myMsg.msg_name = NULL;
	myMsg.msg_namelen = 0;

	char recvBuf[1024];

	iovr[0].iov_base = &recvBuf;
	iovr[0].iov_len = sizeof(recvBuf);

	myMsg.msg_iov = iovr;
	myMsg.msg_iovlen = 1;
	myMsg.msg_flags = 0;

	int cmsgLen = CMSG_LEN(sizeof(int));

	pcmsg = (struct cmsghdr *)calloc(1, sizeof(struct cmsghdr));

	pcmsg -> cmsg_len = cmsgLen;
	pcmsg -> cmsg_level = SOL_SOCKET;
	pcmsg -> cmsg_type = SCM_RIGHTS;

	myMsg.msg_control = pcmsg;
	myMsg.msg_controllen = cmsgLen;

	recvmsg(sockFd, &myMsg, 0);
	
	*fd = *(int *)CMSG_DATA(pcmsg);
}

