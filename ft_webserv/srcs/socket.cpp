#include "../incs/network/Socket.hpp"
#include <stdlib.h>
#include <unistd.h>


// ------ Default contructor
SAMATHE::Socket::Socket(SAMATHE::ServConf &sc)
{
	// ------- Define address structure
	_address.sin_family			= sc.getDom();
	_address.sin_port			= htons(sc.getPort());
	_address.sin_addr.s_addr	= htonl(sc.getInt());

	// ------ Establish socket
	_sock = socket(sc.getDom(), sc.getSer(), sc.getProt());
	if (_sock == -1)
	{
		perror("Cann't establish socket!");
		exit(EXIT_FAILURE);
		return;
	}

/*
	// ------ Allow socket descriptor to be reuseable   
	int on = 1;
	int rc = setsockopt(_sock, SOL_SOCKET,  SO_REUSEADDR,
					(char *)&on, sizeof(on));
	test_connection(rc, "setsockopt() failed");
	// ------ Set socket to be nonblocking. All of the sockets for
#include <sys/ioctl.h>
	// the incoming connections will also be nonblocking since
	// they will inherit that state from the listening socket.
	rc = ioctl(listen_sd, FIONBIO, (char *)&on);
	test_connection(rc, "ioctl() failed");
*/
}


// ------- Test connexion
void SAMATHE::Socket::test_connection(int item_to_test, const char *str_error)
{
	if (item_to_test < 0)
	{	
		// ------ Connection is not established !
		perror(str_error);
		exit(EXIT_FAILURE);
	}
}

// ------ Getters
struct sockaddr_in	SAMATHE::Socket::get_address()
{	return _address;			}

int	SAMATHE::Socket::get_sock()
{	return _sock;			}
 

//*MS* quelle est la fonction de cette variable (_connection)
int	SAMATHE::Socket::get_connection()
{	return _connection;		}

// ------ Setters
void				SAMATHE::Socket::set_connection(int con)
{	_connection = con;		}
