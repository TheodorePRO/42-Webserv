#include "../incs/network/Socket.hpp"

// ------ Default contructor
SAMATHE::Socket::Socket(int domain, int service, int protocol, int port, u_long interface)
{
	// ------- Define address structure
	address.sin_family= domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);

	// ------ Establish socket
	sock = socket(domain, service, protocol);
	
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
{	return address;			}

int	SAMATHE::Socket::get_sock()
{	return sock;			}

int	SAMATHE::Socket::get_connection()
{	return connection;		}

// ------ Setters
void				SAMATHE::Socket::set_connection(int con)
{	connection = con;		}
