/*************************************************************************
	> File Name: server.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Fri 06 Feb 2015 09:38:25 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#define STR_LEN 128

typedef struct _QueueInfo
{
	char **queueStr;
	int queueCurrSize;
	int queueLen;
	int queueStrt, queueTail;
	int flag;
	int threadPrintCnt;
	pthread_mutex_t phdmutex;
	pthread_cond_t condThread, condMain, condPrint;
}QUEUE, *pQUEUE;

void putStrInQueue(pQUEUE que, char *str);
void getStrInQueue(pQUEUE que, char *str);
void *fThreadPrint(void *arg);

void *fThreadPrint(void *arg)
{
	pQUEUE que = (pQUEUE)arg;

	char buf[STR_LEN];
	int cnt = 0;
	while(1)
	{
		pthread_mutex_lock(&que -> phdmutex);
		if(cnt > que -> threadPrintCnt)
		{
			pthread_cond_wait(&que -> condPrint, &que -> phdmutex);
		}
		pthread_mutex_unlock(&que -> phdmutex);
		memset(buf, 0, STR_LEN);
		getStrInQueue(que, buf);
		if(buf[0] == '\0')
		{
			printf("%u exit!\n", pthread_self());
			pthread_cond_broadcast(&que -> condThread);
			pthread_exit((void *)cnt);
		}
		++cnt;
		printf("thread %u print: %s\n", pthread_self(), buf);
		pthread_cond_broadcast(&que -> condPrint);

		if(strcmp(buf, "exit") == 0)
		{
			que -> flag = 1;
			pthread_cond_broadcast(&que -> condThread);
			pthread_exit((void *)cnt);
		}
	}
}

void putStrInQueue(pQUEUE que, char *str)
{
	pthread_mutex_lock(&que -> phdmutex);

	while(que -> queueCurrSize == que -> queueLen)
		pthread_cond_wait(&que -> condMain, &que -> phdmutex);

	que -> queueTail = (que -> queueTail + 1) % que -> queueLen;
	strcpy(que -> queueStr[que -> queueTail], str);
	++que -> queueCurrSize;
	pthread_mutex_unlock(&que -> phdmutex);
	pthread_cond_broadcast(&que -> condThread);
}

void getStrInQueue(pQUEUE que, char *str)
{
	pthread_mutex_lock(&que -> phdmutex);

	while(que -> queueCurrSize == 0 && que -> flag == 0)
		pthread_cond_wait(&que -> condThread, &que -> phdmutex);

	if(que -> flag == 1)
	{
		str[0] = '\0';
		pthread_mutex_unlock(&que -> phdmutex);
		return;
	}

	strcpy(str, que -> queueStr[que -> queueStrt]);
	--que -> queueCurrSize;
	que -> queueStrt = (que -> queueStrt + 1) % que -> queueLen;
	pthread_mutex_unlock(&que -> phdmutex);
	pthread_cond_broadcast(&que -> condMain);
}

int main(int argc, char *argv[])
{
	QUEUE que;
	memset(&que, 0, sizeof(QUEUE));

	//create queue
	int numThread;

	numThread = atoi(argv[1]);
	que.queueLen = atoi(argv[2]);

	int i;

	que.queueStr = (char **)calloc(que.queueLen, sizeof(char *));

	for(i = 0;i < que.queueLen;i++)
	{
		que.queueStr[i] = (char *)calloc(STR_LEN, sizeof(char));
	}

	que.queueCurrSize = 0;
	que.queueStrt = 0;
	que.queueTail = -1;

	pthread_mutex_init(&que.phdmutex, NULL);
	pthread_cond_init(&que.condThread, NULL);
	pthread_cond_init(&que.condMain, NULL);
	pthread_cond_init(&que.condPrint, NULL);

	//create pthread
	
	pthread_t *pthreadWork = (pthread_t *)calloc(numThread, sizeof(pthread_t));
	int *threadTask = (int *)calloc(numThread, sizeof(int));

	for(i = 0;i < numThread;i++)
	{
		pthread_create(pthreadWork + i, NULL, fThreadPrint, &que);
	}
	//put str in queue
	char buf[STR_LEN];
	int inputCnt = 0;
	while(memset(buf, 0, STR_LEN), fgets(buf, STR_LEN, stdin) != NULL)
	{
		++inputCnt;
		que.threadPrintCnt = inputCnt / numThread;
		if(que.threadPrintCnt < numThread)
			que.threadPrintCnt = inputCnt % numThread;
		putStrInQueue(&que, buf);
	}

	//exit
	strcpy(buf, "exit");
	putStrInQueue(&que, buf);


	//thread exit
	for(i = 0;i < numThread;i++)
	{
		pthread_join(pthreadWork[i], (void *)(threadTask + i));
	}

	//show lode
	for(i = 0;i < numThread;i++)
	{
		printf("%d ", threadTask[i]);
	}

	printf("\n");

	pthread_mutex_destroy(&que.phdmutex);
	pthread_cond_destroy(&que.condThread);
	pthread_cond_destroy(&que.condMain);
	pthread_cond_destroy(&que.condPrint);

	return 0;
}
