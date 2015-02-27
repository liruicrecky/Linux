/*************************************************************************
      > File Name: ser.c
      > Author: Reacky
      > Mail:327763224@qq.com 
      > Created Time: Fri 30 Jan 2015 09:24:01 AM CST
 ************************************************************************/

#include"pipser.h"

int main(int argc, char *argv[])
{
	int fp_ser_enter;
	int res;
	char buf[BUF_SIZE];

	//create ser_pipe
	
	char path_name[128];

	sprintf(path_name, "%s/%s", PIPE_PATH, SER_PIPE_NAME);

	printf("/----------------------------------------\n");
	if(access(path_name, F_OK) == -1){

		res = mkfifo(path_name, 0666);
		if(res != 0){
			perror("create ser_pipe failed:");
			exit(1);
		}
		printf("ser_pipe create \033[31mOK!\033[0m\n");

	}else{	
		printf("ser_pipe create \033[31mOK!\033[0m\n");
	}

	printf("waiting for the client\n");

	fp_ser_enter = open(path_name, O_RDONLY);
	if(fp_ser_enter == -1){
		perror("open ser_pipe failed:\n");
		exit(1);
	}

	printf("\nopen ser_pipe \033[31msuccess\033[0m\n");
	printf("------------------------------------/\n");

	//ser_pipe judge
	
	fd_set ser_survilliance, bak_ser;

	pCLIENT c_list = NULL;

	FD_ZERO(&ser_survilliance);
	FD_ZERO(&bak_ser);
	FD_SET(0, &ser_survilliance);
	FD_SET(fp_ser_enter, &ser_survilliance);

	int  cli_pid;
	char cli_sta[128];
	char cli_path[128];

	while(1){

		bak_ser = ser_survilliance;
		select(1024, &bak_ser, NULL, NULL, NULL);
		
		pCLIENT pcur = c_list;
		int tmp;
       
		//exit

		//send msg
		while(pcur){
				tmp = pcur -> c_send;
				if(FD_ISSET(tmp, &bak_ser)){
					pCLIENT psend = c_list;
					memset(buf, 0, 1024);
					read(tmp, buf, 1024);
					while(psend){
						if(psend -> c_send != tmp)
							write(psend -> c_recv, buf, sizeof(buf));
						psend = psend -> next;
					}
				}
			pcur = pcur ->next;
		}

		//new client &  del client
		if(FD_ISSET(fp_ser_enter, &bak_ser)){

			if(read(fp_ser_enter, buf, 1024) == 0)
				continue;

			read(fp_ser_enter, buf, 1024);
		
			sscanf(buf, "%s%d", cli_sta, &cli_pid);

			if(strncmp("on", cli_sta, 2) == 0){

				printf("\n/-----------------------------------------\n");
				printf("client \033[33m%d\033[0m is \033[32monline!\033[0m\n", cli_pid);
		
				//list
				pCLIENT pnew;
				pnew = (pCLIENT)calloc(1, sizeof(CLIENT));

				pnew -> c_pid = cli_pid;
				pnew -> next = NULL;

				//add read pipe
				memset(cli_path, 0, 128);
				sprintf(cli_path, "%s/%d_send.fifo", PIPE_PATH, cli_pid);
				
				int f_cend, f_recv;

				f_cend = open(cli_path, O_RDONLY);
				if(f_cend == -1){
					perror("open read client pipe faild");
					exit(1);
				}

				pnew -> c_send = f_cend;
		
				//add write pipe
				memset(cli_path, 0, 128);
				sprintf(cli_path, "%s/%d_recv.fifo", PIPE_PATH, cli_pid);
				
				f_recv = open(cli_path, O_WRONLY);
				if(f_recv == -1){
					perror("open write client pipe faild");
					exit(1);
				}

				pnew -> c_recv = f_recv;

				FD_SET(f_cend, &ser_survilliance);
				//create list
				if(c_list == NULL){
					c_list = pnew;
					c_list -> next = NULL;
				}else{
					pnew -> next = c_list;
					c_list = pnew;
				}

				printf("set client \033[33m%d\033[0m online \033[32msuccess\033[0m\n", cli_pid);	
				printf("-----------------------------------------/\n");
		
			}else if(strncmp("off", cli_sta, 3) == 0){

				printf("\n/------------------------------");
				printf("\nclient \033[33m%d\033[0m is \033[31moffline\033[0m\n", cli_pid);

				//search list
				pCLIENT ptmp = c_list, pdel;
			
				//if head
				if(c_list -> c_pid == cli_pid){
					
					pdel = c_list;
		
				}else{

					while(ptmp -> next){
						if(ptmp -> next -> c_pid == cli_pid){
							break;
						}
						ptmp = ptmp -> next;
					}

					pdel = ptmp -> next;
				}

				//clear select
				FD_CLR(pdel -> c_send, &ser_survilliance);
			
				//close pipe
				close(pdel -> c_send);
				close(pdel -> c_recv);
				
				//del node from list
				ptmp -> next = pdel -> next;
				free(pdel);
	
				printf("set client \033[33m%d\033[0m offline \033[32msuccess\033[0m", cli_pid);
				printf("\n-----------------------------/\n");

			}
		}		
	}

	return 0;
}				
