#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

namespace SAMATHE
{

	class Socket
	{
	private:
		// ------ Struct that contains info about the protocol
		struct sockaddr_in address;
		// ------ Address of Socket obj in the network
		int sock;
		int connection;

	public:
		// ------ Constructor
		Socket(int domain, int service, int protocol, int port, u_long interface);
		// ------ Virtual function to connect
		virtual void connect_to_network(int sock, struct sockaddr_in address) = 0;
		// ------ Test connexion
		void test_connection(int);
		// ------ Getters
		struct sockaddr_in	get_address();
		int					get_sock();
		int					get_connection();
		// ------ Setters
		void set_connection(int);
	};


}

#endif
