# 42-Webserv
WebServ

- NameSpace = SAMATHE = Saray; Mariya, Théodore

- TestServer OBJECT : 
Object instance of Server
* Launch function that launches in infinite loop : 
		Accept-> to receive messages : 
		Handler-> to fetch the answer
		Responder -> to send response
* Accepter function : 
	- stores in address the address of the socket
	- ** The accept system call grabs the first connection request on the queue (set up in listen) and creates a new socket for that connection.
	- ** to read and store in Buffer the message
* Handler function :
	- ...
* Responder function :
	- ... Send a new message
	- closes the new socket

xxx  It uses a Buffer (BAD BAD BAD)

- Server OBJECT :	
Launch / Accpter / handler and responder are virtual.
	- It instantiate a ListeningSocket in constructor.
	- It as a getter for the socket object.)

-------

- Socket OBJECT
ARE GIVEN :
avec #include <sys/socket.h>
int sock = socket(domain, type, protocol);
	Domain :	AF_INET
	Type :		SOCK_STREAM
	Protocol :	0
Address structure = sockaddr : generic container
->
Create a socket : 
1 fill addresss.sin_family (domain) + .sinport (prot) + .sin_addr = interface
2 sock = socket(...);

- Binding Socket OBJECT :
given function "bind" links address to incoming "line"

- Listening Socket OBJECT :
	- it instantiates a BindingSocket in constructor
	- The listen system call tells a socket that it should be capable of accepting incoming connections
		(backloag is the max nb of conexions it can queue)

NGinX configuraitiion
# pour commentaires
lignes finissent par ";"
user
worker_processes
error_log
pid
events {}
http {} directives for web traffic handling contains
	- include /etc/nginx/mime.types; <- lieu de fichier de conf du serveurdu

SERVER conf file
server {
listen 80 default_server;
listen [::]:80 default_server;   (for ipv6)
server_name example.com www.example.com;	
server_name *.example.com;	(+subdomains)
server_name example.com.*;	(+all domain naims starting with ..)


root /var/www/example.com;
index index.html;
try_files $uri /index.html;
}

