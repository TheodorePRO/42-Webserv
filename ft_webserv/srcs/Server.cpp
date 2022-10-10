#include "../incs/network/Server.hpp"

SAMATHE::Server::Server(int domain, int service, int protocol, int port, u_long interface, int bklg)
{
	socket = new ListeningSocket(domain, service, protocol, port, interface, bklg);
}

SAMATHE::ListeningSocket *SAMATHE::get_socket()
{	return socket;		}
