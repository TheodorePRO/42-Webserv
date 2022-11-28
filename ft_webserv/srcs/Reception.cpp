

#include "../incs/Reception.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


SAMATHE::Reception::Reception()
{
	_method = "";
	_version = "";
	_page = "";
	_body = "";
	_size = 0;
	_fileName = "";
	_fileLim = "";
	
}

SAMATHE::Reception::Reception(int fd, ServerInParser& conf)
{
	//*********MS
	(void) conf; // config de serveur
	_fd = fd;
	//*********MS
			_method = "";
			_version = "";
			_page = "";
			_body = "";
			_size = 0;
}

SAMATHE::Reception::~Reception(){}


void		SAMATHE::Reception::setReception(std::vector<std::string> &cut)
{
	if (cut.size() >= 3)
	{
		_method = cut[0];
		_page = cut[1];
		if (cut[1] == "/")
			_page += "index.html";
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
			_fileName = std::string("01 IN/") + _fileName;
			std::cout << "fffffffffff "<<_fileName << std::endl;
		}
	}
}

void		SAMATHE::Reception::setBody(std::string &justRecv)
{
	size_t i = justRecv.find(_fileLim) + _fileLim.size();
	_body = justRecv.substr(i , justRecv.find(_fileLim + "--") - i);
	_body = _body.substr(_body.find(std::string("\r\n\r\n")) + 4);
}


/*
std::string&	SAMATHE::Reception::pop(std::string& str)
{
	if (str.size())
		str.resize(str.size() - 1);
	return str;
}


void	SAMATHE::Reception::setBody2(const std::string& str)
{
	char	strip[] = {'\n', '\r'};

	this->_body.assign(str);
	for (int i = 0; i < 4; i++)
		if (this->_body.size() > 0 && this->_body[this->_body.size() - 1] == strip[i % 2])
			pop(this->_body);
		else
			break ;
}
*/
