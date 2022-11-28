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
			_client_sockets[new_socket] = ClientS(new_socket, _glob_conf.getServersList().at(i), this); // ajouter variables comme 'address' et 'conf'

			if (new_socket > _max_cld) 
			{
				_max_cld = new_socket;
			}
		}

		else
			perror("Failed to accept...");
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


		std::string		TestServer::getError(std::sting code)
		{
			 return (_errors.find(code)->second);
		}

		std::string		TestServer::getContents(std::string type);
		{
			 return (_contents.find(type)->second);
		}

}
