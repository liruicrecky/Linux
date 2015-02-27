/*************************************************************************
	> File Name: ./include/2048.h
	> Author: Reacky
	> Mail:3277632240@qq.com 
	> Created Time: Thu 26 Feb 2015 08:09:29 PM CST
 ************************************************************************/

#ifndef __MIAN_H__
#define __MIAN_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ncurses.h>

void refreshPad(int *pad);
void refineArray(int *fourArr, int *nineArr);
void initPad(int *pad);
int mergeNum(int *fourArr, int dire);
void randomNum(int *fourArr);
int checkWin(int *fourArr);

#endif

