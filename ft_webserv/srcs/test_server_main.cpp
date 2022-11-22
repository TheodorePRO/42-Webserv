

#include <stdio.h>
#include "../incs/TestServer.hpp"
#include "../incs/webserv.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		std::cout << av[0] << " needs conf file" << std::endl;
	
	// 1 check if all cgi binaries are available

	// 2 check if all default error pages exist

	// 3 parsing	
		// std::string inputPath(av[1]);
		// GlobalConfiguration globalConf;
		//ConfigurationParser parser(inputPath, globalConf);	
		//globalConf.startEngines();		

	std::cout << "IN TEST SERVER CPP"<<std::endl;
	SAMATHE::ServConf	sc;
	SAMATHE::TestServer t(sc);
}
