
#ifndef TEST_SERVER_HPP
# define TEST_SERVER_HPP

#include <stdio.h>
#include <map>

#include "network/Server.hpp"
#include "Conf.hpp"
#include "ClientS.hpp"


namespace SAMATHE
{
	enum{READ, WRITE, FINI};

	class TestServer: public Server
	{
		GlobalConfiguration					_glob_conf;
		//int					_new_socket;
		int									_max_cld;
		std::map<int, ClientS>				_client_sockets;
		std::map<std::string, std::string>	_errors;
		std::map<std::string, std::string>	_contents;


	public:
		void	accepter(int);
		void	initErrorMap();
		void	initContentMap();

		TestServer(GlobalConfiguration &);
		~TestServer();
		std::string		getError(std::string code);
		std::string		getContents(std::string type);

		void launch();
	};

}

#endif
