#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include "errore.h"

class Socket
{
	private:	
		int sock_id;
	public:		
		Socket(int mode);	//Costruttore con Modalità richiesta dal socket
		~Socket();

		int get_sock_id();	//Restituisce l'identificativo del socket
};

/*#################################### IMPLEMENTAZIONE ####################################*/

	Socket::Socket(int mode){
		sock_id=socket(AF_INET,mode,0);	//Istanzio il socket in relazione alla modalità TCP/UDP
		if(sock_id<0) { errore("Errore Socket Server",-1); }	//Richiamo la funzione di errore
	}

	Socket::~Socket(){
		shutdown(sock_id, SHUT_RDWR);	//Richiamo la funzione per la chiusura della connessione e del socket
		close(sock_id);	//Elimino il socket
	}

	int Socket::get_sock_id(){
		return sock_id;
	}

/*#########################################################################################*/

#endif
