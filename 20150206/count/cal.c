/*************************************************************************
	> File Name: cal.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Fri 06 Feb 2015 02:59:47 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>


long long int sum1 = 0, sum2 = 0;

void *add1(void *arg)
{
	long long int i = 500000000;
	while(i--)
		++sum1;
	return(NULL);
}

void *add2(void *arg)
{
	long long int i = 500000000;
	while(i--)
		++sum2;
	return(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t phd1, phd2;
	clock_t str, end;
	long long int su = 0;
	
	str = clock();

	pthread_create(&phd1, NULL, add1, NULL);
	pthread_create(&phd2, NULL, add2, NULL);


	pthread_join(phd1, NULL);
	pthread_join(phd2, NULL);
	su = sum1 + sum2;
	end = clock();

	printf("time:%2.6lf,  %ld\n", (double)(end - str)/CLOCKS_PER_SEC, su);

	long long int ss = 0, j = 1000000000;
	
	str = clock();
	while(j--)
		++ss;
	end = clock();

	printf("time:%2.6lf,  %ld\n", (double)(end - str)/CLOCKS_PER_SEC, ss);

	return 0;
}
