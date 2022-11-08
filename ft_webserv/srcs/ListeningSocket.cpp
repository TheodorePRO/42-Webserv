# include "../incs/network/ListeningSocket.hpp"


SAMATHE::ListeningSocket::ListeningSocket(SAMATHE::ServConf &sc) : BindSocket(sc.getDom(), sc.getSer(), sc.getProt(), sc.getPort(), sc.getInt())
{
	_sc = &sc;
	std::cout << "IN LISTENONG SOCKET"<< std::endl;
	// ------ Start listening
	start_listening();
	// ------ Confirm success
	test_connection (listening);
}

void	SAMATHE::ListeningSocket::start_listening()
{	listening = listen(get_sock(), _sc->getBkl());	}

// ------ Getters
int SAMATHE::ListeningSocket::get_listening()
{	return listening;			}

