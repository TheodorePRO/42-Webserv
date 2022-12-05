#ifndef SERVER_HPP
# define SERVER_HPP

#include <stdio.h>
#include "ListeningSocket.hpp"
#include "../webserv.hpp"
#include <sys/socket.h>
#include <vector>


namespace SAMATHE
{
	class Server
	{
	private:
		std::vector<ListeningSocket>		_sockets; //?map parsing congig
		int									_max_sd;
		fd_set                              _master_set; // for read
        fd_set                              _writeMaster_set; //for write

		virtual void	accepter(int) = 0;

	public:
		Server(GlobalConfiguration &sc);
		virtual ~Server();
		virtual void launch() = 0;
		ListeningSocket& get_socket(int i);
		int	get_max_sd() {return _max_sd;}
		fd_set*	get_master_set() {return &_master_set;}
		fd_set*	get_writeMaster_set() {return &_writeMaster_set;}
		int	get_N_sockets() {return _sockets.size();}
	};

}

#endif
