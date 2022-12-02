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

		public :
		Response(void);
		~Response(void);

		int				setContent(std::string page);
		void			setC(std::string c);
		std::string		genIndex(std::string path);

		void	setCode(std::string const &c)
		{	_code = c;	}
		void	setType(std::string const &t)
		{	_type = t;	}

		std::string		getContent()
		{	return _content;	}
		std::string		getType()
		{	return _type;	}
		std::string		getCode()
		{	return _code;	}
	};
}

#endif
