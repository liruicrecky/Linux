/*************************************************************************
	> File Name: app.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Fri 06 Feb 2015 11:19:04 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

pthread_mutex_t muphd;
char buf[1024];
int flag;

void *readStdin(void *arg)
{
	pthread_mutex_lock(&muphd);
	while(memset(buf, 0, 1024), fgets(buf, 1024, stdin))
	{
		if(strcmp(buf, "end") != 0)
		{
			flag = 1;
			pthread_mutex_unlock(&muphd);
			sleep(1);
			pthread_mutex_lock(&muphd);
		}
		else
			return(NULL);
	}
}

void *writeStdin(void *arg)
{
	while(strcmp(buf, "end") != 0)
	{
		pthread_mutex_lock(&muphd);
		if(flag)
		{
			printf("%s", buf);
			flag = 0;
		}
		pthread_mutex_unlock(&muphd);
	}
	return(NULL);
}

int main(int aegc, char *argv[])
{
	pthread_t stdinRead, stdinWrite;

	pthread_mutex_init(&muphd, NULL);

	pthread_create(&stdinRead, NULL, readStdin, NULL);
	pthread_create(&stdinWrite, NULL, writeStdin, NULL);

	pthread_join(stdinRead, NULL);
	pthread_join(stdinWrite, NULL);

	pthread_mutex_destroy(&muphd);

	return 0;
}
