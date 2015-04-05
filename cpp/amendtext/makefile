INC_DIR:=./include
SRC_DIR:=./src/main/server/ ./src/socket/ ./src/thread/
SRCS:=$(wildcard ./src/main/server/*.cpp) $(wildcard ./src/socket/*.cpp) $(wildcard ./src/thread/*.cpp)
#OBJS:= $(patsubst %.cpp, %.cco, $(SRCS)) 
LIBS:= -lpthread -lhiredis

CXX:=g++

CXXFLAGS:= -Wall -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS)

EXE:=./bin/server.o

$(EXE):$(SRCS)
	$(CXX) -o $(EXE) $(SRCS) $(CXXFLAGS)

clean:
	rm -rf $(EXE)
	rm -rf $(OBJS)
