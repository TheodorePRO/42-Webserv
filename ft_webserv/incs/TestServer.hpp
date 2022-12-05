
#ifndef TEST_SERVER_HPP
# define TEST_SERVER_HPP

#include <stdio.h>
#include <map>

#include "network/Server.hpp"
#include "Conf.hpp"
#include "ClientS.hpp"


namespace SAMATHE
{
	class ClientS;
	
	class TestServer: public Server
	{
		GlobalConfiguration					_glob_conf;
		//int					_new_socket;
		int									_max_fd;
		std::map<int, ClientS>				_client_sockets;
		std::map<std::string, std::string>	_errors;
		std::map<std::string, std::string>	_contents;


	public:
		TestServer(GlobalConfiguration &);
		~TestServer();

		void	accepter(int);
		void	initErrorMap();
		void	initContentMap();
		void	launch();

		GlobalConfiguration		getGConf()
		{	return _glob_conf;	}

		std::string		getError(std::string code)
		{	return (_errors.find(code)->second);	}

		std::string		getContents(std::string type)
		{	return (_contents.find(type)->second);	}

		
	};

}

#endif
