# include "../incs/network/ListeningSocket.hpp"

namespace SAMATHE
{
	ListeningSocket::ListeningSocket(ServerInParser &sc) : BindSocket(sc)
	{
	//	_sc = &sc;
		std::cout << "IN LISTENING SOCKET"<< std::endl;
		// ------ Start listening
		start_listening(sc.getBklg());
		// ------ Confirm success
		test_connection (_listening, "Listening error!");
	}

	// ------ Tells the number of simultaneous connections
	void	ListeningSocket::start_listening(int bkl)
	{	_listening = listen(get_sock(), bkl);	}  // N listening socket

	// ------ Getters
	int ListeningSocket::get_listening()
	{	return _listening;			}
}
