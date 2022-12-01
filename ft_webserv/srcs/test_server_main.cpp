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
		std::cout << "Port = " << globalConf.getServersList().at(i).getPort() << std::endl;

		if(globalConf.getServersList().at(i).getClientBufferSize() != -1)
			std::cout << "client_max_body_size = " << globalConf.getServersList().at(i).getClientBufferSize() << std::endl;

		std::cout << " Names of server :"<< std::endl;
		for (std::size_t j = 0; j < globalConf.getServersList().at(i).getNames().size(); ++j)
			std::cout << "\tServer_name = " << globalConf.getServersList().at(i).getNames().at(j) << std::endl;
			//_currentServer->addName(line_items[i]);
		std::cout<< std::endl<<std::endl;

		std::cout << YELLOW_TXT"Elements in Locations blocks *** " << std::endl;
		for (std::size_t k = 0; k < globalConf.getServersList().at(i).getRoutes().size(); ++k)
		{
			std::cout << YELLOW_TXT"\nRoot = " << globalConf.getServersList().at(i).getRoutes().at(k).getRoot() << std::endl;
			std::cout << "Prefix = " << globalConf.getServersList().at(i).getRoutes().at(k).getPrefix() << std::endl;
			
			for (std::set<std::string>::iterator it = globalConf.getServersList().at(i).getRoutes().at(k).getAllowedMethods().begin();
				 it !=globalConf.getServersList().at(i).getRoutes().at(k).getAllowedMethods().end(); ++it)
				 std::cout << "AllowedMethods = " << *it << " ";
			std::cout << std::endl;	 
			//std::cout << "AllowedMethods = " << globalConf.getServersList().at(i).getRoutes().at(k).getAllowedMethods() << std::endl;
			
			std::cout << "IndexPage = " << globalConf.getServersList().at(i).getRoutes().at(k).getIndexPage() << std::endl;
			std::cout << "Autoindex = " << globalConf.getServersList().at(i).getRoutes().at(k).isAutoindexed() << std::endl;
			std::cout << "isRedirected = " << globalConf.getServersList().at(i).getRoutes().at(k).isRedirected() << std::endl;
			std::cout << "Number of redirection = " << globalConf.getServersList().at(i).getRoutes().at(k).getRedirection().first
			           <<"\t" <<"ULR of Redirection = " << globalConf.getServersList().at(i).getRoutes().at(k).getRedirection().second<<std::endl;
		}
		std::cout <<"\n*******\n"RESET_TXT;
	}
	std::cout << RESET_TXT"IN TEST SERVER CPP"<<std::endl;
	//SAMATHE::ServConf	sc(av[1]); // obtenir parametres a partir d'un fichier do cinfig
	
	SAMATHE::TestServer testServer(globalConf);
}
