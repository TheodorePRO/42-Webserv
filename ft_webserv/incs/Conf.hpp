#ifndef CONF_HPP
# define CONF_HPP

#include <netdb.h>
#include <netinet/in.h>
#include <vector>


namespace SAMATHE
{
		typedef struct conf_server_t{
			int		_proto;
			int		_domain;
			int		_service;
			int		_port;
			u_long	_interface;
			int		_bklg;
			u_long	_family;
		} conf_server;	
	
	class ServConf 
	{
		std::vector<conf_server> conf_servers; // vecteur de configuration

		public:
		ServConf(char* conf_file)
		{
			(void)conf_file;
			conf_server tmp;
			
			struct	protoent	*proto;
			proto = getprotobyname("tcp");
			if (!proto)
			{
				perror("Get Proto failed... ");
				tmp._proto	= 0;
			}
			else
			tmp._proto		= proto->p_proto;
			tmp._domain		= PF_INET;
			tmp._service	= SOCK_STREAM;
			tmp._port		= 8080;   //*************
			tmp._interface	= INADDR_ANY;
			tmp._bklg		= 42;	//*********
			tmp._family		= AF_INET;

			conf_servers.push_back(tmp);
		}

		~ServConf(){};

		int	getNumConfServs()
		{	return conf_servers.size();	}
		conf_server&	getConfServ(int i)
		{	return conf_servers[i];	}

		// int	getDom()
		// {	return _domain;	}
		// int	getSer()
		// {	return _service;	}
		// int	getProt()
		// {	return _proto;	}
		// int	getPort()
		// {	return _port;	}
		// int	getInt()
		// {	return _interface;	}
		// int	getBkl()
		// {	return _bklg;	}

	};
}
#endif
