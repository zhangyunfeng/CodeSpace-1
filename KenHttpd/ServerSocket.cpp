
// Implement ServerSocket

#include <cassert>

#include "ServerSocket.hpp"


ServerSocket::ServerSocket(std::unique_ptr<SocketParam>& sp)
{
	m_sp = std::move(sp);
	m_socketfd = -1;
	m_clientsocketfd = -1;
	m_listenMax = 50;
	m_hasStartedServer = false;
}


ServerSocket::~ServerSocket()
{
	if (m_hasStartedServer) {
		if (m_clientsocketfd > 0) close (m_clientsocketfd);
		if (m_socketfd > 0) close (m_socketfd);
	}
	
}


void ServerSocket::StartServer()
{

	if (m_sp) {
		if (m_hasStartedServer) { //
			perror("Warning: Server is running!");
			return;
		}

		int domain = getStdDomain(m_sp->domain);
		int type = getStdType(m_sp -> type);
		int protocol = getStdProtocol(m_sp->protocol);

		//creating socket
		m_socketfd = socket(domain, type, protocol);
		assert(m_socketfd>2); // 0-stderr  1-stdin 2-stdout

		bzero((char*) &m_server_addr, sizeof(m_server_addr));
		m_server_addr.sin_family = domain;
		if (m_sp->serverIp.empty()) {
			m_server_addr.sin_addr.s_addr = INADDR_ANY;
		} else {
			int addrStatusCode = inet_aton(m_sp->serverIp.c_str(), &m_server_addr.sin_addr);
			if (addrStatusCode == 0) {
				fprintf(stderr, "%s\n", strerror(errno));
				fprintf(stdout, "invalid ip");
			}
		}
		m_server_addr.sin_port = htons(m_sp->serverPort);
		
		//bind serve
		int bindResusltStatus = bind(m_socketfd, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr));
		if (bindResusltStatus < 0) {
			fprintf(stderr, "Bind error: %s\n", strerror(errno));
		}
		assert(bindResusltStatus == 0);

		//listen socket
		int listenResultStatus = listen(m_socketfd, m_listenMax);
		if (listenResultStatus < 0) {
			fprintf(stderr, "Listen error: %s\n", strerror(errno));
		}
		assert(listenResultStatus == 0);

		m_hasStartedServer = true;

		//accept client socket
		socklen_t clientLen = sizeof(m_client_addr);
		 while (m_hasStartedServer &&
		 	   (m_clientsocketfd = accept(m_socketfd, (struct sockaddr*)&m_client_addr, &clientLen)) > 0) {
		 	//write(m_clientsocketfd, "server response", 15);
		 	char buffer[1024] = {0};
		 	int bytesRead = read(m_clientsocketfd, buffer, 1024);
		 	assert(bytesRead >= 0);
		 	printf("[Received]: %s\n", buffer);

		 	int bytesWrite = write(m_clientsocketfd, "message from server", 19);
		 	
		 }

		 if (m_hasStartedServer) { //server 异常
		 	fprintf(stderr, "%s\n", "Server Exceptioin.");
		 	StopServer();
		 }
	}
}


void ServerSocket::StopServer()
{
	if (m_hasStartedServer) {
		m_hasStartedServer = false;
		if (m_clientsocketfd > 0) close (m_clientsocketfd);
		if (m_socketfd > 0) close (m_socketfd);
		m_socketfd = -1;
		m_clientsocketfd = -1;
	}
}

void ServerSocket::ResetServerParam(std::unique_ptr<SocketParam>& sp)
{
	if (this->m_sp) {
		this->m_sp.reset(nullptr);
	}
	this->m_sp = std::move(sp);
	RestartServer(); 
}


void ServerSocket::RestartServer()
{
	StopServer();
	StartServer();
}


bool ServerSocket::IsServerRunning()
{
	if (m_hasStartedServer) {
		return true;
	}
	return false;
}

void ServerSocket::SetServerListenMax(int listenMax)
{
	this->m_listenMax = listenMax;
}

int ServerSocket::GetServerListenMax()
{
	return this->m_listenMax;
}