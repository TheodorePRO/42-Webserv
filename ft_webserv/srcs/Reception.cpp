

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
	}
}

