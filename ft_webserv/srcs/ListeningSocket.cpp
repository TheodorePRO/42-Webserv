# include "../incs/network/ListeningSocket.hpp"


SAMATHE::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg) : BindSocket(domain, service, protocol, port, interface)
{
	// ------ Set Backlog variable
	backlog = bklg;
	// ------ Start listening
	start_listening();
	// ------ Confirm success
	test_connection (listening);
}

void	SAMATHE::ListeningSocket::start_listening()
{	listening = listen(get_sock(), backlog);	}

// ------ Getters
int SAMATHE::ListeningSocket::get_listening()
{	return listening;			}

int SAMATHE::ListeningSocket::get_backlog()
{	return backlog;			}
