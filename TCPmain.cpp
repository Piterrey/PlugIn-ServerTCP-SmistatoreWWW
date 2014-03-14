/*FOR COMPILE: clear; g++ TCPmain.cpp -o main -Wno-format-security -Wno-write-strings -std=c++11*/
#define MAX_BUFFER 4096

#include <iostream>
using namespace std;

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "errore.h"
#include "Socket.hpp"
#include "Address.hpp"
#include "List.hpp"
#include "TCP.hpp"
#include "WebPage.h"

int main(int argc, char const *argv[])
{
	char* msgrec;
	char* msg;
	char* header = "HTTP/1.1 200 OK\n\
Date: Mon, 23 May 2005 22:38:34 GMT\n\
Server: Apache/1.3.3.7 (Unix) (Red-Hat/Linux)\n\
Last-Modified: Wed, 08 Jan 2003 23:11:55 GMT\n\
Accept-Ranges: bytes\n\
Connection: close\n\
\n";

	int server_port;

	if (argc !=2) {	
		printf("USAGE:%s PORT\n",argv[0]);
		return -1; 
	}

	server_port = atoi(argv[1]);

	Address* addr = new Address("127.0.0.1",server_port);
	ServerTCP* server = new ServerTCP(server_port);
	Conn_Server* client;

	client = server->accetta(addr);

	msgrec = client->ricevi();

	printf("#Richiesta#\n%s\n--------------\n\n",msgrec ); //Richiesta

	msg=stringConcat(header,CheckHttpRequest(msgrec));

	client->invia(msg);

	printf("#Risposta#\n%s\n---------------\n\n",msg);	//Risposta

	delete(addr);
	delete(server);
	delete(client);
	return 0;
}
