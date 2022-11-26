#include "../../incs/parsConf/GlobalConfiguration.hpp"

//------------------------------- CONSTRUCTOR  DESTRUCTOR--------------------------------
GlobalConfiguration::GlobalConfiguration() {}

GlobalConfiguration::~GlobalConfiguration() {}

// --------------------------------- METHODS ----------------------------------

void	GlobalConfiguration::addServer(ServerInParser & server)
{
	_serversList.push_back(server);
	//g_nb_of_server = _serversList.size();
}

void	GlobalConfiguration::addServer(void)
{
	_serversList.push_back(ServerInParser());
	//g_nb_of_server = _serversList.size();
}


/*
** --------------------------------- ACCESSOR ---------------------------------
*/

std::vector<ServerInParser> & GlobalConfiguration::getServersList()
{
	return _serversList;
}


/* ************************************************************************** */