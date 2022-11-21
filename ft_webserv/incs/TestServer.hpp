
#ifndef TEST_SERVER_HPP
# define TEST_SERVER_HPP

#include <stdio.h>
#include <map>

#include "network/Server.hpp"
#include "Response.hpp"
#include "Conf.hpp"

namespace SAMATHE
{
	class TestServer: public SAMATHE::Server
	{
		std::string			_reception;
		int					_new_socket;
		std::string			_page;
		std::string			_type;
		SAMATHE::Response	_response;
		std::map<std::string, std::string>			_errors;
		std::map<std::string, std::string>	_contents;
//*MS*		
		fd_set              _master_set, _working_set;

		void accepter();
		void handler();
		void responder();
		void initErrorMap();
		void initContentMap();

	public:
		TestServer(SAMATHE::ServConf &sc);
		~TestServer();
		void launch();
	};

}

#endif
