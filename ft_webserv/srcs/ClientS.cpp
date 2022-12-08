#include "../incs/ClientS.hpp"
# define B_SIZE 300000

namespace SAMATHE{

  ClientS::ClientS(){}

//********************************************
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

//********************************************
	void	ClientS::receiving() 
	{
		                        std::cout << " -------  Enter Receiving --------- " << std::endl;
		char		buffer[B_SIZE] = {0};
		int			ret;

		// ------ appel système pour recevoir depuis le client
		std::cout << "_fd =" << _fd<< std::endl;
		ret = ::recv(_fd, buffer, sizeof(buffer), 0);
		                        //std::cout << " -------buffer --------- " << buffer << std::endl;
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
				_status = WRITE;
				FD_SET(_fd, _serv->get_writeMaster_set());
			}
			                           std::cout << "C   *vvvvvvvvvvvvvvvvv***"<< std::endl;
		}

	}
//********************************************
	void ClientS::handler()
	{

		                              //std::cout  << _justRecv << std::endl;
		std::stringstream ssxx(_justRecv);
		std::istream_iterator<std::string> begin(ssxx);
		std::istream_iterator<std::string> end;
		std::vector<std::string> cut(begin, end);
		_reception.setReception(cut);
	                               	std::cout << "rrrrrrrrrrrrrrrrr "<< _reception.getHost() << std::endl;
		getServer();
                                  std::cout << "jjjjjjj" <<_server.getNames().size() << std::endl;
                                  std::cout << "jjjjjjj" <<_server.getPort() << std::endl;
                                  std::cout << "jjjjjjj" <<_server.getRoot() << std::endl;
                                  std::cout << "jjjjjjj" <<_server.isAutoindexed() << std::endl;
                                  std::cout << "jjjjjjj" <<_server.getErrorPagePath(404)<< std::endl;
                                  std::cout << "jjjjjjj" << _server.getClientBufferSize() << std::endl;
		                              std::cout << "------ Exit Handler ----------"<< std::endl;
		responder();
	}

//********************************************
	void ClientS::checkPage()
	{
                                  std::cout << "--------- page 0-----" << _reception.getPage() << std::endl;
    if (_response.getCode()[0] != '2')
      _reception.setPage( _server.getRoot() + _reception.getPage());
                                  std::cout << "--------- page 1-----" << _reception.getPage() << std::endl;
		if (_response.getCode() == "" || _response.getCode()[0] == '2')
		{
                                  std::cout << "---------check page 2 -----"  << _server.isAutoindexed() << " = --- = " << *(_reception.getPage()).rbegin() << std::endl;
			if (_server.isAutoindexed() != 0 && *(_reception.getPage()).rbegin() == '/')
			{
                                  std::cout << "---------GEN INDEX PAGE -----" << std::endl;
				_response.setC(_response.genIndex(_reception.getPage(), std::string(_server.getIP()), _server.getPort()));
//        _response.setC(_response.genIndex(_reception.getPage()));

				if (_response.getCode() == "")
					_response.setCode("200");
				_response.setType(std::string("html"));
        return;
			}
      else if (*(_reception.getPage()).rbegin() == '/')
      {
                                  std::cout << "--------- / ? -----" << _reception.getIndexP().c_str() << std::endl;
        if (_reception.getIndexP() != "")
        {
                                  std::cout << "---------Take INDEX loc -----" << _reception.getPage() << std::endl;
          std::string g = _reception.getPage().c_str() ;
          g += _reception.getIndexP().c_str();
                                 std::cout << "---------Take INDEX loc -----" << g << std::endl;
          _reception.setPage(g.c_str());
                                  std::cout << "---------set Index page -----" << _reception.getPage() << std::endl;
          _response.setCode("200");
        }
        else
          _response.setCode("404");
        checkPage();
        return;
      }
      else if (_response.setContent(_reception.getPage()) == 0)
			{
                                  std::cout << "---------Page 3-----" << _reception.getPage() << std::endl;
        _response.setCode("404");
        checkPage();
        return;
			}
		}
		else if ( _response.getRedC() == "" && _response.getCode() != "200")
    {
                                 std::cout << "---------Page 4-----" << _response.getCode() << std::endl;
      int respond = std::atoi((_response.getCode()).c_str());
                                 std::cout << "---------Page 4 respond : -----"<< _server.getErrorPagePath(respond) << std::endl;
      if (_server.getErrorPagePath(respond) != "")
        _response.setContent(_server.getErrorPagePath(respond));
      else
        _response.setContent(std::string("error/") + _response.getCode() + std::string(".html"));
	    _response.setType(std::string("html"));
    }
                                  std::cout << "---------OUT -----"  <<_response.getCode() << std::endl;
	}

