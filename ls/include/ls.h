/*************************************************************************
	> File Name: ./include/ls.h
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Sat 21 Feb 2015 03:48:15 PM CST
 ************************************************************************/
#ifndef __LS_H__
#define __LS_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>


void getFileInfo(char *path);
void getDirInfo(char *path, int flag);
static void modeToStr(mode_t mode, char *buf);

#endif
