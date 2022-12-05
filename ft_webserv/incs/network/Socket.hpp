#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "../webserv.hpp"



namespace SAMATHE
{

	class Socket
	{
	private:
		// ------ Struct that contains info about the protocol
		struct sockaddr_in _address;
		// ------ Address of Socket obj in the network
		int _sock;
		int _connection;

	public:
		// ------ Constructor
		Socket(ServerInParser &sc);
		virtual		~Socket(){};
		// ------ Virtual function to connect
		virtual int	connect_to_network(int sock, struct sockaddr_in address) = 0;
		// ------ Test connexion
		void		test_connection(int, const char *);
		// ------ Getters
		struct sockaddr_in	get_address();
		int					get_sock();
		int					get_connection();
		// ------ Setters
		void set_connection(int);
	};


}

#endif
