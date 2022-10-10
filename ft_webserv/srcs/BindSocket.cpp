# include "../incs/network/BindSocket.hpp"

// ------ Constructor
SAMATHE::BindSocket::BindSocket(int domain, int service, int protocol, int port, u_long interface) : Socket(domain, service, protocol, port, interface)
{
	connect_to_network(get_sock(), get_address());
	test_connection(get_connection());
//	test_connection(listening);
}

// ------ Definition of connect_to_network virtual function
void			SAMATHE::BindSocket::connect_to_network(int sock, struct sockaddr_in address)
{
	//
	binding = bind(sock, (struct sockaddr *)&address, sizeof(address));
}

// ------ Getters
int			SAMATHE::BindSocket::get_binding()
{	return binding;				}
