#ifndef BINDSOCKET_HPP
# define BINDSOCKET_HPP

# include <stdio.h>
# include "Socket.hpp"
#include "../Conf.hpp"

namespace SAMATHE
{
	class BindSocket : public Socket
	{
		// ------ To store 0 if success
		int		_binding;
		// ------ Virtual fct from parent to bind
		int		connect_to_network(int sock, struct sockaddr_in address);

	public:
		// ------ Constructor
				BindSocket(ServerInParser &sc);
				~BindSocket(){};

		// ------ Getters
		int		get_binding();
	};

}

#endif

