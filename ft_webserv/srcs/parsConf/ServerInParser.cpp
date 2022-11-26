#include "../../incs/parsConf/ServerInParser.hpp"

/*
** --------------------------- EXTERNAL HELPER FUNCTIONS ----------------------
*/

// check if a given string is a numeric string or not
static bool isNumber(const std::string &str)
{
	return !str.empty() &&
		   (str.find_first_not_of("0123456789") == std::string::npos);
}

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ServerInParser::ServerInParser()
	:_port(-1), _clientBufferSize(-1) {}

ServerInParser::ServerInParser(const ServerInParser &src)
{
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ServerInParser::~ServerInParser() {}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ServerInParser &ServerInParser::operator = (ServerInParser const &rhs)
{
	if (this != &rhs)
	{
		_names = rhs._names;
		_IP = rhs._IP;
		_port = rhs._port;
		//_errorPages = rhs._errorPages;
		_clientBufferSize = rhs._clientBufferSize;
		//_routes = rhs._routes;
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

// Setters

void ServerInParser ::addName(std::string name)
{
	_names.push_back(name);
}

void ServerInParser::setIP(std::string IP)
{
	if (!_isIPValid(IP))
		throw std::invalid_argument("IP address is not valid");
	else
		_IP = IP;
}

void ServerInParser::setPort(std::string port)
{
	if (!isNumber(port))
		throw std::invalid_argument("Port number is not valid");
	else if (std::atoi(port.c_str()) > 65535)
		throw std::invalid_argument("Bad/illegal port format (max value: 65535)");
	else
		_port = std::atoi(port.c_str());
}

/*void ServerInParser::addErrorPage(int error_code, std::string filePath)
{
	_errorPages.insert(std::make_pair(error_code, filePath));
}

void ServerInParser::setClientBufferSize(std::size_t buffer_max)
{
	_clientBufferSize = buffer_max;
}*/
/*
Location & ServerInParser::addLocation()
{
	_routes.push_back(Location());
	return _routes.back();
}*/

// Private Helpers

bool ServerInParser::_isIPValid(std::string IP) const
{
	if (IP.compare("localhost") == 0)
		return true;

	if (IP.size() < 7) // smallest value being '0.0.0.0'
		return false;

	// split the string into tokens
	std::vector<std::string> list = split(IP, '.');

	// if the token size is not equal to four
	if (list.size() != 4)
	{
		return false;
	}

	// validate each token
	for (std::vector<std::string>::iterator it = list.begin(); it != list.end(); ++it)
	{
		// verify that the string is a number or not, and the numbers
		// are in the valid range
		if (!isNumber(*it) ||
			std::atoi(it->c_str()) > 255 ||
			std::atoi(it->c_str()) < 0)
		{
			return false;
		}
	}
	return true;
}

/*void			ServerInParser::completeErrorPages()
{
	if (_errorPages.find(BAD_REQUEST) == _errorPages.end())
	{
		_errorPages[BAD_REQUEST] = BAD_REQUEST_DEFAULT;
	}
	if (_errorPages.find(FORBIDDEN) == _errorPages.end())
	{
		_errorPages[FORBIDDEN] = FORBIDDEN_DEFAULT;
	}
	if (_errorPages.find(NOT_FOUND) == _errorPages.end())
	{
		_errorPages[NOT_FOUND] = NOT_FOUND_DEFAULT;
	}
	if (_errorPages.find(METHOD_NOT_ALLOWED) == _errorPages.end())
	{
		_errorPages[METHOD_NOT_ALLOWED] = METHOD_NOT_ALLOWED_DEFAULT;
	}
	if (_errorPages.find(SERVER_ERROR) == _errorPages.end())
	{
		_errorPages[SERVER_ERROR] = SERVER_ERROR_DEFAULT;
	}
}*/

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::vector<std::string> & ServerInParser::getNames()
{
	return _names;
}

std::string ServerInParser::getIP() const
{
	return _IP;
}

int ServerInParser::getPort() const
{
	return _port;
}

/*std::string ServerInParser::getErrorPagePath(int error_code) const
{
	std::map<int, std::string>::const_iterator it = _errorPages.find(error_code);
	
	if (it == _errorPages.end())
		return "";
	else
		return it->second;
}*/

/*std::size_t ServerInParser::getClientBufferSize() const
{
	return _clientBufferSize;
}*/

/*std::vector<Location> & 	ServerInParser::getRoutes()
{
	return _routes;
}*/

/* ************************************************************************** */