# include "../incs/network/BindSocket.hpp"

// ------ Constructor
SAMATHE::BindSocket::BindSocket(int domain, int service, int protocol, int port, u_long interface) : Socket(domain, service, protocol, port, interface)
{
	std::cout << "in binding socket" << std::endl;
	int i = connect_to_network(get_sock(), get_address());
	std::cout << "in binding socket" << i << " ff " << get_connection() << std::endl;
	test_connection(binding);
}

// ------ Definition of connect_to_network virtual function
int			SAMATHE::BindSocket::connect_to_network(int sock, struct sockaddr_in address)
{
	//
	binding = bind(sock, (struct sockaddr *)&address, sizeof(address));
	return (binding);
}

// ------ Getters
int			SAMATHE::BindSocket::get_binding()
{	return binding;				}
