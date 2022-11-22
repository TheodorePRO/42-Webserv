#ifndef GLOBALCONFIGURATION_HPP
# define GLOBALCONFIGURATION_HPP

# include "./webserv.hpp"

class ServerInParser;
class ServerEngine;

class GlobalConfiguration
{

	public:

		GlobalConfiguration();
		~GlobalConfiguration();

	private:
		
		std::vector<ServerInParser>				_serversList;
		std::vector<ServerEngine *>				_serverEngines;
		t_fds_map								_fds_ptr;

	public:

		// methods & setters

		void	addServer(void);
		void	addServer(ServerInParser & server);
		void	addClientFd(int fd, int flag_events, ServerEngine *serv_ptr);
		void	updateClientFd(int fd, int flag_events, ServerEngine *serv_ptr);
		void	eraseClientFd(int fd);
		void	startEngines();
		void	dispatchStream(std::vector<struct pollfd> fds);

		// accessors
		
		std::vector<ServerInParser> & 			getServersList();
		std::vector<ServerEngine *> &			getEngines();
		t_fds_map					& 			getFdsPtr();

};

#endif /* ********************************************* GLOBALCONFIGURATION_H */