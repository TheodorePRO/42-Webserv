
#ifndef TEST_SERVER_HPP
# define TEST_SERVER_HPP

#include <stdio.h>
#include <map>

#include "network/Server.hpp"
#include "Response.hpp"
#include "Reception.hpp"
#include "Conf.hpp"

#define RECVSIZE 10240

namespace SAMATHE
{
	class TestServer: public SAMATHE::Server
	{
		int					_new_socket;
		int					_status; // 0 = READ - 1 = Write - 2 = fini
		size_t				_received;
		std::string			_justRecv;


		std::string			_page;
		std::string			_type;

		SAMATHE::Reception	_reception;
		SAMATHE::Response	_response;
		std::map<std::string, std::string>			_errors;
		std::map<std::string, std::string>	_contents;

	public:
		void	accepter();
		void	handler();
		void	responder();
		void	initErrorMap();
		void	initContentMap();
		void	receiving();

		TestServer(SAMATHE::ServConf &sc);
		~TestServer();
		void launch();
		void	clearReception()
		{
		}
	};

}

#endif
