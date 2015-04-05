#include "ThreadPool.h"
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include"Inetaddr.h"
#include"Socket.h"
#include"SocketIO.h"
#include<iostream>
#include<string>
using namespace Tiny;

void nano_sleep(double val);

void foo()
{
	//addr
	InetAddr cliSocketAddr("127.0.0.1", 1234);
	//socket info save
	std::string mode("tcp");
	Socket cliSocket(cliSocketAddr, mode);
	//socket init
	cliSocket.cliInit(cliSocketAddr);
	cliSocket.cliConnect(cliSocketAddr);

	SocketIO cliSocketIO;

	char buf[1024];
	struct sockaddr_in tmp;

	srand(time(NULL));

	int num = rand() % 10 + 1;
	for(int i = 0;i != num;++i){

		buf[i] = rand()%26;
   		buf[i]+=97; 
	}
	buf[num] = '\0';

	while(memset(buf, 0, sizeof(buf)))
	{	
		cliSocketIO.sendBuf(buf, cliSocket.getSocket(), 1024);
		cliSocketIO.recvBuf(buf, cliSocket.getSocket(), 1024);
		std::cout << buf << std::endl;
	}

}

int main(int argc, char const *argv[])
{
    Tiny::ThreadPool pool(100, 1);
    pool.start();

    while(1)
    {
        pool.addTask(&foo);
        nano_sleep(1);
    }
    
    return 0;
}


void nano_sleep(double val)
{
    struct timespec tv;
    tv.tv_sec = val; //取整
    tv.tv_nsec = (val - tv.tv_sec) * 1000 * 1000 * 1000;

    int ret;
    do
    {
        ret = nanosleep(&tv, &tv);
    }while(ret == -1 && errno == EINTR);
}
