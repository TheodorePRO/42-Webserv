#include <cstdio> 
#include <csignal>
#include <cerrno>
#include "../incs/TestServer.hpp"
#include "../incs/webserv.hpp"

void	signalHandler(int sig) {
	if (sig == SIGINT)
		throw std::runtime_error("\nServer is closed by user");
	if (sig == SIGPIPE)
        throw std::runtime_error("Server catch SIGPIPE");
}

int main(int ac, char **av)
{
	std::cout.setf(std::ios::unitbuf);
	if (ac != 2)
	{
		std::cout << RED_TXT "Error: " << av[0]<< " needs conf file ." RESET_TXT << std::endl;
		return (EXIT_FAILURE);
	}
	try{
		//parser
		std::string inputPath(av[1]);
		GlobalConfiguration globalConf;
		ParserConf parser(inputPath, globalConf);


		std::cout << GREEN_TXT"\nTemporary printe for result of parsing : \n\n";
		for ( unsigned int i = 0; i < globalConf.getServersList().size(); i++)
		{
			std::cout << GREEN_TXT"for server number " << i << " : \n";
			std::cout << "Ip = " << globalConf.getServersList().at(i).getIP() << std::endl;
			std::cout << "Port = " << globalConf.getServersList().at(i).getPort() << std::endl;
			std::cout << "Autoindex = " << globalConf.getServersList().at(i).isAutoindexed() << std::endl;
			std::cout << "Root = " << globalConf.getServersList().at(i).getRoot() << std::endl;
			
			std::cout << "Error_pages = " << globalConf.getServersList().at(i).getErrorPagePath(404) << std::endl;
			/*std::map<int, std::string>::iterator itr;
			std::cout << "ok\n";
			for(itr=globalConf.getServersList().at(i).getMapErrorPage().begin()
				;itr!=globalConf.getServersList().at(i).getMapErrorPage().end();itr++)
			{
				std::cout<<itr->first<<" "<<itr->second<<std::endl;
			}*/
			if(globalConf.getServersList().at(i).getClientBufferSize() != 0)
				std::cout << "client_max_body_size = " << globalConf.getServersList().at(i).getClientBufferSize() << std::endl;

			std::cout << " Names of server :"<< std::endl;
			for (std::size_t j = 0; j < globalConf.getServersList().at(i).getNames().size(); ++j)
				std::cout << "\tServer_name = " << globalConf.getServersList().at(i).getNames().at(j) << std::endl;
				//_currentServer->addName(line_items[i]);
			std::cout<< std::endl<<std::endl;

			std::cout << YELLOW_TXT"Elements in Locations blocks ********************************************************************************* " << std::endl;																			
			for (std::size_t k = 0; k < globalConf.getServersList().at(i).getRoutes().size(); ++k)																//-----
			{																																					//  L  |
				//std::cout << YELLOW_TXT"\nRoot = " << globalConf.getServersList().at(i).getRoutes().at(k).getRoot() << std::endl;								//  O  |			
				std::cout << "Prefix = " << globalConf.getServersList().at(i).getRoutes().at(k).getPrefix() << std::endl;										//  C  |	
																																								//  A  |
				for (std::set<std::string>::iterator it = globalConf.getServersList().at(i).getRoutes().at(k).getAllowedMethods().begin();						//  C  |
					it !=globalConf.getServersList().at(i).getRoutes().at(k).getAllowedMethods().end(); ++it)													//  T  |
					std::cout << "AllowedMethods = " << *it << " ";																							//  I  |
				std::cout << std::endl;	 																														//  O  |
																																								//  N  |
				//std::cout << "Prefix = " << globalConf.getServersList().at(i).getRoutes().at(k).getPrefix() << std::endl;
				std::cout << "IndexPage = " << globalConf.getServersList().at(i).getRoutes().at(k).getIndexPage() << std::endl;									//     |
				//std::cout << "Autoindex = " << globalConf.getServersList().at(i).getRoutes().at(k).isAutoindexed() << std::endl;								//  B  |
				std::cout << "isRedirected = " << globalConf.getServersList().at(i).getRoutes().at(k).isRedirected() << std::endl;								//  L  |
				std::cout << "Number of redirection = " << globalConf.getServersList().at(i).getRoutes().at(k).getRedirection().first							// ock |	
							<<"\t" <<"ULR of Redirection = " << globalConf.getServersList().at(i).getRoutes().at(k).getRedirection().second<<std::endl<<std::endl;		    //----
			}
			std::cout <<"\n*******************************************************************************************************************************\n" << RESET_TXT;
		}
		std::cout << RESET_TXT"IN TEST SERVER CPP"<<std::endl;
		//SAMATHE::ServConf	sc(av[1]); // obtenir parametres a partir d'un fichier do cinfig
		
		
				
		signal(SIGINT, signalHandler);
		signal(SIGPIPE, signalHandler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		SAMATHE::TestServer testServer(globalConf);
	}
	catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;

}
