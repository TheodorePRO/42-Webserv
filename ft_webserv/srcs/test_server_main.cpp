

#include <stdio.h>
#include "../incs/TestServer.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		std::cout << av[0] << " needs conf file" << std::endl;


	std::cout << "IN TEST SERVER CPP"<<std::endl;
	SAMATHE::ServConf	sc(av[1]); // obtenir parametres a partir d'un fichier do cinfig
	SAMATHE::TestServer t(sc);
}
