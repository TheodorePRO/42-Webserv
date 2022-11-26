#include "../../incs/parsConf/GlobalConfiguration.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

GlobalConfiguration::GlobalConfiguration() {}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

GlobalConfiguration::~GlobalConfiguration() {}


/*
** --------------------------------- OVERLOAD ---------------------------------
*/



/*
** --------------------------------- METHODS ----------------------------------
*/

void	GlobalConfiguration::addServer(ServerInParser & server)
{
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