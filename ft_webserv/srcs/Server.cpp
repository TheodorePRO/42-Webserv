#include "../incs/network/Server.hpp"

SAMATHE::Server::Server(int domain, int service, int protocol, int port, u_long interface, int bklg)
{
	
	std::cout << "IN SERVER CPP"<<std::endl;
	socket = new ListeningSocket(domain, service, protocol, port, interface, bklg);
}

SAMATHE::ListeningSocket* SAMATHE::Server::get_socket()
{	return socket;		}
