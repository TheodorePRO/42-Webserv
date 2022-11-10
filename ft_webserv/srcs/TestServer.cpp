#include "../incs/TestServer.hpp"
#include "../incs/Conf.hpp"
#include <unistd.h>

// ------ Constructor
SAMATHE::TestServer::TestServer(SAMATHE::ServConf &sc) : Server(sc)
{
	std::cout << "==READY TO LAUNCH=="<< std::endl;
	launch();
}


void SAMATHE::TestServer::accepter()
{
	struct sockaddr_in address = get_socket()->get_address();
	
	int addrlen = sizeof(address);

	new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&address, (socklen_t *)&addrlen);
	read(new_socket, buffer, 30000);
}

void SAMATHE::TestServer::handler()
{
	std::cout << "*** RECEIVED FROM CLIENT ***" << std::endl;
	std::cout << 	buffer << std::endl;
	std::cout << "*** END OF BUFFER ***" << std::endl;
}

void SAMATHE::TestServer::responder()
{
	char *hello = (char *)"Hello from server";
	write(new_socket, hello, strlen(hello));
	close(new_socket);
}

void SAMATHE::TestServer::launch()
{
	while (true)
	{
		std::cout << "========WAITING======="<< std::endl;
		accepter();
		handler();
		responder();
		std::cout << "========DONE========" << std::endl;
	}
}
