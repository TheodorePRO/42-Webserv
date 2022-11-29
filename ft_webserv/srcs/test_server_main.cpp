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


	std::cout << GREEN_TXT"\nTemporary printe for result of parsing : \n\n";
	for ( unsigned int i = 0; i < globalConf.getServersList().size(); i++)
	{
		std::cout << "for server number " << i << " : \n";
		std::cout << "Ip = " << globalConf.getServersList().at(i).getIP() << std::endl;
		std::cout << "Port = " << globalConf.getServersList().at(i).getPort() << std::endl<< std::endl;
	}
	std::cout << RESET_TXT"IN TEST SERVER CPP"<<std::endl;
	//SAMATHE::ServConf	sc(av[1]); // obtenir parametres a partir d'un fichier do cinfig
	
	SAMATHE::TestServer testServer(globalConf);
}
