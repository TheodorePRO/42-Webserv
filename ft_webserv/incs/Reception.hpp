#ifndef RECEPTION_HPP
# define RECEPTION_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>


//#include <iostream>

namespace SAMATHE
{
	class Reception
	{
		std::string									_method;
		std::string									_version;
		std::string									_page;
		std::string									_body;
		size_t										_size;

/*
		std::map<std::string, std::string>			_headers;
		std::map<std::string, std::string>			_env_for_cgi;
		int											_ret;
		int											_port;
		std::string									_path;
		std::string									_query;
		std::list<std::pair<std::string, float> >	_lang;
		const std::string&							_raw;
		std::string					_content;

		std::string					_type;
		std::string					_code;
*/
		public :
		Reception(void);
		~Reception(void);

		void setReception(std::vector<std::string> &cut);
		void setBody(std::string	justRecv)
		{	_body = justRecv; }
		
		void clearReception()
		{
			_body = "";
			_version = "";
			_page = "";
			_body = "";
			_size = 0;
		}
		void		setSize()
		{	_size = 0;	}

		std::string		getMethod()
		{	return _method;	}
		std::string		getPage()
		{	return _page;	}
		std::string		getBody()
		{	return _body;	}
		std::string		getVersion()
		{	return _version;	}
		size_t		getSize()
		{	return _size;	}
	};

}

#endif
