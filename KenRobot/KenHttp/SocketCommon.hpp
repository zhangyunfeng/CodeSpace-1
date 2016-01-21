
/**
**AUTH: Ken
**/

#ifndef SOCKET_COMMON_HPP_
#define SOCKET_COMMON_HPP_

#ifdef __CPLUSPLUS
extern "C" {
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#ifdef __CPLUSPLUS
}
#endif

#include <string>

//域
enum class Domain:int {
	UNIX = 1, LOCAL = 11, INET = 2, INET6 = 3, IPX = 4,
	NETLINK = 5, X25 = 6, AX25 = 7, ATMPVC = 8, APPLETALK = 9, PACKET = 10,
};

//类型
enum class Type:int {
	STREAM = 1, DGRAM = 2, SEQPACKET = 3, RAW = 4, RDM = 5, PACKET = 6, NONBLOCK = 7, CLOEXEC = 8,
};

//协议
enum class Protocol:int {
	DEFAULT = 0,
};

struct SocketParam {
	std::string serverIp; //e.g.  localhost , 127.0.0.1 
	int serverPort;
	Domain domain; //AF_INET AF_INET6 etc
	Type type; //SOCK_STREAM etc
	Protocol protocol; //

	SocketParam(const std::string& serverIp, int serverPort, Domain domain, Type type, Protocol protocol) // 
		{
			this->serverIp = serverIp;
			this->serverPort = serverPort;
			this->domain = domain;
			this->type = type;
			this->protocol = protocol;
		}
};


//system socket domain
extern int getStdDomain(Domain d);

// system socket type
extern int getStdType(Type t);


//System protocol
extern int getStdProtocol(Protocol p);


typedef void (*HandleReceiveFuncPtr_T)() ;

#endif

