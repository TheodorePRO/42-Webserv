#ifndef SERVER_HPP
# define SERVER_HPP

#include <stdio.h>
#include "ListeningSocket.hpp"
#include "../Conf.hpp"
#include <sys/socket.h>


namespace SAMATHE
{
	class Server
	{
	private:
		ListeningSocket		*_socket;

		virtual void	accepter() = 0;
		virtual void	handler() = 0;
		virtual void	responder() = 0;

	public:
		Server(SAMATHE::ServConf &sc);
		virtual void launch() = 0;
		ListeningSocket *get_socket();
	};

}

#endif
