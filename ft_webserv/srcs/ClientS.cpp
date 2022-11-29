#include "../incs/ClientS.hpp"

namespace SAMATHE{

//********MS
	ClientS::ClientS(){}

	ClientS::ClientS(int fd, ServerInParser *conf, TestServer *serv)
	{
		_fd = fd;
		_serv = serv;
		_conf = conf;
		_justRecv = "";
		_binary = 0;
//******MS
		receiving();
	}
	ClientS::~ClientS(){}


	void	ClientS::receiving()
	{
		char				buffer[30000] = {0}; 
		int					ret;
		// ------ appel système pour recevoir depuis le client
std::cout << "_fd=" << _fd<< std::endl;
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
std::cout << "buffer=" << buffer << std::endl;

		_justRecv.append(buffer, ret);
		_received += ret;
		size_t	i = _justRecv.find("\r\n\r\n");
		if (i != std::string::npos)
		{
			if (_justRecv.find("Content-Length: ") == std::string::npos)
			{
				handler();
				_status = WRITE; //****MS - c'est read ? verifie stp
				FD_SET(_fd, _serv->get_writeMaster_set());
				std::cout << "A   *vvvvvvvvvvvvvvvvv***" << std::endl;
				return;
			}
			size_t	len = std::atoi(_justRecv.substr(_justRecv.find("Content-Length: ") + 16, 10).c_str());
			if (_received >= len + i + 4)
			{
				std::cout << "B   *vvvvvvvvvvvvvvvvv***" << std::endl;
				handler();
				_status = READ;
				FD_SET(_fd, _serv->get_master_set());
				return;
			}
			std::cout << "C   *vvvvvvvvvvvvvvvvv***"<< std::endl;
//			receiving(); // SELECT DOES THAT ///////////////////////////////
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
	}

	
	void ClientS::checkPage()
	{
		if (_response.setContent(std::string("pages/").c_str() + _reception.getPage()) == 0)
		{
			_response.setContent(std::string("pages/404.html").c_str());
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
			if (_reception.getPage != "")
			{
				remove(_reception.getPage())
				_reception.setCode("204");
				_response.setC("<html> \n<body> \n<h1>File deleted.</h1> \n</body> \n</html>")
				_reception.setType("html");
			}
		}
		else
		{
			_reception.setCode("404");
			_reeption.setPage("pages/error/404.html");
			checkPage();
		}	
		makeHeader();
	}

	void	sending()
	{
		int size = _output.size() + 1;
		int ret = ::send(_fd, _output.substr(_sent, size - _sent).c_str(), size - _sent, 0 );
		_sent += ret;
		if (ret != -1 && ret !=0 && _sent < size)
			return;
		else
		{
			close(_fd);
			_status = FINI;	// to change to 2 ???? depends on select
				FD_CLR(_fd, _serv->get_master_set());
		if (FD_ISSET(_fd, _serv->get_writeMaster_set()))
			FD_CLR(_fd, _serv->get_writeMaster_set());
    
    _reception.clearReception();
			_received = 0;
			_justRecv.clear();
			_binary = 0;
			_sent = 0;
			_output = 0;
		}
	}

//*******MS
	int	ClientS::getStatus()
	{return _status;}

}
