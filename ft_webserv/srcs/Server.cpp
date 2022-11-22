#include "../incs/network/Server.hpp"

SAMATHE::Server::Server(SAMATHE::ServConf &sc)
{
	std::cout << "IN SERVER CPP"<<std::endl;
	_max_sd = 0;
    FD_ZERO(&_master_set);
    FD_ZERO(&_writeMaster_set);

	for(int i=0; i < sc.getNumConfServs(); ++i){
		ListeningSocket ls = ListeningSocket(sc.getConfServ(i));
		_sockets.push_back(ls);
    	
		int sd = ls.get_sock();
		FD_SET(sd, &_master_set);

		if (sd > _max_sd) {
			_max_sd = sd;
		}
	}
	// Le constructeur du serveur créé une "listeningSocket qui est une socket ->bindée et -> qui listen.
}

SAMATHE::Server::~ Server(){}

SAMATHE::ListeningSocket& SAMATHE::Server::get_socket(int i)
{	return _sockets[i];		}
