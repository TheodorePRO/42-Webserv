
#ifndef CLIENTS_HPP
# define CLIENTS_HPP


#include "Response.hpp"
#include "Reception.hpp"
#include "TestServer.hpp"
#include "webserv.hpp"
#include "cstdio"		// for remove

#include <string>
#include <unistd.h>


namespace SAMATHE
{
	enum{READ, WRITE, FINI};
	
	class TestServer;
	class Reception;
	class Response;

	class ClientS
	{
		int					_status; // 0 = READ - 1 = Write - 2 = fini ***** 
		int					_fd;
		size_t				_received;
		std::string			_justRecv;
		std::string			_page;
		std::string			_type;
		Reception			_reception;
		Response			_response;
		TestServer			*_serv;
		int					_binary;
		std::string			_output;
		size_t				_sent;
		ServerInParser		_server;
		ServerInParser		*_conf;

	public:
		ClientS();
		ClientS(int fd, ServerInParser *conf, TestServer *serv);
		~ClientS();
		void	checkPage();
		void	makeHeader();
		void	handler();
		void	responder();
		void	receiving();
		void	clearReception();
		void	sending();
		int		getStatus()
		{	return _status;	}
		int		getFd()
		{	return _fd;		}
		void	getServer();

	};

}

#endif
