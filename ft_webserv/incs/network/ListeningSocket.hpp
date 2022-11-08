#ifndef LISTENING_SOCKET
# define LISTENING_SOCKET

#include <stdio.h>
#include "BindSocket.hpp"
#include "../Conf.hpp"

namespace SAMATHE
{
	class ListeningSocket :public BindSocket
	{
		SAMATHE::ServConf *_sc;
		int listening;

	public:
		// ------ Constructor
		ListeningSocket(SAMATHE::ServConf &sc);

		// ------ Operations
		void start_listening();
		int get_listening();
	};

}

#endif
