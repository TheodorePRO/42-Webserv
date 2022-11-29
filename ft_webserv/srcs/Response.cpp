#include "../incs/Response.hpp"


SAMATHE::Response::Response(){}
SAMATHE::Response::~Response(){}


int		SAMATHE::Response::setContent(std::string page)
{	
	std::ifstream		file(page.c_str());
	if (file.is_open())
	{
		std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		_content = str;
		setCode("200");
		setType(page.substr(page.find(".") + 1));
		file.close();
		return 1;
	}
	else
	{
		file.close();
		return 0;
	}
}
