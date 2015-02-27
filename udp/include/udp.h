/*************************************************************************
	> File Name: ./include/udp.h
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 14 Feb 2015 12:20:12 PM CST
 ************************************************************************/

#ifndef __UDP_H__
#define __UDP_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int socketInit(char *ip, int port);


#endif
