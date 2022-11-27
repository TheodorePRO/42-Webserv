
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
	enum{READ, WRITE, FINI};

	class TestServer: public Server
	{
		GlobalConfiguration _glob_conf;
		//int					_new_socket;
		int 				_max_cld;
		int					_status; // 0 = READ - 1 = Write - 2 = fini ***** 
		size_t				_received;
		std::string			_justRecv;


		std::string			_page;
		std::string			_type;

		Reception			_reception;
		Response			_response;

		//std::vector<int>	_client_sockets;
		std::map<int, Reception> _client_sockets;

		std::map<std::string, std::string>	_errors;
		std::map<std::string, std::string>	_contents;
		


	public:
		void	accepter(int);
		void	handler(int);
		void	responder(int);
		void	initErrorMap();
		void	initContentMap();
		void	receiving(int sd);

		TestServer(GlobalConfiguration &);
		~TestServer();
		void launch();
		void	clearReception()
		{
		}
	};

}

#endif