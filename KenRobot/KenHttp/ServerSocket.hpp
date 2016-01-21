/**

**AUTH: Ken

**/


#ifndef SERVERSOCKET_HPP_
#define SERVERSOCKET_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <memory>
#include <thread>
#include <utility>

#include "SocketCommon.hpp"

class ServerSocket 
{
public:
	ServerSocket() = delete;
	ServerSocket(std::unique_ptr<SocketParam>& sp);
	virtual ~ServerSocket();

	void StartServer();

	void StopServer();

	void RestartServer();

	bool IsServerRunning();

	void ResetServerParam(std::unique_ptr<SocketParam>& sp);

	void SetServerListenMax(int listenMax);

	int GetServerListenMax();

private:
	std::unique_ptr<SocketParam> m_sp;
	int m_listenMax;
	int m_socketfd;
	int m_clientsocketfd;  //socket fd to write and read
	struct sockaddr_in m_server_addr;
	struct sockaddr_in m_client_addr; //current connecting client socket-addr
	bool m_hasStartedServer;
};

#endif //SERVERSOCKET_HPP_