#ifndef CONF_HPP
# define CONF_HPP

#include <netdb.h>

namespace SAMATHE
{
	class ServConf 
	{
		int			_domain;
		int			_service;
		int			_proto;
		int			_port;
		u_long		_interface;
		int			_bklg;

		public:
		ServConf()
		{
			struct	protoent	*proto;
			proto = getprotobyname("tcp");
//			if (!proto)
//				return (-1); //*********************
			_domain		= AF_INET;
			_service	= SOCK_STREAM;
			_proto		= proto->p_proto;
			_port		= 80;	//*********
			_interface	= INADDR_ANY;
			_bklg		= 10;	//*********
		};
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
