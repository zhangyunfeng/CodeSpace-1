
/**
**Auth: Ken
**/

#include <cassert>
#include <thread>
#include <fcntl.h>
#include <string.h>
#include "ClientSocket.hpp"


ClientSocket::ClientSocket(std::unique_ptr<SocketParam>& sp) 
{
    this->m_sp = std::move(sp);
    this->m_socketfd = -1;
    m_hasConnected = false;
}

ClientSocket::~ClientSocket()
{
    //auto release resource
    if (this->m_socketfd > 2) { //close socket
        close(this->m_socketfd);
    }
}


bool ClientSocket::Connect()
{
    if (m_hasConnected) {
        assert("Connection has been built.");
        return false;
    }

    if (m_sp) {
        int domain = getStdDomain(m_sp->domain);
        int type = getStdType(m_sp->type);
        int protocol = getStdProtocol(m_sp->protocol);

        m_socketfd = socket(domain, type, protocol);
        assert(m_socketfd > 0);
		
        bzero((char*)&m_server, sizeof(m_server));
        m_server.sin_family = domain;
        //memcpy((char*)&m_server.sin_addr, m_sp->serverIp.c_str(), m_sp->serverIp.length());
        //bcopy(inet_addr(m_sp->serverIp.c_str()), (char*)&m_server.sin_addr, m_sp->serverIp.length()); //server ip
        int addrStatusCode = inet_aton(m_sp->serverIp.c_str(), &m_server.sin_addr);
        if (addrStatusCode == 0) {
            fprintf(stderr, "%s\n", strerror(errno));
            fprintf(stdout, "invalid ip");
        }
        assert(addrStatusCode != 0);

        m_server.sin_port = htons(m_sp->serverPort); //server port

        int connectResult = connect(m_socketfd, (struct sockaddr*)&m_server, sizeof(m_server));
        if (connectResult < 0) { //connect failed
            fprintf(stderr, "%s\n", strerror(errno));
        }
        assert(connectResult == 0);
        m_hasConnected = true;
        return true;
    }
    return false;
}


void ClientSocket::Disconnect()
{
    if (m_hasConnected) {
        int closeResultCode = close(m_socketfd);
        if (closeResultCode == 0) { //close socket successed
            close(m_socketfd);
            m_hasConnected = false;
            m_socketfd = -1;
        } else {
            assert("close Connecting socket failed.");
            exit(-1);
        }
    }
}

void ClientSocket::ResetSocketParam(std::unique_ptr<SocketParam>& sp)
{
    if (m_hasConnected) {
        assert("Socket has been built. Please disconnect it first.");
        return;
    }

    if (this->m_sp) {
        this->m_sp.reset(nullptr);
    }
    this->m_sp = std::move(sp);
}


int ClientSocket::Send(const std::string& data)
{
    if (!m_hasConnected) {// not connecting socket
        assert("Did not connect a server socket. you cnan't send anything.");
        return 0;
    }
    //
    int writeResultCode = write(m_socketfd, data.c_str(), data.length());
    if (writeResultCode == -1) {
        perror(strerror(errno));
    }
#ifdef DEBUG
    fprintf(stdout, "Send %d bytes content.\n", writeResultCode);
#endif
    return writeResultCode;
}


std::string ClientSocket::Receive()
{
    if (!m_hasConnected) { // not connecting socket
        assert("Do not conenct to a server socket, you can't receive anything");
    }
    const int kBufferSize = 1024;
    std::string receivedData("");
    std::string retData("");
    char buffer[kBufferSize] = {0};
    while (true) {
        int readBytesCount = read(m_socketfd, buffer, kBufferSize);
#ifdef DEBUG
        std::cout << "readBytesCount: " << readBytesCount << std::endl;
#endif
        if (readBytesCount > 0) {
            receivedData.assign(buffer, readBytesCount);  //
            retData += receivedData;
            memset(buffer, 0, kBufferSize);
        }
        if (readBytesCount < kBufferSize) { //FIXME: 当readBytesCount 是kBufferSize的整数倍时，会阻塞 直到server disconnect
            break;
        }
    }
    return retData;
}

std::string ClientSocket::NoblockReceive()
{
    if (!m_hasConnected) { // not connecting socket
        assert("Do not conenct a server socket, you can't receive anything");
    }
    const int kBufferSize = 512;
    std::string receivedData("");
    char buffer[kBufferSize] = {0};
    int fdflags = 0;
    fdflags = fcntl(m_socketfd, F_GETFL, 0);
    fcntl(m_socketfd, F_SETFL, fdflags | O_NONBLOCK); //NONBLOCK
    int readBytesCount = read(m_socketfd, buffer, kBufferSize);
#ifdef DEBUG
    std::cout << "readBytesCount: " << readBytesCount << std::endl;
#endif
    
    if (readBytesCount > 0) {
        receivedData += receivedData.assign(buffer, readBytesCount);		
    }

    return receivedData;	
}

void ClientSocket::AsynReceive(HandleReceiveFuncPtr_T hfunc)
{
    std::unique_ptr<std::thread> newThread(new std::thread(hfunc));


    if (m_receiverThread) {
        this->m_receiverThread.reset(nullptr);
    } 

    this->m_receiverThread = std::move(newThread);
    this->m_receiverThread->join();
}

bool ClientSocket::IsSocketAlive()
{
    if (m_hasConnected) {
        return true;
    }
    return false;
}
