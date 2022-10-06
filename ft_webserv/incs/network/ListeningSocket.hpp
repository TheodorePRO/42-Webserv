#include <stdio.h>
#include "BindSocket.hpp"

namespace SAMATHE
{
	class ListeningSocket :public BindSocket
	{
		int backlog;
		int listening;

	public:
		// ------ Constructor
		ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg);
		void start_listening();
		int get_listening();
		int get_backlog();
	};

}
