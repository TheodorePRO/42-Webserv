#include "../incs/network/Socket.hpp"
#include <stdlib.h>



// ------ Default contructor
SAMATHE::Socket::Socket(int domain, int service, int protocol, int port, u_long interface)
{
	// ------- Define address structure
	_address.sin_family= domain;
	_address.sin_port = htons(port);
	_address.sin_addr.s_addr = htonl(interface);

	// ------ Establish socket
	_sock = socket(domain, service, protocol);
	
}

// ------- Test connexion
void SAMATHE::Socket::test_connection(int item_to_test)
{
	if (item_to_test < 0)
	{	// ------ Connection established ?
		perror("Failed to connect...");
		exit(EXIT_FAILURE);
	}
}

// ------ Getters
struct sockaddr_in	SAMATHE::Socket::get_address()
{	return _address;			}

int	SAMATHE::Socket::get_sock()
{	return _sock;			}

int	SAMATHE::Socket::get_connection()
{	return _connection;		}

// ------ Setters
void				SAMATHE::Socket::set_connection(int con)
{	_connection = con;		}
