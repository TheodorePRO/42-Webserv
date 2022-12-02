#ifndef SERVERINPARSER_HPP
# define SERVERINPARSER_HPP

# include "../webserv.hpp"

#include <netdb.h>
#include <netinet/in.h>


class Location;

class ServerInParser
{
	private:

		std::vector<std::string>	_names;
		std::string					_IP;
		int							_port;
		std::map<int, std::string>	_errorPages;
		std::size_t					_clientBufferSize;  // TJ Not here, but in locations
		std::vector<Location>		_routes;


	public:

		ServerInParser();
		ServerInParser(ServerInParser const & src );
		~ServerInParser();

		// Setters
		
		void			addName(std::string name);
		void			setIP(std::string IP); // can be equal to 'localhost'
		void			setPort(std::string port);
		void			addErrorPage(int error_code, std::string filePath);
		void			setClientBufferSize(std::size_t buffer_max);
		Location &		addLocation();
		void			completeErrorPages();

		// Accessors
		std::vector<std::string> & 	getNames();
		std::string 				getIP() const;
		int							getPort() const;
		in_addr_t					getIP_() const;
		in_port_t					getPort_() const;
		std::size_t					getClientBufferSize() const;
		std::string					getErrorPagePath(int error_code) const;
		std::vector<Location> 	&	getRoutes();

		// Socket
		int							getBklg(){return 42;};
		int							getDomain(){return PF_INET;};
		int							getService(){return SOCK_STREAM;};

		int							getProto()
		{
			struct	protoent	*proto;
			proto = getprotobyname("tcp");
			if (!proto)
			{
				perror("Get Proto failed... ");
				return 0;
			}
			else
				return proto->p_proto;
		};
	//********************************************

	private:

		// helper functions
		bool _isIPValid(std::string IP) const;

};

#endif
