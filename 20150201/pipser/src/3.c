/*************************************************************************
      > File Name: 3.c
      > Author: Reacky
      > Mail:327763224@qq.com 
      > Created Time: Fri 30 Jan 2015 09:27:57 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/select.h>

int main(int argc, char *argv[])
{
	int fp_23;
	int res;
	char buf[1024];
	struct timeval tm;

	fd_set fres;

	fp_23 = open(argv[1], O_RDONLY);

	if(fp_23 == -1)
	{
		perror("Error:");
		exit(1);
	}

	printf("connect OK\n");
	while(1)
	{
		tm.tv_sec = 0;
		tm.tv_usec = 1;

		FD_ZERO(&fres);
		FD_SET(0, &fres);
		FD_SET(fp_23, &fres);

		res = select(15, &fres, NULL, NULL, &tm);

		if(res == 0)
		{
		}
		else
		{
			if(FD_ISSET(0, &fres))
			{
				close(fp_23);

				fp_23 = open(argv[1], O_WRONLY);
				
				if(fp_23 == -1)
				{
					perror("Error:");
					exit(1);
				}
				memset(buf, 0, 1024);
				read(0, buf, 1024);
				write(fp_23, buf, strlen(buf));
				close(fp_23);
				fp_23 = open(argv[1], O_RDONLY);
			}
			else if(FD_ISSET(fp_23, &fres))
			{
				memset(buf, 0, 1024);
				read(fp_23, buf, 1024);
				printf("%s", buf);
			}
		}
	}
	close(fp_23);
	return 0;
}
