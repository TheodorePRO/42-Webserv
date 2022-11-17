#include "../incs/TestServer.hpp"
#include "../incs/Conf.hpp"
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <iostream>				// for open
#include <fstream>				// for open
#include <sstream>				// for open
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// ------ Constructor
SAMATHE::TestServer::TestServer(SAMATHE::ServConf &sc) : Server(sc)
{
	std::cout << "==READY TO LAUNCH=="<< std::endl;
	launch();
}

void SAMATHE::TestServer::accepter()
{
//---------     CA
	struct sockaddr_in address	= get_socket()->get_address();
	int addrlen					= sizeof(address);
	_new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&address, (socklen_t *)&addrlen);
//-----------	OU CA
//	struct	sockaddr_in csin;
//	unsigned int		cslen;
//	_new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&csin, &cslen);
//____________

	char				buffer[30000];
	int					ret;

	if (_new_socket > - 1 )
	{	
		std::cout << "Client accepted at ip :" << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl; 
//		std::cout << "Client accepted at ip :" << inet_ntoa(csin.sin_addr) << ":" << ntohs(csin.sin_port) << std::endl;
	}
	else
		perror("Failed to accept...");
	ret = ::recv(_new_socket, buffer, sizeof(buffer) - 1, 0);
	if (ret < 1)
	{
		close(_new_socket);
		if (!ret)
			std::cout << "Connexion closed " << std::endl;
		else
			perror("Read error...");
	}
	_reception = std::string(buffer);
}

void SAMATHE::TestServer::handler()
{
	std::cout << "*** RECEIVED FROM CLIENT ***" << std::endl;
	std::cout << _reception << std::endl;
	std::cout << "*** END OF BUFFER ***" << std::endl;
	_page = _reception.substr(_reception.find("GET") + 4 , (_reception.find("HTTP") - _reception.find("GET") - 5));
	std::cout <<"-"<< _page<<"-" << std::endl;
}

void SAMATHE::TestServer::responder()
{
	// ------ Read html
	std::ifstream		file;
	std::stringstream	buf;
	std::string			p;
	if (_page == "/")
		_page = "pages/index.html";
	else
		_page.insert(0, "pages");
	file.open(_page.c_str(), std::ifstream::in);
	if (file.is_open() == false)
		buf << "<!Doctype html>\n<html><title>40404</title><body>there was an error finding your page</body></html>\n";
	else
		buf << file.rdbuf();
	file.close();

	// ----- Send back
	//::send(_new_socket, buf.str().c_str(), buf.str().size(), 0);
	write(_new_socket, buf.str().c_str(), buf.str().size());

//---------------- TEST DESTINATION
	struct sockaddr_in address	= get_socket()->get_address();
	std::cout << "Address :" << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl;
//------------------------------
	close(_new_socket);

	std::cout << _page << std::endl;
}

void SAMATHE::TestServer::launch()
{
	while (true)
	{
		std::cout << "========WAITING======="<< std::endl;
		accepter();
		handler();
		responder();
		std::cout << "========DONE========" << std::endl;
	}
}
