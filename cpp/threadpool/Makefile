.PHONY:clean
CC=g++
CFLAGS=-Wall -g -std=c++0x
BIN=test
OBJS=main.o inetaddr.o socket.o socketio.o MutexLock.o Condition.o Thread.o ThreadPool.o
LIBS=-lpthread
$(BIN):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)
%.o:%.cpp
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f *.o $(BIN) core
