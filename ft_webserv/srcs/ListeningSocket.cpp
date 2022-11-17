# include "../incs/network/ListeningSocket.hpp"


SAMATHE::ListeningSocket::ListeningSocket(SAMATHE::ServConf &sc) : BindSocket(sc)
{
//	_sc = &sc;
	std::cout << "IN LISTENONG SOCKET"<< std::endl;
	// ------ Start listening
	start_listening(sc.getBkl());
	// ------ Confirm success
	test_connection (_listening);
}

// ------ Tells the number of simultaneous connections
void	SAMATHE::ListeningSocket::start_listening(int bkl)
{	_listening = listen(get_sock(), bkl);	}

// ------ Getters
int SAMATHE::ListeningSocket::get_listening()
{	return _listening;			}

