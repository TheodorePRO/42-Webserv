#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <map>
#include <cstring>
#include <sys/wait.h>
#include "../incs/webserv.hpp"
#include "../incs/ClientS.hpp"

namespace SAMATHE
{
    void	ClientS::free_env (char **env)
    {
        for (int i = 0; env[i]; i++) {
            free(env[i]);
        }
        delete[]env;
    }

    char**    ClientS:: makeEnviroment(ServerInParser conf) 
    {
        std::map<std::string, std::string> envs; /***  prepare execve data ***/
        std::ostringstream ss_port;

        ss_port << conf.getPort();
        envs["SERVER_SOFTWARE"] = "Webserv"; 
        envs["SERVER_NAME"] = conf.getIP();
        envs["GATEWAY_INTERFACE"] = "CGI/1.1";
        envs["SERVER_PROTOCOL"] =  "HTTP/1.1";
        envs["SERVER_PORT"] = ss_port.str();    
        envs["REQUEST_METHOD"] = "GET";
        envs["PATH_INFO"] = std::string("pages/cgi/"); // The path for the CGI script.
        envs["SCRIPT_NAME"] = std::string("hello.py"); //The name of the CGI script.
        envs["REMOTE_HOST"] = ""; //The fully qualified name of the host making the request. If this information is not available, then REMOTE_ADDR can be used to get IR address
        envs["REMOTE_ADDR"] = ""; //The IP address of the remote host making the request. This is useful logging or for authentication.
        envs["REMOTE_PORT"] = "";
        envs["REMOTE_USER"] = "";
        envs["CASHE-CONTROL"] = "no-cache"; //The data type of the content. Used when the client is sending attached content to the server. For example, file upload.
        envs["CONTENT_TYPE"] = "text/html"; //The data type of the content. Used when the client is sending attached content to the server. For example, file upload.       
        envs["CONTENT_LENGTH"] = "5000"; // It is available only for POST requests.
        envs["HTTP_USER_AGENT"] = "Google Chrome Version 107.0.5304.110 (Official Build) (64-bit)";

        std::string	key;
        int   j = 0;
        int size = envs.size() + 1;
        char **env = new char*[size];
        for(std::map<std::string, std::string>::iterator it = envs.begin(); it != envs.end(); it++)
        {
            key = it->first + "=" + it->second;
            env[j++] = strdup(key.c_str());
        }
        env[j] = NULL;

        return env;
    }


    int		ClientS::cgi(int fd, char* argv[], char *env[])	
    {
        int	tmp_fd = dup(STDIN_FILENO);

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return EXIT_FAILURE;
        }
        if (pid == 0) 
        {
            if(dup2(fd, STDOUT_FILENO) == -1)
            {
                perror("dup2 IN");
                return EXIT_FAILURE;			
            }
            close(fd);
            execve(argv[0], argv, env);
            perror("execve");
            return EXIT_FAILURE;
        }
        else 
        {
            int stat;
            close(tmp_fd);
            waitpid(pid, &stat, 0);
            tmp_fd = dup(STDIN_FILENO);
        }
        return EXIT_SUCCESS;
    }   

    int     ClientS::makeCgiRequest(int fd, ServerInParser conf)
    {
        char** env = makeEnviroment(conf);

        std::string binPath = "/usr/bin/python3"; 
		std::string progPath = "pages/cgi/hello.py";
		char* argv[3] = {(char*)binPath.c_str(), (char*)progPath.c_str(), NULL };

        if (argv[0] == NULL or argv[1] == NULL)
			return EXIT_FAILURE;
        int status = cgi(fd, argv, env);
        free_env(env);
        if (EXIT_FAILURE==status)
            return EXIT_FAILURE;

        return EXIT_SUCCESS;
    }
}
