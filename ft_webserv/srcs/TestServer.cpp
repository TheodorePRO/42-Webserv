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
#include <vector> 
#include <istream>
#include <iterator> 

// ------ Constructor
SAMATHE::TestServer::TestServer(SAMATHE::ServConf &sc) : Server(sc)
{	// ------ le constructeur créé un e listeniong socket...
	std::cout << "==READY TO LAUNCH=="<< std::endl;
	initErrorMap();
	initContentMap();
	launch();
}

SAMATHE::TestServer::~TestServer()
{}

void SAMATHE::TestServer::accepter()
{
	// ------ 1ere fonction : RECEPTION depuis le client
	struct sockaddr_in address	= get_socket()->get_address();
	int addrlen					= sizeof(address);
	_new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&address, (socklen_t *)&addrlen);

	char				buffer[30000];
	int					ret;

	if (_new_socket > - 1 )
		std::cout << "Client accepted at ip :" << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl; 
	else
		perror("Failed to accept...");
	ret = ::recv(_new_socket, buffer, sizeof(buffer) - 1, 0);	// ------ appel système pour recevoir depuis le client
	if (ret < 1)
	{
		close(_new_socket);
		if (!ret)
			std::cout << "Connexion closed " << std::endl;
		else
			perror("Read error...");
	}
	_reception = std::string(buffer);	// ------ passse le message à la variable string de la classe
}

void SAMATHE::TestServer::handler()
{
	std::cout << "*** RECEIVED FROM CLIENT ***" << std::endl;
	std::cout << _reception << std::endl;
	std::cout << "*** END OF BUFFER ***" << std::endl;
}

void SAMATHE::TestServer::responder()
{
	// ------ Read request ans slash it into vector
	std::stringstream ssxx(_reception);
	std::istream_iterator<std::string> begin(ssxx);
	std::istream_iterator<std::string> end;
	std::vector<std::string> cut(begin, end);

	// ------ Get thge requested page
	if (cut.size() >= 3 && cut[0] == "GET")
	{
		_page = std::string("pages") + cut[1];
		if (cut[1] == "/")
			_page = "pages/index.html";
	}

	// ------ GET response content
	if (_response.setContent(_page) == 0)
	{
		_response.setContent(std::string("pages/404.html").c_str());
		_response.setCode("404");
	}

	// ------ Build response : header + content
	std::ostringstream oss;
	oss << "HTTP/1.1 " << _response.getCode() << _errors.find(_response.getCode())->second << "\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: "<< _contents[_response.getType()] << "\r\n";
	oss << "Content-Length: " << _response.getContent().size() << "\r\n";
	oss << "\r\n";

	oss << _response.getContent();
	std::string output = oss.str();
	int size = output.size() + 1;
	::send(_new_socket, output.c_str(), size, 0 );

	close(_new_socket);
}


void SAMATHE::TestServer::launch()
{
	while (true)
	{ // ------ boucle infinie qui fait Accept -> Handle -> Respond (Voir avec Mariys pour le select)
		std::cout << "========WAITING======="<< std::endl;
		accepter();
		handler();
		responder();
		std::cout << "========DONE========" << std::endl;
	}
}

void	SAMATHE::TestServer::initErrorMap()
{
	_errors["100"] = " Continue";
	_errors["200"] = " OK";
	_errors["201"] = " Created";
	_errors["204"] = " No Content";
	_errors["400"] = " Bad Request";
	_errors["403"] = " Forbidden";
	_errors["404"] = " Not Found";
	_errors["405"] = " Method Not Allowed";
	_errors["413"] = " Payload Too Large";
	_errors["500"] = " Internal Server Error";
 }

void	SAMATHE::TestServer::initContentMap()
{
	_contents["html"] = "text/html";
	_contents["png"] = "image/png";
	_contents["bmp"] = "image/bmp";
	_contents["css"] = "text/css";
	_contents["ico"]	= "image/vnd.microsoft.icon";
	_contents["jpg"]	= "image/jpeg";
	_contents["jpeg"]	= "image/jpeg";
	_contents["js"]	= "text/javascript";
	_contents["json"] = "application/json";
	_contents["ttf"]	= "font/ttf";
	_contents["txt"]	= "text/plain";
	_contents["woff"] = "font/woff";
	_contents["xml"]	= "text/xml";
	_contents["mp3"]	= "audio/mpeg";
	_contents["mpeg"] = "video/mpeg";
	_contents["m3u8"] = "application/vnd.apple.mpegurl";
	_contents["ts"]	= "video/mp2t";
}
