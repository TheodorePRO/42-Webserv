#ifndef SERVER_HPP
# define SERVER_HPP

#include <stdio.h>
#include "ListeningSocket.hpp"
#include "../Conf.hpp"
#include <sys/socket.h>
#include <vector>


namespace SAMATHE
{
	class Server
	{
	private:
		std::vector<ListeningSocket>		_sockets;
		int									_max_sd;
		fd_set                              _master_set;
        fd_set                              _writeMaster_set;


		virtual void	accepter(int) = 0;
		virtual void	handler() = 0;
		virtual void	responder() = 0;

	public:
		Server(SAMATHE::ServConf &sc);
		virtual ~Server();
		virtual void launch() = 0;
		
		ListeningSocket& get_socket(int i);
	};

}

#endif
