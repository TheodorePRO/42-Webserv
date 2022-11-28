#ifndef RECEPTION_HPP
# define RECEPTION_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "webserv.hpp"


//#include <iostream>

namespace SAMATHE
{
	class Reception
	{
		std::string									_method;
		std::string									_version;
		std::string									_page;
		std::string									_body;
		std::string									_fileLim;
		std::string									_fileName;
		size_t										_size;
	
	int 										_fd; //MS - new: pour gerer pusieurs fd
	//int					_status; // 0 = READ - 1 = Write - 2 = fini 

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
	Reception(int sd, ServerInParser &);
		~Reception(void);

		void	setReception(std::vector<std::string> &cut);
		void	setBody(std::string &justRecv);
void	setBody2(const std::string& str);
std::string&	pop(std::string& str);
		
		void	clearReception()
		{
			_body = "";
			_version = "";
			_page = "";
			_body = "";
			_fileLim = "";
			_fileName = "";
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

		std::string		getFName()
		{	return _fileName;	}


	//*******get_status()

	};

}

#endif
