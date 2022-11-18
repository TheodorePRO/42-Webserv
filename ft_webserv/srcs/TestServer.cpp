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
{ // ------ 1ere fonction : RECEPTION depuis le client
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
	// ------ Read html
	std::stringstream ssxx(_reception);
	std::istream_iterator<std::string> begin(ssxx);
	std::istream_iterator<std::string> end;
	std::vector<std::string> cut(begin, end);
//	_page = _reception.substr(_reception.find("GET") + 4 , (_reception.find("HTTP") - _reception.find("GET") - 5));

	_response.setContent("<h1>404 Not Found</h1>");
	_page = "pages/404.html";
	_response.setCode("404");

	if (cut.size() >= 3 && cut[0] == "GET")
	{
		_page = std::string("pages") + cut[1];
		if (cut[1] == "/")
			_page = "pages/index.html";
	}

	std::ifstream		file(_page.c_str());
	if (file.good())
	{
		std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		_response.setContent(str);
		_response.setCode("200");
	}
	file.close();
	_response.setType(_contents[_page.substr(_page.find(".") + 1)]);


	std::ostringstream oss;
	oss << "HTTP/1.1 " << _response.getCode() << _errors.find(_response.getCode())->second << "\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: "<< _response.getType() << "\r\n";
	oss << "Content-Length: " << _response.getContent().size() << "\r\n";
	oss << "\r\n";
	oss << _response.getContent();

	std::string output = oss.str();
	int size = output.size() + 1;

	::send(_new_socket, output.c_str(), size, 0 );

/*	if (_page == "/")
		_page = "pages/index.html";
	else
		_page.insert(0, "pages");
	std::ifstream		file;
	std::stringstream	buf;
	file.open(_page.c_str(), std::ifstream::in);
	if (file.is_open() == false)
	{
		_response.setCode("404");
		_response.setType("text/html");
		buf << "<!Doctype html>\n<html><title>40404</title><body>there was an error finding your page</body></html>\n";
	}
	else
	{
		_response.setCode("200");
		_response.setType(_contents[_page.substr(_page.find(".") + 1)]);
		buf << file.rdbuf();
	}
	file.close();



	// ----- Send back
	//::send(_new_socket, buf.str().c_str(), buf.str().size(), 0);
	std::stringstream ss;
	ss << buf.str().size();
	_response.setHeader(std::string("HTTP/1.1 ") + _response.getCode() + _errors.find(_response.getCode())->second + std::string("\r\n") + std::string("Cache-Control: no-cache, private\r\nContent-Type: ") + _response.getType() + std::string("\r\nContent-Length: ") + ss.str() + std::string("\r\n\r\n"));
write(_new_socket, _response.getHeader().c_str(), sizeof(_response.getHeader().c_str()) +1);
	write(_new_socket, buf.str().c_str(), buf.str().size()+1);

	
	std::ostringstream	oss;
	oss << "HTTP/1.1 200 OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: 14\r\n";
	oss << "\r\n";
	oss << "<h1>hello</h1>";

	std::string output = oss.str();
//	int size = output.size() + 1;
//	write(_new_socket, output.c_str(), size);

	std::cout <<"--------------------"<< std::endl;
	std::cout << _response.getHeader() << std::endl;
	std::cout << _page << std::endl;


	//---------------- TEST DESTINATION
	struct sockaddr_in address	= get_socket()->get_address();
	std::cout << "Address :" << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl;
	//------------------------------


*/

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
