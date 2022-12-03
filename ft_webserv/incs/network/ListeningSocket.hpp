#ifndef LISTENING_SOCKET
# define LISTENING_SOCKET

#include <stdio.h>
#include "BindSocket.hpp"
#include "../webserv.hpp"

namespace SAMATHE
{
	class ListeningSocket :public BindSocket
	{
	//	SAMATHE::ServConf	*_sc;
		int					_listening;

	public:
		// ------ Constructor
		ListeningSocket(ServerInParser &sc);
		~ListeningSocket(){};

		// ------ Operations
		void start_listening(int bkl);
		int get_listening();
	};

}

#endif
