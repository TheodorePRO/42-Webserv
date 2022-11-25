#include "../incs/TestServer.hpp"
#include "../incs/Conf.hpp"
#include <unistd.h>
#include <string>
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


	if (_new_socket > - 1 )
		std::cout << "Client accepted at ip :" << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl; 
	else
		perror("Failed to accept...");
}

void	SAMATHE::TestServer::receiving()
	{
	char				buffer[30000] = {0}; 
	int					ret;
	// ------ appel système pour recevoir depuis le client
	ret = ::recv(_new_socket, buffer, sizeof(buffer), 0);
	if (ret == 0 || ret == -1)
	{
		close(_new_socket);
		if (!ret)
			std::cout << "\rConnection was closed by client.\n" << std::endl;
		else
			std::cout << "\rRead error, closing connection.\n" << std::endl;
		return;
	}
	_received += ret;
	_justRecv += std::string(buffer);
	size_t	i = _justRecv.find("\r\n\r\n");
	if (i != std::string::npos)
	{
		if (_justRecv.find("Content-Length: ") == std::string::npos)
		{
			if (_justRecv.find("Transfer-Encoding: chunked") != std::string::npos)
			{
				if (_justRecv.find("0\r\n\r\n") == _justRecv.size() - 6)
				{
					handler();
					_status = 1;
	  std::cout << "A   *vvvvvvvvvvvvvvvvv***" << std::endl;
					return;
				}
				else
				{
	  std::cout << "B   *vvvvvvvvvvvvvvvvv***" << std::endl;
					return;}
			}
			else
			{
				handler();
				_status = 1;
	  std::cout << "C   *vvvvvvvvvvvvvvvvv***" << std::endl;
				return;
			}
		}
		size_t	len = std::atoi(_justRecv.substr(_justRecv.find("Content-Length: ") + 16, 10).c_str());
	  std::cout << "*vvvvvvvvvvvvvvvvv*** content len = "<< len << "--- reception = " << _justRecv.size() << "--- i= "<< i << std::endl;
		if (_justRecv.size() >= len + i + 4)
		{
	  std::cout << "D   *vvvvvvvvvvvvvvvvv***" << std::endl;
			handler();
			_status = 1;
			return;
		}
	std::cout << "E   *vvvvvvvvvvvvvvvvv***"<< std::endl;
		_justRecv.substr(0, _justRecv.find(std::string("\r\n\r\n") )) << std::endl;
		receiving(); // SELECT DOES THAT ///////////////////////////////
	//		handler();
	//		_status = 1;
	}
}

void SAMATHE::TestServer::handler()
{
	// ------ Read request and slash it into vector
	std::stringstream ssxx(_justRecv);
	std::istream_iterator<std::string> begin(ssxx);
	std::istream_iterator<std::string> end;
	std::vector<std::string> cut(begin, end);
		std::cout << "uuuuuuuuuuuuu  1 "<< _reception.getSize() << std::endl;
	_reception.setReception(cut);
		std::cout << "uuuuuuuuuuuuu  1 "<< _reception.getSize() << std::endl;
}

void SAMATHE::TestServer::responder()
{
	// ------ GET response content
	if (_reception.getMethod() == "GET")
	{
		if (_response.setContent(std::string("pages/").c_str() + _reception.getPage()) == 0)
		{
			_response.setContent(std::string("pages/404.html").c_str());
			_response.setCode("404");
		}

		// ------ Build response : header + content
		std::ostringstream oss;
		oss << _reception.getVersion() << " " << _response.getCode() << _errors.find(_response.getCode())->second << "\r\n";
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
	else if (_reception.getMethod() == "POST")
	{
		std::cout << "*** CREATING FILE ***" << std::endl;
		_reception.setBody(_justRecv);
//		std::ofstream(_reception.getFName()) << _reception.getBody().c_str();
		std::ofstream file(_reception.getFName());
		file << _reception.getBody().c_str();
	}

	_reception.clearReception();
	_received = 0;
	_justRecv = "";
	_status = 1;		// to change to 2 ???? depends on select
}

void SAMATHE::TestServer::launch()
{
	while (true)
	{ // ------ boucle infinie qui fait Accept . Handle . Respond (Voir avec Mariys pour le select)
		std::cout << "========WAITING======="<< std::endl;
		accepter();
		receiving();
	//	handler();  // called in receiving
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
