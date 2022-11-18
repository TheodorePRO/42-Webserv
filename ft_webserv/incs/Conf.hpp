#ifndef CONF_HPP
# define CONF_HPP

#include <netdb.h>
#include <netinet/in.h>

namespace SAMATHE
{
	class ServConf 
	{
		int		_proto;
		int		_domain		;
		int		_service	;
		int		_port	;
		u_long	_interface	;
		int		_bklg	;
		u_long	_family;

		public:
		ServConf()
		{
			struct	protoent	*proto;
			proto = getprotobyname("tcp");
			if (!proto)
			{
				perror("Get Proto failed... ");
				_proto	= 0;
			}
			else
				_proto		= proto->p_proto;
			_domain		= PF_INET;
			_service	= SOCK_STREAM;
			_port		= 8080;   //*************
			_interface	= INADDR_ANY;
			_bklg		= 42;	//*********
			_family		= AF_INET;
		}

		~ServConf(){};

		int	getDom()
		{	return _domain;	}
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

	};
}
#endif
