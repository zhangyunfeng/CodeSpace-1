CC := g++
CCFLAGS := -Wall
CCVERSION := -std=c++11

LIBS := 

CLIENTOBJ := SocketClientTest

SERVEROBJ := SocketServerTest

COMMONSRC := ClientSocket.hpp \
	SocketCommon.hpp \
	SocketCommon.cpp \
	ClientSocket.cpp \
	ServerSocket.hpp \
	ServerSocket.cpp 

all:$(CLIENTOBJ) $(SERVEROBJ)

$(CLIENTOBJ):$(COMMONSRC) ClientTest.cpp
	@echo "Compiling " $@
	$(CC) $(CCFLAGS) $^ -o $@ $(CCVERSION) $(LIBS)

$(SERVEROBJ):$(COMMONSRC) ServerTest.cpp
	@echo "Compiling " $@
	$(CC) $(CCFLAGS) $^ -o $@ $(CCVERSION) $(LIBS)

.PHONY:clean
clean:
	-rm $(CLIENTOBJ) *~ *#
	-rm $(SERVEROBJ) *~ *#
