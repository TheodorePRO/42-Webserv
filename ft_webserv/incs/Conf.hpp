#ifndef CONF_HPP
# define CONF_HPP

#include <netdb.h>
#include <netinet/in.h>
#include <vector>

namespace SAMATHE
{
	typedef struct conf_server_t{
		int		proto;
		int		domain;
		int		service;
		int		port;
		u_long	interface;
		int		bklg;
		u_long	family;

	} conf_server;

	class ServConf 
	{
		std::vector<conf_server> conf_servers;

		public:
		ServConf()
		{
			conf_server tmp;

			struct	protoent	*prt;
			prt = getprotobyname("tcp");
			if (!prt)
			{
				perror("Get Proto failed... ");
				tmp.proto	= 0;
			}
			else
				tmp.proto		= prt->p_proto;
			tmp.domain		= PF_INET;
			tmp.service	= SOCK_STREAM;
			tmp.port		= 8080;   //*************
			tmp.interface	= INADDR_ANY;
			tmp.bklg		= 42;	//*********
			tmp.family		= AF_INET;

			conf_servers.push_back(tmp);
		}

		~ServConf(){};

		int	getNumConfServs()
		{	return conf_servers.size();	}
		conf_server&	getConfServ(int i)
		{	return conf_servers[i];	}
/*
		int	getDom(int i)
		{	return conf_servers[i]._domain;	}
		int	getSer()
		{	return _service;	}
		int	getProt()
		{	return _proto;	}
		int	getPort()
		{	return _port;	}
		int	getInt()
		{	return _interface;	}
		int	getBkl()
		{	return _bklg;	}
*/
	};
}
#endif
