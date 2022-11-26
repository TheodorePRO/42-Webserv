#ifndef SERVERENGINE_HPP
# define SERVERENGINE_HPP

# include "../webserv.hpp"

class ServerInParser;


/*struct Connection
{
	
};*/


class ServerEngine
{
	public:
		typedef struct sockaddr_in		t_sockaddr_in;

	public:
		std::map<int, std::string>		err_dictionary;

	public:
		// ServerEngine(const ServerEngine & src);
		ServerEngine(ServerInParser & server);
		~ServerEngine();

	private:

		int							_socket_fd;
		struct pollfd				_in_fd;
		t_sockaddr_in				_sockaddr;
		socklen_t					_peer_addr_size;
		ServerInParser &			_server;
		ServerInParser 				*_virtual_server;
		GlobalConfiguration			*_globalConf;
		std::map<int, Connection>	_aliveConnections;

		// request / response
		/*Request			*_req;
		Response		*_resp;*/

		void			_buildResponseOnRequest();
		void			_buildRequest();
		void			_getMethod();
		void			_init_dictionary();
		void			_limit_request_size();
		void			_parse_CGI_output(std::string cgi_output);
		void			_postMethod();
		void			_deleteMethod();

	public:

		void			setGlobalConf(GlobalConfiguration *globalConf);
		void			stream_in(int poll_client_fd);
		int				stream_out(int client_fd);
		int				getSocketFd() const;
		struct pollfd	* getInFdPtr();
		void			kill_client(int client_fd);

};

#endif 