#ifndef WSERV_HPP
#define WSERV_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace SAMATHE
{

	class socket
	{
	private:
		struct sockaddr_in address;
		int connexion;
	public:
		socket(int domain, int service, int protocol, int port, u_long interface);
		virtual void connect_net_conn() = 0;
	};


}


#endif
