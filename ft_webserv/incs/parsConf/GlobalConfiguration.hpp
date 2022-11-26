#ifndef GLOBALCONFIGURATION_HPP
# define GLOBALCONFIGURATION_HPP

# include "../webserv.hpp"

class ServerInParser;
class ServerEngine;

class GlobalConfiguration
{

	public:

		GlobalConfiguration();
		~GlobalConfiguration();

	private:
		
		std::vector<ServerInParser>				_serversList;
		

	public:

		// methods & setters

		void	addServer(void);
		void	addServer(ServerInParser & server);
		

		// accessors
		
		std::vector<ServerInParser> & 			getServersList();
		

};

#endif /* ********************************************* GLOBALCONFIGURATION_H */