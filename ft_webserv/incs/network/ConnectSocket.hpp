#ifndef CONNECT_SOCKET_CPP
# define CONNECT_SOCKET_CPP

#include <stdio.h>
#include "Socket.hpp"
#include "../Conf.hpp"

namespace SAMATHE
{
	class ConnectSocket : public Socket
	{
	public:
		// ------ Constructor
		ConnectSocket(SAMATHE::ServConf &sc);
		int connect_to_network(int sock, struct sockaddr_in address);

	};

}


#endif
