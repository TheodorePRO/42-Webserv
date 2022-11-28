# include "../incs/network/BindSocket.hpp"
#include "../incs/Conf.hpp"

namespace SAMATHE
{
// ------ Constructor
	BindSocket::BindSocket(ServerInParser &sc) : Socket(sc)
	{
		std::cout << "in binding socket" << std::endl;

		connect_to_network(get_sock(), get_address());
		test_connection(_binding, "Binding error");

	}

	// ------ Definition of connect_to_network virtual function
	int		BindSocket::connect_to_network(int sock, struct sockaddr_in address)
	{
		//
		_binding = bind(sock, (const struct sockaddr *)&address, sizeof(address));
		return _binding;
	}

	// ------ Getters
	int		BindSocket::get_binding()
	{	return _binding;}
}