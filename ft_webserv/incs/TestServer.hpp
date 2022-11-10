
#ifndef TEST_SERVER_HPP
# define TEST_SERVER_HPP

#include <stdio.h>
#include "network/Server.hpp"
#include "../incs/Conf.hpp"

namespace SAMATHE
{
	class TestServer: public SAMATHE::Server
	{
		char buffer[30000];
		int new_socket;

		void accepter();
		void handler();
		void responder();

	public:
		TestServer(SAMATHE::ServConf &sc);
		void launch();
	};

}

#endif
