
#ifndef CLIENTS_HPP
# define CLIENTS_HPP


#include "Response.hpp"
#include "Reception.hpp"
#include "TestServer.hpp"
#include "webserv.hpp"

#include <string>
#include <unistd.h>


namespace SAMATHE
{

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
		ServerInParser		_conf;

	public:
	//*********MS
		ClientS();
	//*********MS
		ClientS(int fd, ServerInParser _conf, TestServer *serv);
		~ClientS();
		void	checkPage();
		void	makeHeader();
		void	handler();
		void	responder();
		void	receiving();
		void	clearReception();

	//***********MS
		int	getStatus();

	};

}
#endif
