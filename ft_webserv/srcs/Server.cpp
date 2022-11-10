#include "../incs/network/Server.hpp"

SAMATHE::Server::Server(SAMATHE::ServConf &sc)
{
	
	std::cout << "IN SERVER CPP"<<std::endl;
	socket = new ListeningSocket(sc);
}

SAMATHE::ListeningSocket* SAMATHE::Server::get_socket()
{	return socket;		}
