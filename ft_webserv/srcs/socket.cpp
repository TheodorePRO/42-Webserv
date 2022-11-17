#include "../incs/network/Socket.hpp"
#include <stdlib.h>



// ------ Default contructor
SAMATHE::Socket::Socket(SAMATHE::ServConf &sc)
{
	// ------- Define address structure
	_address.sin_family			= sc.getDom();
	_address.sin_port			= htons(sc.getPort());
	_address.sin_addr.s_addr	= htonl(sc.getInt());

	// ------ Establish socket
	_sock = socket(sc.getDom(), sc.getSer(), sc.getProt());
	
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
