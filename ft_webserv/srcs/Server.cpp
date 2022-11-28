#include "../incs/network/Server.hpp"

namespace SAMATHE{

	Server::Server(GlobalConfiguration &glob_conf)
	{
		std::cout << "IN SERVER CPP"<<std::endl;
		_max_sd = 0;
		FD_ZERO(&_master_set);
		FD_ZERO(&_writeMaster_set);

		for ( unsigned int i = 0; i < glob_conf.getServersList().size(); i++)
		{
			ListeningSocket ls = ListeningSocket(glob_conf.getServersList().at(i));
			_sockets.push_back(ls);	
			int sd = ls.get_sock();
			FD_SET(sd, &_master_set);

			if (sd > _max_sd) {
				_max_sd = sd;
			}
		}
		// Le constructeur du serveur créé une "listeningSocket qui est une socket ->bindée et -> qui listen.
	}

	Server::~ Server(){}

	ListeningSocket& Server::get_socket(int i)
	{	return _sockets[i];		}

}