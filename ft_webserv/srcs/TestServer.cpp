#include "../incs/TestServer.hpp"
#include "../incs/webserv.hpp"
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/select.h>

#include <iostream>				// for open
#include <fstream>				// for open
#include <sstream>				// for open
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <vector>
#include <stdio.h>
#include <fcntl.h>
#include <map>
#include <istream>
#include <iterator>
#include <stack>

namespace SAMATHE{
	// ------ Constructor

  TestServer::TestServer(GlobalConfiguration &glob_conf) : Server(glob_conf)
	{	// ------ le constructeur créé un e listeniong socket...
		std::cout << "==READY TO LAUNCH=="<< std::endl;
		_glob_conf = glob_conf;
		_max_cld = get_max_sd();
_file = 0;
_justRecv = "";
_binary = 0;

		initErrorMap();
		initContentMap();
		launch();
	}

	TestServer::~TestServer(){}

	void TestServer::accepter(int i)
	{
		// ------ 1ere fonction : RECEPTION depuis le client
		struct sockaddr_in address	= get_socket(i).get_address();
		int addrlen					= sizeof(address);
		

		int new_socket = accept(get_socket(i).get_sock(), (struct sockaddr *)&address, (socklen_t *)&addrlen);
		if (new_socket > - 1 )
		{
			std::cout << "Client accepted at ip :" << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl; 
			fcntl(new_socket, F_SETFL, O_NONBLOCK);
			fd_set tmp = get_master_set();
			FD_SET(new_socket, &tmp);
	//_responder.add_to_map(new_socket, address.sin_port, address.sin_family);
	//_client_sockets.insert(pair<int, Reception>(new_socket, Reception()));
			_client_sockets[new_socket] = Reception(new_socket, _glob_conf.getServersList().at(i)); // ajouter variables comme 'address' et 'conf'

			if (new_socket > _max_cld) 
      {
				_max_cld = new_socket;
			}
		}

else
			perror("Failed to accept...");
	}

void	Client::receiving()
{
	char				buffer[30000] = {0}; 
	int					ret;
	// ------ appel système pour recevoir depuis le client
	ret = ::recv(_new_socket, buffer, sizeof(buffer), 0);
	if (ret == 0 || ret == -1)
		{
			close(sd);
			if (!ret)
				std::cout << "\rConnection was closed by client.\n" << std::endl;
			else
				std::cout << "\rRead error, closing connection.\n" << std::endl;
			return;
		}
	_justRecv.append(buffer, ret);
	_received += ret;
	size_t	i = _justRecv.find("\r\n\r\n");
	if (i != std::string::npos)
	{
		if (_justRecv.find("Content-Length: ") == std::string::npos)
		{
			handler();
			_status = 1;
			 std::cout << "A   *vvvvvvvvvvvvvvvvv***" << std::endl;
			return;
		}
		size_t	len = std::atoi(_justRecv.substr(_justRecv.find("Content-Length: ") + 16, 10).c_str());
		if (_received >= len + i + 4)
		{
			std::cout << "B   *vvvvvvvvvvvvvvvvv***" << std::endl;
			handler();
			_status = 1;
			return;
		}
		std::cout << "C   *vvvvvvvvvvvvvvvvv***"<< std::endl;
		receiving(); // SELECT DOES THAT ///////////////////////////////
}

}

void Client::handler()
{
	// ------ Read request and slash it into vector
	std::stringstream ssxx(_justRecv);
	std::istream_iterator<std::string> begin(ssxx);
	std::istream_iterator<std::string> end;
	std::vector<std::string> cut(begin, end);
	_reception.setReception(cut);
}



void Client::checkPage()
{
	if (_response.setContent(std::string("pages/").c_str() + _reception.getPage()) == 0)
	{
		_response.setContent(std::string("pages/404.html").c_str());
		_response.setCode("404");
	}
}

void Client::makeHeader()
{
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
}


void Client::responder()
{
	// ------ GET response content
	if (_reception.getMethod() == "GET")
	{
		checkPage();
		makeHeader();
	}
  else if (_reception.getMethod() == "POST")
	{
		std::cout << "*** CREATING FILE ***" << std::endl;
		_reception.setBody(_justRecv);
		std::ofstream file(_reception.getFName().c_str());
		file << _reception.getBody();
		checkPage();
		makeHeader();
	}
	close(_new_socket);
	_status = 2;		// to change to 2 ???? depends on select
	_reception.clearReception();
	_received = 0;
	_justRecv.clear();
	_file = 0;
	_binary = 0;
}




	void TestServer::launch()
	{
		fd_set readFd;
		fd_set writeFd;

		// ------Initialize the master fd_set 
		//int listen_sd = get_socket(i).get_sock();

		while (true)
		{ // ------ boucle infinie qui fait Accept . Handle . Respond (Voir avec Mariys pour le select)
			std::cout << "========WAITING======="<< std::endl;
			readFd = get_master_set();
			writeFd = get_writeMaster_set();


							std::cout << "========select======="<< std::endl;
			int res = select(_max_cld + 1, &readFd, &writeFd, 0, 0); //select(get_max_sd() + 1, &readFd, &writeFd, 0, 0)
			if (res <= 0) {
							std::cout << "========BAD======="<< std::endl;
				continue ;
			}
			
							std::cout << "========listen soc======="<< std::endl;
			for (int i = 0; i < get_N_sockets(); ++i) {
							std::cout << "========"<<i<<"======="<< std::endl;

				if (FD_ISSET(get_socket(i).get_sock(), &readFd)) {
								std::cout << "========accept"<<i<<"======="<< std::endl;
				
					accepter(i);
				}
			}

			for (std::map<int, Reception>::iterator it = _client_sockets.begin(); it != _client_sockets.end(); ++it) {
				if (FD_ISSET(it->first, &readFd) and _status==READ) { // ? (cd ..*it).get_status() ? ***** _status il faut retire  de la class Reception: it->second.get_status()
				receiving(it->first);
					if (_status==FINI) { // _status from Reception
	//                    std::cout << "DELETED" << std::endl;
	//					 _responder.del_from_map(it->first);
						_client_sockets.erase(it);
					}
					continue ;
			}
				if (FD_ISSET(it->first, &writeFd) and _status==WRITE) { // ***** _status il faut retire  de la class Reception: it->second.get_status()
					responder(it->first);
					if (_status==FINI) {
	//                    std::cout << "DELETED" << std::endl;
	//					 _responder.del_from_map(*it);
						_client_sockets.erase(it);
					}
				}
			}

			// handler();
			// responder();
			std::cout << "========DONE========" << std::endl;
		}
	}
	void	TestServer::initErrorMap()
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

	void TestServer::initContentMap()
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

}
