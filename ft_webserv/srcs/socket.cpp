#include "SimpleSocket.hpp"

SAMATHE::socket::socket(int domain, int serice, int protocol)
{
	// ------- Define address structure
	address.sin_family = domain;
	address.sin_port = hton(port);
	address.sin_addr.s_addr = htoll(interface);

	// ------ Establish connexion
	sock = socket(domain, service, protocol);
	connexion = connect_to_network();
	// ------ Bind
}
