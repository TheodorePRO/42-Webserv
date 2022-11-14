#include "../incs/TestServer.hpp"
#include "../incs/Conf.hpp"
#include <unistd.h>
#include <string.h>

#include <sys/stat.h>
//#include <iostream>				// for open
//#include <fstream>				// for open

	//#include <sys/sendfile.h> // sendfile for linux
//	#include <sys/types.h>		// sendfile for mac
//	#include <sys/socket.h>
//	#include <sys/uio.h>


// ------ Constructor
SAMATHE::TestServer::TestServer(SAMATHE::ServConf &sc) : Server(sc)
{
	std::cout << "==READY TO LAUNCH=="<< std::endl;
	launch();
}


void SAMATHE::TestServer::accepter()
{
	struct sockaddr_in address = get_socket()->get_address();
	
	int addrlen = sizeof(address);

	new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&address, (socklen_t *)&addrlen);
	read(new_socket, buffer, 30000);
}

void SAMATHE::TestServer::handler()
{
	std::cout << "*** RECEIVED FROM CLIENT ***" << std::endl;
	std::cout << 	buffer << std::endl;
	std::cout << "*** END OF BUFFER ***" << std::endl;
}

void SAMATHE::TestServer::responder()
{

	char *hello = (char *)"Hello from server";
	write(new_socket, hello, strlen(hello));
	close(new_socket);

	// ------ Read html
/*	std::fstream	file;
	std::sstream	buf;
	file.open("../pages/index.html", std::ifstream::in);
	if (file.is_open() == false)
		return ("<!Doctype html>\n<html><title>40404</title><body>there was an error finding your page</body></html>\n");
	buf << file.rdbuf();
	file.close();

	_type = "text/html";

	char *head = (char *)\
				 "HTTP/1.1 200 OK\n\
				 Content-Type: text/plain\n\
				 Content-Length: 200\n\n";

	//	write(new_socket, head, strlen(head));
//	write(new_socket, hello, strlen(hello));
//	close(new_socket);

//void serve_static(int fd, char *filename, size_t filesize)
//{
//    int srcfd;
 //   char buf[LINE_MAX];

    // Send response headers to client 
  //  get_filetype(filename, filetype);


    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: minihttp web server\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, "html");

    // Send response body to client 
	std::fstream fs;
//	int page = open("../pages/index.html", O_RDONLY);
    fs = open("../pages/index.html", ios::out);
    if (fs < 0)
        err_sys("open");

	struct stat stat_buf;
    int filesize = fstat(fd, &stat_buf);
  
	writen(new_socket, buf, strlen(buf));
    Sendfile(srcfd, new_socket, filesize);

    close(fs);
    close(new_socket);
*/

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
