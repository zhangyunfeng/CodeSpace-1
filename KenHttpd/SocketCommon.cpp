

#include "SocketCommon.hpp"


//system socket domain
int getStdDomain(Domain d)
{
	switch (d) {
		case Domain::UNIX:	return AF_UNIX;
		case Domain::LOCAL:	return AF_LOCAL;
		case Domain::INET: return AF_INET;
		case Domain::INET6: return AF_INET6;
		case Domain::IPX: return AF_IPX;
		case Domain::NETLINK: return AF_NETLINK;
		case Domain::X25: return AF_X25;
		case Domain::AX25: return AF_AX25;
		case Domain::ATMPVC: return AF_ATMPVC;
		case Domain::APPLETALK: return AF_APPLETALK;
		case Domain::PACKET: return AF_PACKET;
		default: return AF_INET;
	}
}

// system socket type
int getStdType(Type t)
{
	switch(t) {
		case Type::STREAM: return SOCK_STREAM;
		case Type::DGRAM: return SOCK_DGRAM;
		case Type::SEQPACKET: return SOCK_SEQPACKET;
		case Type::RAW: return SOCK_RAW;
		case Type::RDM: return SOCK_RDM;
		case Type::PACKET: return SOCK_PACKET;
		case Type::NONBLOCK: return SOCK_NONBLOCK;
		case Type::CLOEXEC: return SOCK_CLOEXEC;
		default: return SOCK_STREAM;
	}
}

//System protocol
int getStdProtocol(Protocol p)
{
	switch(p) {
		case Protocol::DEFAULT: return 0;
		default: return 0;
	}

}