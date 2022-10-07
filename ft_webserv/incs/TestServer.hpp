
#ifndef TEST_SERVER_HPP
# define TEST_SERVER_HPP

#include <stdio.h>
#include "network/Server.hpp"

namespace SAMATHE
{
	class TestServer: public SAMATHE::Server
	{
		char buffer[30000] = {0};
		int new_socket;

		void accepter();
		void handler();
		void responder();

	public:
		TestServer();
		void launch();
	};

}

#endif
