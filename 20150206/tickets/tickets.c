/*************************************************************************
	> File Name: tickets.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Fri 06 Feb 2015 07:33:39 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t phdmutex;
pthread_cond_t condSell, condSupply;

void *fSellTickets(void *arg)
{
	int *tick = (int *)arg;
	int tmp;
	int sum = 0;

	while(1)
	{
		pthread_mutex_lock(&phdmutex);
		while(*tick == 0)
		{
			pthread_cond_signal(&condSupply);
			pthread_cond_wait(&condSell, &phdmutex);
		}

		tmp = *tick;
		--tmp;
		*tick = tmp;
		++sum;
		printf("%u sold a ticket, %d, left %d\n", pthread_self(), sum, *tick);
		pthread_mutex_unlock(&phdmutex);
		sleep(1);
	}
	pthread_mutex_unlock(&phdmutex);
	return (void *)sum;
}

void *fSupplyTickets(void *arg)
{
	int *tick = (int *)arg;

	while(1)
	{
		pthread_mutex_lock(&phdmutex);
		if(*tick > 0)
			pthread_cond_wait(&condSupply, &phdmutex);
		*tick = rand() % 30 + 1;
		printf("add %d tickets\n", *tick);
		pthread_mutex_unlock(&phdmutex);
		pthread_cond_broadcast(&condSell);
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	int numTickets, numSell;
	pthread_t pthdSupply;

	numTickets = atoi(argv[2]);
	numSell = atoi(argv[1]);

	int totle = numTickets;

	pthread_mutex_init(&phdmutex, NULL);
	pthread_cond_init(&condSell, NULL);
	pthread_cond_init(&condSupply, NULL);

	pthread_t *pthdSell = (pthread_t *)calloc(numSell, sizeof(pthread_t));
	int *selledTickets = (int *)calloc(numTickets, sizeof(int));

	int i, sum;

	for(i = 0;i < numSell;i++)
	{
		pthread_create(pthdSell + i, NULL, fSellTickets, &numTickets);
	}

	pthread_create(&pthdSupply, NULL, fSupplyTickets, &numTickets);

	for(i = 0;i < numSell;i++)
	{
		pthread_join(pthdSell[i], (void *)(selledTickets + i));
	}

	for(sum = 0, i = 0;i < numSell;i++)
	{
		sum += selledTickets[i];
	}
	
	pthread_mutex_destroy(&phdmutex);
	pthread_cond_destroy(&condSell);
	pthread_cond_destroy(&condSupply);

	printf("sell: %d, totle: %d, current: %d\n", sum, totle, numTickets);


 return 0;
}
