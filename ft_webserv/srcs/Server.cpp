#include "../incs/network/Server.hpp"

SAMATHE::Server::Server(SAMATHE::ServConf &sc)
{
	
	std::cout << "IN SERVER CPP"<<std::endl;
//(void)sc;

	_socket = new ListeningSocket(sc);
	// Le constructeur du serveur créé une "listeningSocket qui est une socket ->bindée et -> qui listen.
}

SAMATHE::ListeningSocket* SAMATHE::Server::get_socket()
{	return _socket;		}
