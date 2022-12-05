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
	std::cout << "I aaaaaaaaaaaammmmmmmmm  assServer(void)\n";
	for ( unsigned int i = 0 ; i < _serversList.size() ; i++)
	{
		std::cout << "aaaaaaaa = "<< i << " = " << _serversList.at(i).getRoot() << "\n";
		std::cout << " aaaaaaaa = "<< i << " = " << _serversList.at(i).getIP() << "\n";    
	}
	_serversList.push_back(ServerInParser());
	for ( unsigned int i = 0 ; i < _serversList.size() ; i++)
	{
		std::cout << "AFTER aaaaaaaa = "<< i << " = " << _serversList.at(i).getRoot() << "\n"; 
		std::cout << "AFTER aaaaaaaa = "<< i << " = " << _serversList.at(i).getIP() << "\n";  
	}
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