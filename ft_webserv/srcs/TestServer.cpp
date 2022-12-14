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
		_max_fd = get_max_sd();

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
			
			ClientS new_client = ClientS(new_socket, &_glob_conf.getServersListSocket().at(i), this); 
			int stat = new_client.getStatus();
			if(stat == FINI)
			{
				std::cout << "conection close" << std::endl;
				return;
			}
			fcntl(new_socket, F_SETFL, O_NONBLOCK);
			_client_sockets[new_socket] = new_client;
			if (new_socket > _max_fd) _max_fd = new_socket;

std::cout << "Client accepted _max_fd = " << _max_fd << std::endl; 
		}

		else{
			perror("Failed to accept...");
			return ;
		}
	}
 
	void TestServer::launch()
	{
			// ------Initialize the master fd_set 
		fd_set* readFd = get_master_set();
		fd_set* writeFd = get_writeMaster_set();

		while (true) // ------ boucle infinie qui fait Accept . Handle . Respond (Voir avec Mariys pour le select)
		{ 	
		std::cout << "========WAITING======="<< std::endl;

			// re-add listening socket
			for (int i = 0; i < get_N_sockets(); ++i) {
				if (!FD_ISSET(get_socket(i).get_sock(), readFd)) {
					FD_SET(get_socket(i).get_sock(), readFd);
				}
			}
			// select
			int res = select(_max_fd + 1, readFd, writeFd, 0, 0);
		std::cout << "======= res="<<res<<"======="<< std::endl;
			if (res <= 0) {
				continue ;
			}

		std::cout << "========listen soc======="<< std::endl;
			for (int i = 0; i < get_N_sockets(); ++i) {
		std::cout << "========"<<i<<"======="<< std::endl;
				if (FD_ISSET(get_socket(i).get_sock(), readFd)) {
		std::cout << "========accept"<<i<<"======="<< std::endl;
					accepter(i);
				}
			}
//****MS******** new map.eraise*******************************************************			
			std::map<int, ClientS>::iterator it = _client_sockets.begin();
			while ( it != _client_sockets.end()) {
		std::cout << "========_client_sockets========"<< std::endl;
				if (FD_ISSET(it->first, readFd) and it->second.getStatus()==READ) { 
		std::cout << "========_client_socket read ======="<< std::endl;
					it->second.receiving(); 
				}
				else if (FD_ISSET(it->first, writeFd) and it->second.getStatus()==WRITE) {
		std::cout << "========_client_socket write ======="<< std::endl;
					it->second.sending(); 
				}

				if (it->second.getStatus()==FINI){
					std::map<int, ClientS>::iterator itt = it;
					++itt;
					if (itt != _client_sockets.end()){
						int next_key = itt->first;
						_client_sockets.erase(it);
						it = _client_sockets.find(next_key);
					}
					else{
						_client_sockets.erase(it);
						break;
					}
				}
				else
					++it;

std::cout << "=======endwhile"<< std::endl;
			}
//****************************************************************************************
		std::cout << "========DONE========" << std::endl;
		}
	}
	void	TestServer::initErrorMap()
	{
		_errors["200"] = " OK";
		_errors["201"] = " Created";
    _errors["202"] = " Accepted";
		_errors["204"] = " No Content";
    _errors["301"] = " Moved permanently";
    _errors["307"] = " Internal redirect";
		_errors["400"] = " Bad Request";
		_errors["403"] = " Forbidden";
		_errors["404"] = " Not Found";
		_errors["405"] = " Method Not Allowed";
		_errors["413"] = " Payload Too Large";
		_errors["500"] = " Internal Server Error";
		_errors["505"] = " Unsuported version";
	}

	void TestServer::initContentMap()
	{
		_contents["py"] = "application/py";	
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
