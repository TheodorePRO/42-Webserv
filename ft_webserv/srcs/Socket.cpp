#include "../incs/network/Socket.hpp"
#include <stdlib.h>
#include <unistd.h>

namespace SAMATHE
{
	// ------ Default contructor
	Socket::Socket(ServerInParser &sc)
	{
		// ------- Define address structure
		_address.sin_family			= sc.getDomain(); 
		_address.sin_port			= sc.getPort_();
		_address.sin_addr.s_addr	= sc.getIP_();

		// ------ Establish socket
		_sock = socket(sc.getDomain(), sc.getService(), sc.getProto());
		if (_sock == -1)
		{
			perror("Cann't establish socket!");
			exit(EXIT_FAILURE);
			return;
		}

		// ------ Allow socket descriptor to be reuseable   
		int on = 1;
		int rc = setsockopt(_sock, SOL_SOCKET,  SO_REUSEADDR, (char *)&on, sizeof(on));
		test_connection(rc, "setsockopt() failed");

	}
	// ------- Test connexion
	void Socket::test_connection(int item_to_test, const char *str_error)
	{
		if (item_to_test < 0)
		{	
			// ------ Connection is not established !
			perror(str_error);
			exit(EXIT_FAILURE);
		}
	}

	// ------ Getters
	struct sockaddr_in	Socket::get_address()
	{	return _address;			}

	int	Socket::get_sock()
	{	return _sock;			}
	
	int	Socket::get_connection()
	{	return _connection;		}
	
	// ------ Setters
	void	Socket::set_connection(int con)
	{	_connection = con;		}
}
