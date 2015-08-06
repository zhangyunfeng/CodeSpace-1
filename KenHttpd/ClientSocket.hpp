/**
** ClientSocket Lib  
** @Auth: Ken
**/


#ifndef CLIENTSOCKET_HPP_
#define CLIENTSOCKET_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <memory>
#include <thread>
#include <utility>

#include "SocketCommon.hpp"


//client socket util
class ClientSocket
{
public:
	ClientSocket() = delete;
	~ClientSocket();

	ClientSocket(std::unique_ptr<SocketParam>& sp);

	//Connect
	bool Connect();
	
	//Disconnect()
	void Disconnect();

		//发送数据
	int Send(const std::string& data);

		//设置socket 参数， 
	void ResetSocketParam(std::unique_ptr<SocketParam>& sp);

		//接受数据
	std::string Receive(); 

	std::string NoblockReceive();

	//asyn receive data
	void AsynReceive(HandleReceiveFuncPtr_T hfunc);

	bool IsSocketAlive();
	
protected:
	
private:
	int m_socketfd;
	std::unique_ptr<SocketParam> m_sp;
	struct sockaddr_in m_server;
	bool m_hasConnected; // identfy whether connection has been built;

	std::unique_ptr<std::thread> m_receiverThread;
};




#endif