//********************************************
	void ClientS::makeHeader()
	{
		// ------ Build response : header + content
		std::ostringstream oss;
		oss << _reception.getVersion() << " " << _response.getCode() << _serv->getError(_response.getCode()) << "\r\n";

    if (_response.getRedC() == "")
    {
      oss << "Cache-Control: no-cache, private\r\n";
		  oss << "Content-Type: "<< _serv->getContents(_response.getType()) << "\r\n";
		  oss << "Content-Length: " << _response.getContent().size() << "\r\n";
		  oss << "\r\n";
		  oss << _response.getContent();
    }
    else
      oss << "Location: " << _response.getRedC();
    oss << "\r\n";
  	_output = oss.str();
                                std::cout << "-----make header end  ----------"<< _response.getRedC() << std::endl;
                            //  std::cout << oss.str() << std::endl;
	}

//********************************************
	void ClientS::responder()
	{
		// ------ GET response content
    std::string tmp[] = {"GET", "POST", "DELETE"};
    std::set<std::string> METHODS(tmp, tmp + sizeof(tmp) / sizeof(tmp[0]));
                                std::cout << "------ Version ----------"<<_reception.getVersion() << std::endl;
                                std::cout << "------ Method ----------"<< std::endl;
                                std::cout << "------ Find ?----------"<< (METHODS.find(_reception.getMethod()) != METHODS.end()) << std::endl;

		if (_reception.getVersion() != "HTTP/1.1" && _reception.getVersion() != "HTTP/1.0")
		{
			_response.setCode("505");
			checkPage();
			makeHeader();
      return;
		}
    else if (METHODS.find(_reception.getMethod()) != METHODS.end()  && checkMethod() == 0)
    {
                                std::cout << "------ Not allowed method 403----------"<< std::endl;
      _response.setCode("403");
      checkPage();
      makeHeader();
      return;
    }
		else if (_reception.getMethod() == "GET")
		{
      std::string page = _reception.getPage();
                                std::cout << "------ GCI page ? ----------"<< page << std::endl;
                                std::cout << "------ GCI page2 ? ----------"<< page.substr(page.find("/") + 1 , page.size()) << std::endl;
			if ( page.substr(page.find("/") + 1 , page.size()) == "cgi.html")
      {

				makeCgiRequest(_fd, _server);
				//_reception.setPage("cgi/hello.py");
				close(_fd);
				_status = FINI;
				return ;
	  			}
			else{
				checkPage();
				makeHeader();
			}
		}
		else if (_reception.getMethod() == "POST")
		{
			if (_server.getClientBufferSize() && _reception.getSize() > _server.getClientBufferSize())
			{
				_response.setCode("413");
				checkPage();
				makeHeader();
                            std::cout << "payload"<< _reception.getFName() << std::endl;
				return;
			}
                            std::cout << "*** CREATING FILE ***"<< _reception.getFName() << std::endl;
			_reception.setBody(_justRecv);
			std::string n = _server.getRoot() + _reception.getFName();
			                   std::cout << "------ ----------"<< n << std::endl;
			std::ofstream file(n.c_str());
			//	std::ofstream file(std::string("pages/") + _reception.getFName().c_str());
			file << _reception.getBody();
			if (_reception.getBody().size() == 0 && _response.getCode() == "")
				_response.setCode("204");
			else
				_response.setCode("201");
      _reception.setPage( _server.getRoot() + _reception.getPage());
			checkPage();
			makeHeader();
      return;
		}
		else if (_reception.getMethod() == "DELETE")
		{
			if (_reception.getPage() != "")
			{
				std::string n = std::string(_server.getRoot()) + _reception.getPage();
				std::cout << "*** DELETING FILE ******"<< n << std::endl;
        int i = remove(n.c_str());
                                  std::cout <<"----DELETE " << i << std::endl;
				if ( i == 0)
        {
		      _response.setCode("202");
				  _response.setC("<html> \n<body> \n<h1>File deleted.</h1> \n</body> \n</html>");
				  _response.setType("html");
          makeHeader();
                                  std::cout <<"----DELETE XXX " << i << std::endl;
        }
        else
        {
          _response.setCode("403");
          checkPage();
          makeHeader();
        }
			}
      return;
		}
		else
		{
                        std::cout <<" ------ Method : 400"  << std::endl;
			_response.setCode("400");
			checkPage();
			makeHeader();
		}
	}

	void	ClientS::sending()
	{
		                    std::cout << "------ Enter sending ----------"<< std::endl;
		                    std::cout << "output size = "<< _output.size() << std::endl;


		std::string	str = _output.substr(_sent, B_SIZE - 1);
	                     	std::cout << "str size = "<< str.size() << std::endl;
		int	ret = ::send(_fd, str.c_str(), str.size(), 0);
                    		std::cout << "----- sent ----- " << ret << std::endl;
    str = "";
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
                         std::cout << "output size 2 = "<< _output.size() << std::endl;

		}
	}


	void	ClientS::getServer()
	{
		int i = 0;
		std::vector<ServerInParser> f;
	//	std::vector<ServerInParser> sers = _serv->getGConf().getServersListSocket();
		std::vector<ServerInParser> sers = _serv->getGConf().getServersList();
		for (std::vector<ServerInParser>::iterator it = sers.begin() ; it != sers.end(); ++it)
		{
                                  std::cout << "Server 0----- Nb de serveurs " << sers.size()<<std::endl;
                                  std::cout << "Server 1----- name " << it->getNames().size()<<std::endl;
                                  std::cout << "Server 11 -----ip " << it->getIP() <<" port: "<< it->getPort() <<std::endl;
			if ((it->getPort() == _conf->getPort()) && (it->getIP() == _conf->getIP()))
			{
				i++;
				f.push_back(*it);
			}
		}

		                              std::cout << "Server 2----- i = "<< i << " -- f.size =" <<  f.size() << "   "  << "ggggg" << std::endl;
		if (i == 1)
		{
			_server = f[0];
			return;
		}
		else if (i > 1)
		{
			for (std::vector<ServerInParser>::iterator it = f.begin() ; it != f.end(); ++it)
			{
				std::vector<std::string> names = it->getNames();
				for (std::vector<std::string>::iterator it2 = names.begin() ; it2 != names.end(); ++it2)
				{
					if ( *it2 == _reception.getHost())
					{
						_server = *it;
						return;
					}
				}
			}
			_server = f[0];
		}
	}

  int ClientS::checkMethod()
  {
    unsigned int i = 10000;
    int res = 1;
    if (!_server.getRoutes().empty())
    {
                                std::cout << "------ Met 1 ----------"<< std::endl;
      std::vector<Location> locs = _server.getRoutes();
                                std::cout << "------ Met 2 ----------"<< std::endl;
      for (std::vector<Location>::iterator it = locs.begin() ; it != locs.end(); ++it)
      {
                                std::cout << "------ Met 3 ----------" <<_reception.getPage() <<" nnnn "<< it->getPrefix() << std::endl;
        if (_reception.getPage() == it->getPrefix())
        {
          _reception.setIndexP(it->getIndexPage());
                                std::cout << "------ Met 40 ----------" << it->getIndexPage() <<  "" << _reception.getIndexP() << std::endl;
        }

        if ((_reception.getPage().rfind(it->getPrefix(), 0) == 0) && (i >= it->getPrefix().size()))
        {
                                std::cout << "------ Met 4 ----------" << _reception.getPage() <<"jjj" <<it->getPrefix() << std::endl;
            if (it->getRedirection().first != 0)
            {
                std::ostringstream ss;
                ss << it->getRedirection().first;
                _response.setCode(ss.str());
                _response.setRedir(it->getRedirection().second);
                                std::cout << "------ Met 41 ----------"<< _response.getCode() <<std::endl;
            }
            res = 0;
            i = it->getPrefix().size();
          std::set<std::string> me = it->getAllowedMethods();
          for (std::set<std::string>:: iterator it2 = me.begin() ; it2 != me.end(); it2++)
          {
                                std::cout << "------ Met 6 ----------"<< *it2 << std::endl;
              if (*it2 == _reception.getMethod())
                res = 1;
          }
        }
      }
    }
    std::cout << "------ Met OUT ----------"<< res << std::endl;
    return res;
  }


}
