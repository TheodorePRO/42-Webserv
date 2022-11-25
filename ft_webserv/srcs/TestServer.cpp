#include "../incs/TestServer.hpp"
#include "../incs/Conf.hpp"
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
#include <fcntl.h>
#include <vector> 
#include <istream>
#include <iterator> 
#include <map>

namespace SAMATHE{
	// ------ Constructor
	TestServer::TestServer(ServConf &sc) : Server(sc)
	{	// ------ le constructeur créé un e listeniong socket...
		std::cout << "==READY TO LAUNCH=="<< std::endl;
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
		

		_max_cld = 0;
		int new_socket = accept(get_socket(i).get_sock(), (struct sockaddr *)&address, (socklen_t *)&addrlen);

		if (new_socket > - 1 )
		{
			std::cout << "Client accepted at ip :" << inet_ntoa(address.sin_addr) << ":" << ntohs(address.sin_port) << std::endl; 
			fcntl(new_socket, F_SETFL, O_NONBLOCK);
			fd_set tmp = get_master_set();
			FD_SET(new_socket, &tmp);
	//_responder.add_to_map(new_socket, address.sin_port, address.sin_family);
	//_client_sockets.insert(pair<int, Reception>(new_socket, Reception()));
			_client_sockets[new_socket] = Reception(new_socket);

			if (new_socket > _max_cld) {
				_max_cld = new_socket;
			}
		}
		else
			perror("Failed to accept...");
	}

	//*****j'ai ajute sd (socket de client), que permettra de gere plusieurs requets de differents clients.
	void	TestServer::receiving(int sd) 
		{
		char				buffer[30000];
		int					ret;

		// ------ appel système pour recevoir depuis le client
		ret = ::recv(sd, buffer, sizeof(buffer), 0);
		if (ret == 0 || ret == -1)
		{
			close(sd);
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
						handler(sd);
						_status = 1;
					}
					else
						return;
				}
				else
				{
					handler(sd);
					_status = 1;
				}
			}
			size_t	len = std::atoi(_justRecv.substr(_justRecv.find("Content-Length: ") + 16, 10).c_str());
			if (_justRecv.size() >= len + i + 4)
			{
				handler(sd);
				_status = 1;
			}
		}
	}

	void TestServer::handler(int sd)
	{
		(void)sd;
		std::cout << "*** RECEIVED FROM CLIENT ***" << std::endl;
	std::cout <<_justRecv << std::endl;
	std::cout << "*** END OF BUFFER ***" << std::endl;
		// ------ Read request and slash it into vector
		std::stringstream ssxx(_justRecv);
		std::istream_iterator<std::string> begin(ssxx);
		std::istream_iterator<std::string> end;
		std::vector<std::string> cut(begin, end);
		_reception.setReception(cut);
			std::cout << "uuuuuuuuuuuuu  1 "<< _reception.getSize() << std::endl;
	}

	void TestServer::responder(int sd)
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
			::send(sd, output.c_str(), size, 0 );
			close(sd);
		}
		else if (_reception.getMethod() == "POST")
		{
	/*		std::cout << "*** CREATING FILE ***" << std::endl;
			size_t i = _justRecv.find("\r\n\r\n");
			std::ofstream("file.txt") << _justRecv.substr(i , _justRecv.size() - i);
			FILE *file = fopen("RRRRRR.TXT", "wb");
			fwrite(_justRecv,1, _received , file);
	//		free(fileComplete);
			fclose(file);
			_reception.setSize();
	*/	}

		void clearReception();
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

			int res = select(_max_cld + 1, &readFd, &writeFd, 0, 0); //select(get_max_sd() + 1, &readFd, &writeFd, 0, 0)
			if (res <= 0) {
				continue ;
			}
			
			for (int i = 0; i < get_N_sockets(); ++i) {
				if (FD_ISSET(get_socket(i).get_sock(), &readFd)) {
					accepter(i);
				}
			}

			for (std::map<int, Reception>::iterator it = _client_sockets.begin(); it != _client_sockets.end(); ++it) {
				if (FD_ISSET(it->first, &readFd) and _status==READ) { // ***** _status il faut retire  de la class Reception: it->second.get_status()
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
}
