

#include "../incs/Reception.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace SAMATHE
{
	
	Reception::Reception()
	{	
		_fd = 0;
		_method = "";
		_version = "";
		_page = "";
		_body = "";
		_size = 0;
		_fileName = "";
		_fileLim = "";
		_host = "";
		_portC = "";
    _index = "";
	}

	Reception::Reception(int fd, ServerInParser& conf)
	{
		(void) conf;
		_fd = fd;
		_method = "";
		_version = "";
		_page = "";
		_body = "";
		_size = 0;
		_fileName = "";
		_fileLim = "";
		_host = "";
		_portC = "";
    _index = "";
	}

	Reception::~Reception(){}


	void		Reception::setReception(std::vector<std::string> &cut)
	{
		if (cut.size() >= 3)
		{
			_method = cut[0];
			_page = cut[1];
//			if (cut[1] == "/")
//				_page += "index.html";
			_version = cut[2];
			if (std::find(cut.begin(), cut.end(), "Content-Length:") != cut.end())
			{	
				std::istringstream iss(*(++(std::find(cut.begin(), cut.end(), "Content-Length:"))));
				iss >> _size;
			}
			if (std::find(cut.begin(), cut.end(), "Content-Type:") != cut.end())
			{	
				std::istringstream iss(*(++(++(std::find(cut.begin(), cut.end(), "Content-Type:")))));
				iss >> _fileLim;
				_fileLim = std::string("------") + _fileLim.substr(13, _fileLim.size());
			}
			if (std::find(cut.begin(), cut.end(), "Content-Disposition:") != cut.end())
			{		
				std::istringstream iss(*((std::find(cut.begin(), cut.end(), "Content-Disposition:")+3)));
				iss >> _fileName;
				                            std::cout << "fffffffffff "<<_fileName << std::endl;
				_fileName = _fileName.substr(10, _fileName.size()-11);
				_fileName = std::string("/01-IN/") + _fileName;
				                            std::cout << "fffffffffff "<<_fileName << std::endl;
			}
			if (std::find(cut.begin(), cut.end(), "Host:") != cut.end())
			{

				std::istringstream iss(*(++(std::find(cut.begin(), cut.end(), "Host:"))));
				iss >> _host;
				_portC = _host.substr(_host.find(":") + 1, _host.size());
				_host = _host.substr( 0, _host.find(":"));
			}
		}
	}

	void		Reception::setBody(std::string &justRecv)
	{
		size_t i = justRecv.find(_fileLim) + _fileLim.size();
		_body = justRecv.substr(i , justRecv.find(_fileLim + "--") - i);
		_body = _body.substr(_body.find(std::string("\r\n\r\n")) + 4);
	}


	void	Reception::setPage(std::string p)
	{	_page = p;	}


}
