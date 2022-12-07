#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h> // For sockaddr_in
# include <arpa/inet.h>	// For inet_addr
# include <sys/stat.h> // For directory testing
# include <unistd.h>
# include <stdio.h>
# include <poll.h> // for poll
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h> // For directory listing

# include <cstdlib>
# include <vector>
# include <map>
# include <set>
# include <fstream>
# include <string>
# include <iostream>
# include <sstream>

enum ERRER
{
	BAD_REQUEST = 400,
	FORBIDDEN = 403,
	NOT_FOUND = 404,
	METHOD_NOT_ALLOWED = 405,
	SERVER_ERROR = 500
};

# define BAD_REQUEST_DEFAULT		"error/400.html"
# define FORBIDDEN_DEFAULT			"error/403.html"
# define NOT_FOUND_DEFAULT			"error/404.html"
# define METHOD_NOT_ALLOWED_DEFAULT	"error/405.html"
# define SERVER_ERROR_DEFAULT		"error/500.html"

# define SSTR(x) static_cast<std::ostringstream &>(           \
					(std::ostringstream() << std::dec << x)) \
					.str()

# include "./parsConf/GlobalConfiguration.hpp"
# include "./parsConf/Location.hpp"
# include "./parsConf/ServerInParser.hpp"
# include "./parsConf/ParserConf.hpp"
# include "./Reception.hpp"
# include "./Response.hpp"

# define RED_TXT "\e[31m"
# define GREEN_TXT "\e[32m"
# define YELLOW_TXT "\e[33m"
# define BLUE_TXT "\e[34m"
# define MAG_TXT "\e[35m"

# define BOLD_TXT "\e[1m"
# define ITALIC_TXT "\e[2m"
# define UL_TXT "\e[4m"

# define RESET_TXT "\e[0m"

# define DEBUG(x)		std::cerr << YELLOW_TXT << x << RESET_TXT;
# define FATAL_ERR(x)	std::cerr << RED_TXT << x << RESET_TXT;
# define INFO(x)		std::cerr << ITALIC_TXT << x << RESET_TXT;
# define RUNTIME_MSG(x)	std::cerr << GREEN_TXT << x << RESET_TXT;


// CPP functions
std::vector<std::string>	split(const std::string &str, char delim);
std::vector<std::string>	split(const std::string &str, const char *set_delim);
std::string					autoindexPageHtml(std::string directoryName, std::string headerURL);
std::string					int_to_string(int n);
bool						is_digit(std::string str);
bool						is_folder_formatted(std::string path, bool IsFolder = true);

#endif
