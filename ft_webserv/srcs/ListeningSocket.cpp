# include "../incs/network/ListeningSocket.hpp"

namespace SAMATHE
{
	ListeningSocket::ListeningSocket(conf_server &sc) : BindSocket(sc)
	{
	//	_sc = &sc;
		std::cout << "IN LISTENONG SOCKET"<< std::endl;
		// ------ Start listening
		start_listening(sc._bklg);
		// ------ Confirm success
		test_connection (_listening, "Listening error!");
	}

	// ------ Tells the number of simultaneous connections
	void	ListeningSocket::start_listening(int bkl)
	{	_listening = listen(get_sock(), bkl);	}

	// ------ Getters
	int ListeningSocket::get_listening()
	{	return _listening;			}
}
