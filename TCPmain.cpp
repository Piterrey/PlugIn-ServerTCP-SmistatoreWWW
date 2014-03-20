//FOR COMPILE: clear; g++ TCPmain.cpp -o main -Wno-format-security -Wno-write-strings -std=c++11
#define MAX_BUFFER 4096

#include <iostream>
using namespace std;

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TCP.hpp"
#include "WebPage.h"

int main(int argc, char const *argv[])
{
	int server_port,i;
	char* msgrec;	//Per i messaggi in recezione
	MultiFile* msg;	//Per i messaggi in invio
	char* header = "HTTP/1.1 202 OK\nDate: Mon, 23 May 2005 22:38:34 GMT\nServer: Apache/1.3.3.7 (Unix) (Red-Hat/Linux)\nLast-Modified: Wed, 08 Jan 2003 23:11:55 GMT\nAccept-Ranges: bytes\nConnection: close\n\n"; //Header HTTP


	if (argc !=2) {	printf("USAGE:%s PORT\n",argv[0]); return -1; }	//Se la porta non è presente, spiega l'utilizzo della funzione

	server_port = atoi(argv[1]);	//Converte la stringa in numero

	Address* addr = new Address("127.0.0.1",server_port);	//Istanzio il server in locale
	ServerTCP* server = new ServerTCP(server_port);		//Istanzio la classe server
	Conn_Server* client;	//Creo un client singolo su cui operare

	client = server->accetta(addr);	//Aspetto la connessione del client

	msgrec = client->ricevi();	//Ricevo la sua richiesta

	printf("\n#Richiesta#\n%s\n--------------\n",msgrec );

	msg=ConcactMulti(header,CheckHttpRequest(msgrec));	//Controlla la presenza del file e lo aggiungo all'HEADER HTTP

	client->inviaMulti(msg);	//Invio la risposta

	printf("\n#Risposta#\n");	//Leggo ogni carattere
	for (int i = 0; i < msg->lenght; ++i)printf("%c",msg->content[i] );
	printf("\n---------------\n";

	delete(addr);
	delete(server);
	delete(client);
	free(msg);
	return 0;
}
