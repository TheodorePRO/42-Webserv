#include "../../incs/parsConf/GlobalConfiguration.hpp"

//------------------------------- CONSTRUCTOR  DESTRUCTOR--------------------------------
GlobalConfiguration::GlobalConfiguration() {}

GlobalConfiguration::~GlobalConfiguration() {}

// --------------------------------- METHODS ----------------------------------

void	GlobalConfiguration::addServer(ServerInParser & server)
{
	std::cout << "I am in addServer(). \n";
	_serversList.push_back(server);
}

void	GlobalConfiguration::addServer(void)
{
	_serversList.push_back(ServerInParser());
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::vector<ServerInParser> & GlobalConfiguration::getServersList()
{
	return _serversList;
}


/* ************************************************************************** */