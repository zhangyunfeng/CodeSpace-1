CC := g++
CCFLAGS := -Wall
CCVERSION := -std=c++11

LIBS := -pthread

OBJECT := HttpTest

COMMONSRC := SocketCommon.hpp \
	SocketCommon.cpp \
	ClientSocket.cpp \
	ServerSocket.hpp \
	ServerSocket.cpp  \
	ThreadPool.hpp \
	ThreadPool.cpp \
	Url.hpp \
	Url.cpp \
	HttpClient.hpp \
	HttpClient.cpp \
	DNSUtil.hpp \
	DNSUtil.cpp \
	HttpResponseData.hpp \
	HttpResponseData.cpp \
	HttpTest.cpp \
	HttpManager.hpp \
	HttpManager.cpp \
	OnRequestListener.hpp \


$(OBJECT):$(COMMONSRC) HttpTest.cpp
	@echo "Compiling " $@	
	$(CC) $(CCFLAGS) $^ -o $@ $(CCVERSION) $(LIBS)

.PHONY:clean
clean:
	-rm $(OBJECT) *~ *#
