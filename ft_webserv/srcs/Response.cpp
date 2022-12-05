#include "../incs/Response.hpp"


namespace SAMATHE
{
	Response::Response(){}
	Response::~Response(){}

	void		Response::setC(std::string c)
	{		_content = c;	}

	int			Response::setContent(std::string page)
	{
		std::ifstream		file(page.c_str());
        std::cout << "----- file ----  " << file.is_open() << std::endl;
		if (file.is_open())
		{
			std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			_content = str;
			if (getCode() == "")
				setCode("200");
			setType(page.substr(page.find(".") + 1));
			file.close();
			return 1;
		}
		else
		{
			file.close();
			return 0;
		}
	}

	std::string		Response::genIndex(std::string path) 
	{
		std::string p2 = std::string(get_current_dir_name()) + "/" + path;
		std::cout << "----- DIR ----  " << p2 << std::endl;
		DIR *dir = opendir(p2.c_str());
		std::string page =\
						  "<!DOCTYPE html>\n\
						  <html>\n\
						  <head>\n\
						  <title>" + path + "</title>\n\
						  </head>\n\
						  <body>\n\
						  <h1>INDEX</h1>\n\
						  <p>\n";

		if (dir == NULL) {
			std::cerr << "Error: could not open [" << path << "]" << std::endl;
			return "";
		}
		if (path[0] != '/')
			path = "/" + path;
		for (struct dirent *dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir)) 
		{
			std::stringstream   ss;
			ss << "\t\t<p><a href=\"http://" << path + "/" + std::string(dirEntry->d_name) + "\">" + std::string(dirEntry->d_name) + "</a></p>\n";
			page += ss.str();
		}
		page +="\
				</p>\n\
				</body>\n\
				</html>\n";
		closedir(dir);
		return page;
	}

}
