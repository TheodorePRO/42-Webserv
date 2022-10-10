#ifndef SERVER_HPP
# define SERVER_HPP

#include <stdio.h>
#include "ListeningSocket.hpp"

namespace SAMATHE
{
	class Server
	{
	private:
		ListeningSocket *socket;
		virtual void	accepter() = 0;
		virtual void	handler() = 0;
		virtual void	responder() = 0;

	public:
		Server(int domain, int service, int protocol, int port, u_long interface, int bklg);
		virtual void launch() = 0;
		ListeningSocket *get_socket();
	};

}

#endif
