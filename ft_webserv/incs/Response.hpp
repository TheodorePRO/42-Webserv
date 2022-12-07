#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <sys/types.h>	// for DIR
#include <dirent.h>		// for DIR
#include <unistd.h>

namespace SAMATHE
{

	class Response
	{
		std::string					_content;
		std::string					_type;
		std::string					_code;
    std::string         _redir;

		public :
		Response(void);
		~Response(void);

		int				setContent(std::string page);
		void			setC(std::string c);
		std::string		genIndex(std::string path, std::string ip, int port);
//    std::string   genIndex(std::string path, std::string ip, int port);


		void	setCode(std::string const &c)
		{	_code = c;	}
		void	setType(std::string const &t)
		{	_type = t;	}
    void  setRedir(std::string const &t)
    { _redir = t; }

		std::string		getContent()
		{	return _content;	}
		std::string		getType()
		{	return _type;	}
		std::string		getCode()
		{	return _code;	}
    std::string   getRedC()
    {return _redir  ;}
	};
}

#endif
