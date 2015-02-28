/*************************************************************************
	> File Name: ./src/func.c
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 28 Feb 2015 02:49:09 PM CST
 ************************************************************************/

#include"process.h"

void sendFd(int socketFd, int fd)
{
	struct cmsghdr *pCmsg;
	struct iovec buf[2];
	struct msghdr myMsg;

	int cmsgLen = CMSG_LEN(sizeof(int));
	int recVal = 1024;
	char recvBuf[] = "Hello";

	memset(&myMsg, 0, sizeof(myMsg));
	myMsg.msg_name = NULL;
	myMsg.msg_namelen = 0;

	buf[0].iov_base = &recVal;
	buf[0].iov_len = sizeof(recVal);
	buf[1].iov_base = recvBuf;
	buf[1].iov_len = strlen(recvBuf);

	myMsg.msg_iov = buf;
	myMsg.msg_iovlen = 2;
	myMsg.msg_flags = 0;

	pCmsg = (struct cmsghdr *)calloc(1, sizeof(struct cmsghdr));
	pCmsg -> cmsg_len = cmsgLen;
	pCmsg -> cmsg_level = SOL_SOCKET;
	pCmsg -> cmsg_type = SCM_RIGHTS;

	*(int *)CMSG_DATA(pCmsg) = fd;

	myMsg.msg_control = pCmsg;
	myMsg.msg_controllen = cmsgLen;

	sendmsg(socketFd, &myMsg, 0);
}

void recvFd(int socketFd, int *fd)
{
	struct cmsghdr *pCmsg;
	struct iovec buf[2];
	struct msghdr myMsg;

	int cmsgLen = CMSG_LEN(sizeof(int));
	int recVal = 1024;
	char recvBuf[1024] = "";

	memset(&myMsg, 0, sizeof(myMsg));
	myMsg.msg_name = NULL;
	myMsg.msg_namelen = 0;

	buf[0].iov_base = &recVal;
	buf[0].iov_len = sizeof(recVal);
	buf[1].iov_base = recvBuf;
	buf[1].iov_len = 1023;

	myMsg.msg_iov = buf;
	myMsg.msg_iovlen = 2;
	myMsg.msg_flags = 0;

	pCmsg = (struct cmsghdr *)calloc(1, sizeof(struct cmsghdr));
	pCmsg -> cmsg_len = cmsgLen;
	pCmsg -> cmsg_level = SOL_SOCKET;
	pCmsg -> cmsg_type = SCM_RIGHTS;

	myMsg.msg_control = pCmsg;
	myMsg.msg_controllen = cmsgLen;

	recvmsg(socketFd, &myMsg, 0);
	printf("val : %d, buf: %s \n", recVal, recvBuf);

	*fd = *(int *)CMSG_DATA(pCmsg);
	
}
