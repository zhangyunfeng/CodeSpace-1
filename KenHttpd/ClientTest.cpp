#include "ClientSocket.hpp"
#include "ServerSocket.hpp"
//#include "ServerSocket.hpp"


int main(void)
{
	std::cout << "hello world" << std::endl;

	std::unique_ptr<SocketParam> sp(new SocketParam("0.0.0.0", 9999, Domain::INET, Type::STREAM, Protocol::DEFAULT));
	ClientSocket cs(sp);
	cs.Connect();
	cs.Send("message from Ken");

	while (true) {
		std::string rd = cs.Receive();
		std::cout << "received data: " << rd << std::endl;		
	}

	//getchar();

	//ServerSocket ss(sp);
	//ss.StartServer();

	return 0;
}
