

#include <stdio.h>
#include "../incs/TestServer.hpp"
#include "../incs/webserv.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << RED_TXT "Error: " << av[0]<< " needs conf file ." RESET_TXT << std::endl;
		return (EXIT_FAILURE);
	}
	//parser
	std::string inputPath(av[1]);
	GlobalConfiguration globalConf;
	ParserConf parser(inputPath, globalConf);	
	

	std::cout << "IN TEST SERVER CPP"<<std::endl;
	SAMATHE::ServConf	sc;
	SAMATHE::TestServer t(sc);
}
