#ifndef BINDSOCKET_HPP
# define BINDSOCKET_HPP

# include <stdio.h>
# include "Socket.hpp"

namespace SAMATHE
{
	class BindSocket : public Socket
	{
		// ------ To store 0 if success
		int		binding;
		// ------ Virtual fct from parent to bind
		void	connect_to_network(int sock, struct sockaddr_in address);

	public:
		// ------ Constructor
				BindSocket(int domain, int service, int protocol, int port, u_long interface);

		// ------ Getters
		int		get_binding();
	};

}

#endif

