# include "../incs/network/ConnectSocket.hpp"

// ------ Constructor
SAMATHE::ConnectSocket::ConnectSocket(SAMATHE::ServConf &sc) : Socket(sc)
{
	set_connection(connect_to_network(get_sock(), get_address()));
	test_connection(get_connection());
}

// ------ Definition of connect_to_network virtual function
int SAMATHE::ConnectSocket::connect_to_network(int sock, struct sockaddr_in address)
{
	return (connect(sock, (struct sockaddr *)&address, sizeof(address)));
}

