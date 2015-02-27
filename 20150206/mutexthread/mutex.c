/*************************************************************************
	> File Name: mutex.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Fri 06 Feb 2015 10:41:35 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

typedef struct _mutex
{
	int sum;
	pthread_mutex_t muphd;
}*MUT, MUTE;

MUT mu;

void *add(void *arg)
{
	int i = 100000000;
	pthread_mutex_lock(&mu -> muphd);
	while(i)
	{
		++mu -> sum;
		--i;
	}
	pthread_mutex_unlock(&mu -> muphd);
	return(NULL);
}

int main(int argc, char *argv[])
{
	int i;
	pthread_t phd1, phd2;

	if((mu = malloc(sizeof(MUTE))) != NULL)
	{
		mu -> sum = 0;
		if(pthread_mutex_init(&mu -> muphd, NULL) != 0)
		{	
			free(mu);
			exit(1);
		}
	}

	pthread_create(&phd1, NULL, add, NULL);
	pthread_create(&phd2, NULL, add, NULL);

	pthread_join(phd1, NULL);
	pthread_join(phd2, NULL);

	printf("%d\n", mu -> sum);

	pthread_mutex_destroy(&mu -> muphd);
	free(mu);

	return 0;
}
