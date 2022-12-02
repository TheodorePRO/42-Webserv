#include "../incs/ClientS.hpp"



# define B_SIZE 300000

namespace SAMATHE{
	ClientS::ClientS(){}
	ClientS::ClientS(int fd, ServerInParser *conf, TestServer *serv)
	{
		_fd = fd;
		_serv = serv;
		_conf = conf;
		_justRecv = "";
		_binary = 0;
		_output = "";
		_sent = 0;
		receiving();
	}
	ClientS::~ClientS(){}


	void	ClientS::receiving() 
	{
		std::cout << " -------  Enter Receiving --------- " << std::endl;
		char		buffer[B_SIZE] = {0};
		int			ret;

		// ------ appel système pour recevoir depuis le client
		std::cout << "_fd =" << _fd<< std::endl;
		ret = ::recv(_fd, buffer, sizeof(buffer), 0);
		std::cout << " -------buffer --------- " << buffer << std::endl;
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
		std::cout << ret << " ------- rnrn  --------- " << i << std::endl;
		if (i != std::string::npos)
		{
			if (_justRecv.find("Content-Length: ") == std::string::npos)
			{
				// ------ Cas où pas content-length dans le header -> pas header de POST donc GET
				std::cout << "A   *vvvvvvvvvvvvvvvvv***" << std::endl;
				handler();
				_status = WRITE;
				FD_SET(_fd, _serv->get_writeMaster_set());
				return;
			}
			size_t	len = std::atoi(_justRecv.substr(_justRecv.find("Content-Length: ") + 16, 10).c_str());
			if (_received >= len + i + 4)
			{
				// ------ Cas où on a lu toute la requete
				std::cout << "B   *vvvvvvvvvvvvvvvvv***" << std::endl;
				handler();
				_status = WRITE;			//// TJ has finished receiving => WRITE
				FD_SET(_fd, _serv->get_writeMaster_set());  //////// TJ : has finished receiving
				return;
			}
			std::cout << "C   *vvvvvvvvvvvvvvvvv***"<< std::endl;
		}

	}

	void ClientS::handler()
	{
		// ------ Read request and slash it into vector
		std::cout  << _justRecv << std::endl;
		std::stringstream ssxx(_justRecv);
		std::istream_iterator<std::string> begin(ssxx);
		std::istream_iterator<std::string> end;
		std::vector<std::string> cut(begin, end);
		_reception.setReception(cut);
		std::cout << "rrrrrrrrrrrrrrrrr "<< _reception.getHost() << std::endl;
		//	_location = getLocation(_reception.getHost());



		std::cout << "------ Exit Handler ----------"<< std::endl;
		responder();
	}


	void ClientS::checkPage()
	{
		std::string prefix;
		if (_conf->getPort() != 8080)
			prefix = "pages/";
		else
			prefix = "pages2/";
		if (_response.getCode() == "")
		{
	//AUTO INDEX == on ????????
std::cout << "--------Index ? - -------"<< (*(_reception.getPage()).rbegin() == '/') << std::endl;
			if (*(_reception.getPage()).rbegin() == '/')
			{
	// ROOT
				_response.setC(_response.genIndex(_reception.getPage()));
				if (_response.getCode() == "")
					_response.setCode("200");
				_response.setType(std::string("html"));
			}
			else if (_response.setContent(prefix.c_str() + _reception.getPage()) == 0)
			{
				_response.setContent(std::string("error/404.html").c_str());
				_response.setCode("404");
			}
		}
		else
			_response.setContent(std::string("error/") + _response.getCode() + std::string(".html"));
	}

	void ClientS::makeHeader()
	{
		// ------ Build response : header + content
		std::ostringstream oss;
		oss << _reception.getVersion() << " " << _response.getCode() << _serv->getError(_response.getCode()) << "\r\n";
		oss << "Cache-Control: no-cache, private\r\n";
std::cout << "------ content type ="<< _response.getType() << std::endl;
		oss << "Content-Type: "<< _serv->getContents(_response.getType()) << "\r\n";
		oss << "Content-Length: " << _response.getContent().size() << "\r\n";
		oss << "\r\n";


		oss << _response.getContent();
		_output = oss.str();
	}


	void ClientS::responder()
	{
		// ------ GET response content

		if (_reception.getVersion() != "HTTP/1.1" && _reception.getVersion() != "HTTP/1.0")
		{
			_response.setCode("505");
			//		_reception.setPage("error/505.html");
			checkPage();
			makeHeader();
		}
		else if (_reception.getMethod() == "GET")
		{
			checkPage();
			makeHeader();
		}
		else if (_reception.getMethod() == "POST")
		{
			if (_location.getMaxSize() && _reception.getSize() > _location.getMaxSize())
			{
				_response.setCode("413");
				_reception.setPage("error/413.html");
				checkPage();
				makeHeader();
				return;
			}
			std::cout << "*** CREATING FILE ***"<< _reception.getFName() << std::endl;
			_reception.setBody(_justRecv);
			std::string n = std::string("pages/") + _reception.getFName();
			std::cout << "------ ----------"<< n << std::endl;
			std::ofstream file(n.c_str());
			//	std::ofstream file(std::string("pages/") + _reception.getFName().c_str());
			file << _reception.getBody();
			if (_reception.getBody().size() == 0 && _response.getCode() == "")
				_response.setCode("204");
			else
				_response.setCode("201");
			checkPage();
			makeHeader();
		}
		else if (_reception.getMethod() == "DELETE")
		{
			if (_reception.getPage() != "")
			{
				std::string n = std::string("pages/") + _reception.getPage();
				std::cout << "*** DELETING FILE ******"<< n << std::endl;
				remove(n.c_str());
				_response.setCode("204");
				_response.setC("<html> \n<body> \n<h1>File deleted.</h1> \n</body> \n</html>");
				_response.setType("html");
			}
		}
		else
		{
			_response.setCode("400");
			//		_reception.setPage("error/405.html");
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
			_status = FINI;
			FD_CLR(_fd, _serv->get_master_set());
			if (FD_ISSET(_fd, _serv->get_writeMaster_set()))
				FD_CLR(_fd, _serv->get_writeMaster_set());
			_reception.clearReception();
			_received = 0;
			_justRecv.clear();
			_binary = 0;
			_sent = 0;
			_output = "";
		}
	}

	int	ClientS::getStatus()
	{return _status;}

	Location			ClientS::getLocation(std::string host)
	{
		std::vector<Location>	locs = _conf->getRoutes();
		for (std::vector<Location>::iterator it = locs.begin() ; it != locs.end(); ++it)
		{
			if (it->getRoot() == host)
				return *it;
		}
		return locs[0];
	}
}
