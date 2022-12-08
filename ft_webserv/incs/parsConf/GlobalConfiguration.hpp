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
		std::vector<ServerInParser>				_ggg;
		

	public:

		// methods & setters

		void	addServer(void);
		void	addServer(ServerInParser & server);
		

		// accessors
		
		std::vector<ServerInParser> & 			getServersList();
		std::vector<ServerInParser> & 			getServersList_ggg();
		

};

#endif /* ********************************************* GLOBALCONFIGURATION_H */