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
			
			ClientS new_client = ClientS(new_socket, &_glob_conf.getServersList().at(i), this); // ajouter variables comme 'address' et 'conf'
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

		else
			perror("Failed to accept...");
	}
 
	void TestServer::launch()
	{
		fd_set* readFd = get_master_set();
		fd_set* writeFd = get_writeMaster_set();

		// ------Initialize the master fd_set 
		//int listen_sd = get_socket(i).get_sock();

//int j = 5;
//while (j--)
		while (true)
		{ // ------ boucle infinie qui fait Accept . Handle . Respond (Voir avec Mariys pour le select)
			std::cout << "========WAITING======="<< std::endl;

			// re-add listening socket
			for (int i = 0; i < get_N_sockets(); ++i) {
				if (!FD_ISSET(get_socket(i).get_sock(), readFd)) {
					FD_SET(get_socket(i).get_sock(), readFd);
				}
			}

			int res = select(_max_fd + 1, readFd, writeFd, 0, 0); //select(get_max_sd() + 1, &readFd, &writeFd, 0, 0)
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
			
			for (std::map<int, ClientS>::iterator it = _client_sockets.begin(); it != _client_sockets.end(); ++it) {
std::cout << "========_client_sockets=" << it->first <<" status=" <<it->second.getStatus() <<"======="<< std::endl;
				if (FD_ISSET(it->first, readFd) and it->second.getStatus()==READ) { // ? (cd ..*it).get_status() ? ***** _status il faut retire  de la class Reception: it->second.get_status()
std::cout << "========_client_socket read ======="<< std::endl;
					it->second.receiving(); //it->second.receiving(it->first)
					if (it->second.getStatus()==FINI) { // _status from Reception
										 //                    std::cout << "DELETED" << std::endl;
										 //					 _responder.del_from_map(it->first);
						_client_sockets.erase(it);
					}
					//continue ; ????
				}
				if (FD_ISSET(it->first, writeFd) and it->second.getStatus()==WRITE) { // ***** _status il faut retire  de la class Reception: it->second.get_status()
std::cout << "========_client_socket write ======="<< std::endl;
					it->second.sending(); //it->second.responder(it->first);  ///////////////TJ : sending(une fois que le content est pret (avant responder qui prépare le content et envoie après.)
					if (it->second.getStatus()==FINI) {
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
		_errors["200"] = " OK";
		_errors["201"] = " Created";
		_errors["204"] = " No Content";
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


		std::string		TestServer::getError(std::string code)
		{
			 return (_errors.find(code)->second);
		}

		std::string		TestServer::getContents(std::string type)
		{
			 return (_contents.find(type)->second);
		}

}
