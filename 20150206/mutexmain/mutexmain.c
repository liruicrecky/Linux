/*************************************************************************
	> File Name: mutexmain.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Fri 06 Feb 2015 11:06:39 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


int sum = 0;
pthread_mutex_t muphd;

void *add(void *arg)
{
	int i = 100000000;
	pthread_mutex_lock(&muphd);
	while(i--)
		++sum;
	pthread_mutex_unlock(&muphd);
	return(NULL);
}

int main(int argc, char *argv[])
{
	int i = 100000000;
	pthread_t phd;
	pthread_mutex_init(&muphd, NULL);
	
	pthread_create(&phd, NULL, add, NULL);

	while(i--)
		++sum;

	pthread_join(phd, NULL);
	pthread_mutex_destroy(&muphd);

	printf("%d\n", sum);


	return 0;
}
