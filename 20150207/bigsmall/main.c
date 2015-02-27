/*************************************************************************
	> File Name: main.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Sat 07 Feb 2015 04:35:52 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int a = 0x1234;
	char x1, x2;

	x1 = *((char *)&a);
	x2 = *((char *)&a + 1);

	printf("x1: %x, x2: %x\n", x1, x2);

	return 0;
}
