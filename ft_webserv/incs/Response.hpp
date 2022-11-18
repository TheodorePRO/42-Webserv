#ifndef RESPONSE_HPP
# define RESPONSE_HPP

#include <string>

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

		void	setContent(std::string const &h)
		{	_content = h;	}
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
