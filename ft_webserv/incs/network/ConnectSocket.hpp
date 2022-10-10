#ifndef CONNECT_SOCKET_CPP
# define CONNECT_SOCKET_CPP

#include <stdio.h>
#include "Socket.hpp"

namespace SAMATHE
{
	class ConnectSocket : public Socket
	{
	public:
		// ------ Constructor
		ConnectSocket(int domain, int service, int port, u_long interface);
		void connect_to_network(int sock, struct sockaddr_in address);

	};

}


#endif
