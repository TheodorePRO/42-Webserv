#include "../incs/ClientS.hpp"
#include "cstdio"



# define B_SIZE 30000

namespace SAMATHE{
//********MS
	ClientS::ClientS(){}
//********MS	
	ClientS::ClientS(int fd, ServerInParser *conf, TestServer *serv)
	{
		_fd = fd;
		_serv = serv;
		_conf = conf;
		_justRecv = "";
		_binary = 0;
		_output = "";
		_sent = 0;
//******MS
		receiving();
	}
	ClientS::~ClientS(){}


	void	ClientS::receiving() 
	{
std::cout << " -------  Enter Receiving --------- " << std::endl;
//		int i = _conf->getClientBufferSize();
//		if (i < 100)
//			i = 100;
		char		buffer[B_SIZE] = {0};
		int			ret;

		// ------ appel système pour recevoir depuis le client
std::cout << "_fd =" << _fd<< std::endl;
		ret = ::recv(_fd, buffer, sizeof(buffer), 0);
		if (ret == 0 || ret == -1)
		{
			close(_fd);
			_status = FINI;
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
				// ------ Cas où pas content-length dans le header -> pas header de POST donc GET
				handler();
				_status = WRITE;
				FD_SET(_fd, _serv->get_writeMaster_set());
				std::cout << "A   *vvvvvvvvvvvvvvvvv***" << std::endl;
				return;
			}
			size_t	len = std::atoi(_justRecv.substr(_justRecv.find("Content-Length: ") + 16, 10).c_str());
			if (_received >= len + i + 4)
			{
				// ------ Cas où on a lu toute la requete
				std::cout << "B   *vvvvvvvvvvvvvvvvv***" << std::endl;
				handler();
				_status = WRITE;
				FD_SET(_fd, _serv->get_writeMaster_set());
				return;
			}
			std::cout << "C   *vvvvvvvvvvvvvvvvv***"<< std::endl;
		}

	}

	void ClientS::handler()
	{
		// ------ Read request and slash it into vector
		std::stringstream ssxx(_justRecv);
		std::istream_iterator<std::string> begin(ssxx);
		std::istream_iterator<std::string> end;
		std::vector<std::string> cut(begin, end);
		_reception.setReception(cut);
std::cout << "------ Exit Handler ----------"<< std::endl;
	}

	
	void ClientS::checkPage()
	{
		std::string prefix;
		if (_conf->getPort() != 8080)
			prefix = "pages/";
		else
			prefix = "pages2/";
		if (_response.setContent(prefix.c_str() + _reception.getPage()) == 0)
		{
			_response.setContent(std::string("error/404.html").c_str());
			_response.setCode("404");
		}
	}

	void ClientS::makeHeader()
	{
		// ------ Build response : header + content
		std::ostringstream oss;
		oss << _reception.getVersion() << " " << _response.getCode() << _serv->getError(_response.getCode()) << "\r\n";
		oss << "Cache-Control: no-cache, private\r\n";
		oss << "Content-Type: "<< _serv->getContents(_response.getType()) << "\r\n";
		oss << "Content-Length: " << _response.getContent().size() << "\r\n";
		oss << "\r\n";

		oss << _response.getContent();
		_output = oss.str();
		sending();
	}


	void ClientS::responder()
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
		else if (_reception.getMethod() == "DELETE")
		{
			if (_reception.getPage() != "")
			{
				remove(_reception.getPage().c_str());
				_response.setCode("204");
				_response.setC("<html> \n<body> \n<h1>File deleted.</h1> \n</body> \n</html>");
				_response.setType("html");
			}
		}
		else
		{
			_response.setCode("404");
			_reception.setPage("pages/error/404.html");
			checkPage();
			makeHeader();
		}
	}

	void	ClientS::sending()
	{
std::cout << "------ Enter sending ----------"<< std::endl;
std::cout << "output size = "<< _output.size() << std::endl;
std::cout << "sent = "<< _sent << std::endl;

		std::string	str = _output.substr(_sent, B_SIZE);
std::cout << "str size = "<< str.size() << std::endl;
		int	ret = ::send(_fd, str.c_str(), str.size(), 0);
std::cout << "----- sent ----- " << std::endl;

		_sent += ret;
		if (ret != -1 && ret !=0 && _sent < _output.size())
		{
std::cout << "----- NOT FINISHED  ---- " << std::endl;
			return;
		}
		else
		{
std::cout << "----- 1 YES FINISHED  ---- " << std::endl;
			close(_fd);
std::cout << "----- 2 YES FINISHED  ---- " << std::endl;
			_status = FINI;
std::cout << "----- 3 YES FINISHED  ---- " << std::endl;
			FD_CLR(_fd, _serv->get_master_set());
std::cout << "----- 4 YES FINISHED  ---- " << std::endl;
			if (FD_ISSET(_fd, _serv->get_writeMaster_set()))
				FD_CLR(_fd, _serv->get_writeMaster_set());
std::cout << "----- 5 YES FINISHED  ---- " << std::endl;
			_reception.clearReception();
std::cout << "----- 6 YES FINISHED  ---- " << std::endl;
			_received = 0;
std::cout << "----- 7 YES FINISHED  ---- " << std::endl;
			_justRecv.clear();
std::cout << "----- 8 YES FINISHED  ---- " << std::endl;
			_binary = 0;
std::cout << "----- 9 YES FINISHED  ---- " << std::endl;
			_sent = 0;
std::cout << "----- 10 YES FINISHED  ---- " << std::endl;
			_output = "";
std::cout << "----- 11 YES FINISHED  ---- " << std::endl;
		}
	}
	
	// 
	int	ClientS::getStatus()
	{return _status;}

}
