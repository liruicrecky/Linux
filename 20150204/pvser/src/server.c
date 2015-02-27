/*************************************************************************
	> File Name: ./src/server.c
	> Author: Recky
	> Mail:327763224@qq.com 
	> Created Time: Wed 04 Feb 2015 07:26:53 PM CST
 ************************************************************************/

#include"server.h"

void reverse(char *pstr)
{
	int str, end;
	char tmp;
	
	str = 0;
	end = strlen(pstr) - 1;
	while(str < end)
	{
		tmp = pstr[str];
		pstr[str] = pstr[end];
		pstr[end] = tmp;
		++str;
		--end;
	}
}

void child_handle(int sig_id)
{
//	printf("/---------------------------------------\n");
//	printf("client \033[31moffline\033[0m\n");
//	printf("---------------------------------------/\n");
	wait(NULL);
}

int main(int argc, char *argv[])
{
	signal(17, child_handle);
	//create and set serpipe
	char ser_path[128];
	int  ser_pipe;
	FILE *fp_ser;
	memset(ser_path, 0, 128);
	sprintf(ser_path, "%s/%s", PATH, SER_NAME);
	if(access(ser_path, F_OK) == -1)
	{
		mkfifo(ser_path, 0660);
	}

	ser_pipe = open(ser_path, O_RDONLY);
	open(ser_path, O_WRONLY);
	fp_ser = fdopen(ser_pipe, "r");
	
	printf("/---------------------------------------\n");
	printf("connect serpipe \033[32msuccess\033[0m\n");
	printf("---------------------------------------/\n");

	//fork
	int fd_pipe[2];
	int cli_id;
	char ser_msg[32];
	char cli_path[128];


	while(memset(ser_msg, 0, 32), fgets(ser_msg, 32, fp_ser) != NULL)
	{
		if(pipe(fd_pipe) == -1)
		{
			perror("create interpipe failed");
			exit(1);
		}

		if(fork() > 0)
		{
			close(fd_pipe[0]);
			sscanf(ser_msg, "%d", &cli_id);
			write(fd_pipe[1], &cli_id, sizeof(&cli_id));
			close(fd_pipe[1]);
		}
		else
		{
			char cli_rpath[128], cli_wpath[128];
			int  op_cli_rpipe, op_cli_wpipe;
			char cli_buf[1024];
			close(fd_pipe[1]);
			read(fd_pipe[0], &cli_id, sizeof(&cli_id));
			printf("\033[32m%d\033[0m is \033[32monline\033[0m\n", cli_id);

			memset(cli_rpath, 0, 128);
			memset(cli_wpath, 0, 128);

			sprintf(cli_rpath, "%s/%d_r.fifo", PATH, cli_id);
			sprintf(cli_wpath, "%s/%d_w.fifo", PATH, cli_id);

			op_cli_rpipe = open(cli_rpath, O_WRONLY);
			op_cli_wpipe = open(cli_wpath, O_RDONLY);

			if(op_cli_rpipe == -1 || op_cli_wpipe == -1)
			{
				perror("open clipipe failed");
				exit(1);
			}
					
			printf("/---------------------------------------\n");
			printf("open \033[32m%d\033[0m w&r pipe \033[32msuccessed\033[0m\n", cli_id);
			printf("---------------------------------------/\n");

			while(memset(cli_buf, 0, 1024), read(op_cli_wpipe, cli_buf, 1024) != 0)
			{
			//	reverse(cli_buf);
			//	fflush(op_cli_rpipe);
				write(op_cli_rpipe, cli_buf, strlen(cli_buf));
			}
			
			close(fd_pipe[0]);
			close(op_cli_rpipe);
			close(op_cli_wpipe);
			printf("--------------\033[32m%d\033[0m client is \033[31moffline\033[0m---------------\n", cli_id);
			exit(0);
		}
	}
	
	unlink(ser_path);
	return 0;
}

