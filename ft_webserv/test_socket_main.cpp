#include "incs/network/ListeningSocket.hpp"
#include "incs/network/Server.hpp"
#include <stdio.h>

// Test Socket
int main()
{
	std::cout << "Starting..." << std::endl;
	std::cout << "Binding Socket..." << std::endl;
	SAMATHE::BindSocket(AF_INET, SOCK_STREAM, 0 ,81, INADDR_ANY);
	std::cout << "Listening Socket..." << std::endl;
	SAMATHE::ListeningSocket(AF_INET, SOCK_STREAM, 0 ,80, INADDR_ANY, 10);
	std::cout << "Success!" << std::endl;
}



