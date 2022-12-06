#include "../../incs/webserv.hpp"

// CPP spliter
std::vector<std::string>	split(const std::string &str, char delim)
{
	std::size_t i = 0;
	std::vector<std::string> list;

	std::size_t pos = str.find(delim);

	while (pos != std::string::npos)
	{
		list.push_back(str.substr(i, pos - i));
		i = ++pos;
		pos = str.find(delim, pos);
	}

	list.push_back(str.substr(i, str.length()));

	return list;
}

std::vector<std::string>	split(const std::string &str, const char *set_delim)
{
	std::size_t i = 0;
	std::vector<std::string> list;

	std::size_t pos = str.find_first_of(set_delim);

	while (pos != std::string::npos)
	{
		if (pos == i)
		{
			i = ++pos;
		}
		else
		{
			list.push_back(str.substr(i, pos - i));
			i = ++pos;
		}
		pos = str.find_first_of(set_delim, pos);
	}
	
	if (i != str.length())
		list.push_back(str.substr(i, str.length()));

	return list;
}

bool						is_digit(std::string str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

/**
 *  path----> String containing the path
 *  IsFolder----> Default value = true. 
 * ==> Return 'true' if the path is likely to be a folder
 */
bool	is_folder_formatted(std::string path, bool IsFolder)
{
	for (std::string::reverse_iterator rit = path.rbegin(); rit != path.rend(); ++rit)
	{
		if (*rit == '.')
			return false;
		else if (*rit == '*' && IsFolder)
			return true;
		else if (*rit == '/')
			return true;
	}
	return true;
}

std::string					int_to_string(int n)
{
	return SSTR("" << n);
}