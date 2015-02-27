/*************************************************************************
	> File Name: ./include/gobang.h
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Mon 23 Feb 2015 02:08:25 PM CST
 ************************************************************************/
#ifndef __GOBANG_H__
#define __GOBANG_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

typedef struct _AiPos
{
	int sx, sy;
	int ex, ey;
	int maxCent;
	int mode;
}AIPOS;

void refreshChessesPad(char *pad);
int checkWin(char *pad, char color);
int aiJudegePad(char *pad, char color, int x, int y);
void aiChesses(char *pad, char color);

#endif
