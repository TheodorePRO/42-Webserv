#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <map>
#include <cstring>
#include <sys/wait.h>

std::map<std::string, std::string>	create_env(void) {

	std::map<std::string, std::string> envs;

	envs["CONTEXT_DOCUMENT_ROOT"] = "";
	envs["SERVER_SOFTWARE"] = "Webserv"; //The name and version of the software the server is running.
	envs["SERVER_NAME"] = "127.0.0.1"; //globalConf.getServersList().at(i).getNames().at(j); //The server's hostname or IP Address
	envs["GATEWAY_INTERFACE"] = "CGI/1.1";//
	envs["SERVER_PROTOCOL"] =  "HTTP/1.1";//
	envs["SERVER_PORT"] = "8080"; //globalConf.getServersList().at(i).getPort(); // The IP address of the remote host making the request. This is useful logging or for authentication: REMOTE_ADDR
	envs["REQUEST_METHOD"] = "GET";
	envs["PATH_INFO"] = "";//std::string("./") + _response->root + _response->url;// 
	envs["SCRIPT_NAME"] = std::string("/cgi/hello.py");//The name of the CGI script.
	envs["SCRIPT_FILENAME"] = std::string("/cgi/hello.py");//std::string("./") + _response->root + _response->url //The full path to the CGI script
	envs["QUERY_STRING"] = ""; // The URL-encoded information that is sent with GET method request.
	envs["REMOTE_HOST"] = "";//_response->fieldLines["Host"]; // REMOTE_HOST=207.0.0.1// The fully qualified name of the host making the request. If this information is not available, then REMOTE_ADDR can be used to get IR address
	envs["REMOTE_ADDR"] = "";//The IP address of the remote host making the request. This is useful logging or for authentication.
	envs["REMOTE_PORT"] = "";
	envs["REMOTE_USER"] = "";//
	envs["CONTENT_TYPE"] = "";//_response->fieldLines["Content-Type"];
	envs["CONTENT_LENGTH"] = "";//get_length();
	envs["HTTP_USER_AGENT"] = "Google Chrome Version 107.0.5304.110 (Official Build) (64-bit)";//_response->httpVersion;// It is name of the web browser.
//	envs["HTTP_COOKIE"] = _response->fieldLines["Cookie"];//PHPSESSID=rbp9ts7miftn1h5jmja928v58u
	return envs;
}

// CONTENT_TYPE // The data type of the content. Used when the client is sending attached content to the server. For example, file upload.
// CONTENT_LENGTH // The length of the query information. It is available only for POST requests.
// HTTP_COOKIE //Returns the set cookies in the form of key & value pair.
// HTTP_USER_AGENT //The User-Agent request-header field contains information about the user agent originating the request. It is name of the web browser.
// PATH_INFO // The path for the CGI script.
// QUERY_STRING // 
// SCRIPT_FILENAME
// SCRIPT_NAME

void	free_env (char **env)
{
	for (int i = 0; env[i + 1]; i++) {
		free(env[i]);
	}
	free(env);
}



int main()
{
	//int	tmp_fd = dup(STDIN_FILENO);
	int	pipefd[2];
	pid_t pid;
	int _code_resp;

	/***    prepare execve data ***/
	std::map<std::string, std::string> envs;
	
	envs["CONTEXT_DOCUMENT_ROOT"] = "";
	envs["SERVER_SOFTWARE"] = "Webserv"; 
	envs["SERVER_NAME"] = "127.0.0.1"; 
	envs["GATEWAY_INTERFACE"] = "CGI/1.1";
	envs["SERVER_PROTOCOL"] =  "HTTP/1.1";
	envs["SERVER_PORT"] = "8080"; 
	envs["REQUEST_METHOD"] = "GET";
	envs["PATH_INFO"] = "";
	envs["SCRIPT_NAME"] = std::string("/test/hello.py");
	envs["SCRIPT_FILENAME"] = std::string("/test/hello.py");
	envs["QUERY_STRING"] = ""; 
	envs["REMOTE_HOST"] = ""; 
	envs["REMOTE_ADDR"] = ""; 
	envs["REMOTE_PORT"] = "";
	envs["REMOTE_USER"] = "";
	envs["CONTENT_TYPE"] = "";
	envs["CONTENT_LENGTH"] = "";
	envs["HTTP_USER_AGENT"] = "Google Chrome Version 107.0.5304.110 (Official Build) (64-bit)";



	std::string	key;
	int j = 0;
	int size = envs.size() + 1;
	char *env[size];
	for(std::map<std::string, std::string>::iterator it = envs.begin(); it != envs.end(); it++)
	{
		std::cout << it->first << " = " << it->second << std::endl;
					//for (size_t i = 0; i < key.size(); ++i) {
					// if (key[i] == '-') {
					//     key[i] = '_';
					// } else if (key[i] == ':') {
					//     key[i] = '=';
					// } else {
					//     key[i] = std::toupper(key[i]);
					// }
		key = it->first + "=" + it->second;
		env[j++] = strdup(key.c_str());
	}
	env[j] = NULL;
	std::cout << "======================================================" << std::endl;
	for (size_t i = 0; i < size; ++i){
		std::cout << env[i] << std::endl;
	}


//		std::string tmp = getProgName(path);
		std::string binPath = "hello.py";
		std::string progPath = "/test/hello.py";
//		const char* pythonPath = "/usr/bin/python";
		char* argv[3] = {(char*)binPath.c_str(), (char*)progPath.c_str(), NULL };

        if (argv[0] == NULL or argv[1] == NULL) {
            // free(cmd[0]);
            // free(cmd[1]);
            _code_resp = 500;
    //        send_resp(fd);
			return (EXIT_FAILURE);
        }

	pid = fork();
	if (pid == -1) {
		//free_env(env);
		//send_resp(fd, 500);
		perror("fork");
		return (EXIT_FAILURE);
	}
std::cout << "pid = " << pid << std::endl;
	if (pid == 0) // child
	{
		int outFD = open("out.txt", O_RDWR | O_CREAT | O_TRUNC, 0666); //open for write
		if (outFD < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }
std::cout << "outFD = " << outFD << std::endl;
		if(dup2(outFD, STDOUT_FILENO) == -1)
		{
          	//free_env(env);
			perror("dup2 IN");
            exit(EXIT_FAILURE);			
		}
		// if(dup2(pipefd[1], STDOUT_FILENO) == -1)
		// {
        //     free_env(envp);
		// 	perror("dup2 OUT");
        //     exit(EXIT_FAILURE);			
		// }
std::cout << "outFD_new =" << outFD << std::endl;
std::cout << "STDOUT_FILENO = " << STDOUT_FILENO << std::endl;		
		close(outFD);
		execve(argv[0], argv, env);
		//free_env(env);
        perror("execve");
        exit(EXIT_FAILURE);

	}
	else
	{
		int stat;
		//free_env(env);
		waitpid(pid, &stat, 0);
		//close(outFD);
		// tmp_fd = dup(STDIN_FILENO);
	}
	return EXIT_SUCCESS;
}
