#ifndef TCP_HPP
#define TCP_HPP

#include "Socket.hpp"
#include "Address.hpp"
#include "List.hpp"
#include "WebPage.h"

#define MAX_BUFFER 4096	//Definisce la massima dimensione di un messaggio
#define COMMON_ADDR "0.0.0.0"	//Definisce l'indirizzo di default per i server
#define MAX_CONN 42	//Definisce il numero massimo di connessioni

/*Classe Socket per il TCP*/
class SocketTCP: public Socket
{
	public:
		SocketTCP();
		~ SocketTCP();
};

/*Classe per la gestione delle connessioni, erdita da nodo, percui è fruibile dalla lista*/
class Connessione : public Nodo
{
	protected:
		int _conn_id;	//Indica sia il codice del socket che la connessione del server
	public:
		Connessione(int conn_id, Nodo* next);	//Richiede l'identificativo di connessione e il puntatore all'elemento successivo
		~Connessione();	
		bool invia(char* msg);	//Invia un messaggio tramite protocollo TCP
		bool inviaMulti(MultiFile* msg);
		char* ricevi();	//Riceve un messaggio tramite protocollo TCP
};

/*Classe per la gestione delle connessioni dei Client, eredita da connessione*/
class Conn_Client : public Connessione
{
	public:
		Conn_Client(int sock_id);	//Riceve l'identificativo del socket
		~Conn_Client();
};

/*Classe per la gestione delle connessioni al Server, eredita da connessioni*/
class Conn_Server : public Connessione
{
	public:
		Conn_Server(int conn_id);	//Riceve l'identificativo della connessione al server
		~Conn_Server();
};

/*Classe per la gestione dei dati da parte di un client*/
class ClientTCP : public SocketTCP
{
	private:
		Conn_Client* connessione;	//Elemento per la gestione della connessione dei client
	public:
		ClientTCP();
		~ ClientTCP();

		Conn_Client* connetti(Address* server);	//Permette di connettersi a un server
		bool close_con();	//Chiude la connessione con esso
		bool invia(char* msg);	//Funzione per l'invio di dati
		char* ricevi();	//Funzioni per la recezione di dati
};

/*Classe per la gestione dei dati da parte del server*/
class ServerTCP : SocketTCP
{
	private:
		Lista* lista_connessione;	//Lista delle connessione a un server
	public:
		ServerTCP(int port);	//Imposta su una porta un server TCP
		~ServerTCP();

		Conn_Server* accetta(Address* client);	//Accetta una connessione di un client
		void close_tutte_connessioni();	//Funzione per la chiusura di tutte le connessioni
		void invia_a_tutti(char* msg);	//Funzione per l'invio di un determinato messaggio a tutti le connessioni aperte

};

/*################################### IMPLEMENTAZIONE #####################################*/
/*##################################### SOCKET-TCP ########################################*/

	SocketTCP::SocketTCP() : Socket(SOCK_STREAM){ }	//Richiama il costruttore di socket specificando il socket TCP
	SocketTCP::~SocketTCP(){ }

/*#################################### CONNESSIONI ########################################*/

	Connessione::Connessione(int conn_id, Nodo* next=NULL):Nodo(next){ _conn_id=conn_id; } //Accetta un identificativo e il prossimo elemento di una lista se inserito, altrimenti lo imposta automaticamente a NULL

	Connessione::~Connessione(){}

	bool Connessione::invia(char* msg){	
		int len_msg;
		int ret;

		len_msg = strlen(msg)+1;	//Aggiunge il carattere di fine stringa
		ret = send(_conn_id,msg,len_msg,0);	//Invia il messaggio per la sua lunghezza
		return (ret==len_msg);	//Compara la lunghezza del messaggio con i caratteri inviati
	}

	bool Connessione::inviaMulti(MultiFile* msg) 
	{
		int ret;
		ret = send(_conn_id,msg->content,msg->lenght,0);	//Invia il messaggio per la sua lunghezza
		return (ret==msg->lenght);	//Compara la lunghezza del messaggio con i caratteri inviati
	}

	char* Connessione::ricevi(){
		char buffer[MAX_BUFFER+1];	//Il buffer è più lungo per il carattere di fine stringa
		int ret;

		ret = recv(_conn_id,buffer,MAX_BUFFER,0);	//Riceve il messaggio

		if(ret<1){	
			return NULL;
		}

		buffer[ret]='\0'; //Imposta il carattere di fine stringa per sicurezza

		return strdup(buffer);	//Duplica la stringa poichè variabile interna
	}

/*#################################### CONN_CLIENT ########################################*/

	Conn_Client::Conn_Client(int sock_id) : Connessione(sock_id){ }	//Passa a connessione l'identificativo del socket
	Conn_Client::~Conn_Client(){ }	

/*#################################### CONN_SERVER ########################################*/

	Conn_Server::Conn_Server(int conn_id):Connessione(conn_id){}	//Passa l'identificativo di connessione alla classe padre

	Conn_Server::~Conn_Server(){ close(Connessione::_conn_id); }	//Richiama la chiusura dell'identificativo del padre

/*##################################### SERVER_TCP ########################################*/

	ClientTCP::ClientTCP(){}

	ClientTCP::~ClientTCP(){}

	Conn_Client* ClientTCP::connetti(Address* server){	//l'address fornisce l'indirizzo del server
		int ret;

		ret=connect(get_sock_id(),(struct sockaddr*) server->get_addr(),(socklen_t)sizeof(struct sockaddr)); 	//Connette all'indirizzo di server 
		if(ret){ return NULL; }
		return new Conn_Client(get_sock_id());	//Restituisce il socket di connessione al server nella connessione
	}

	bool ClientTCP::close_con() { delete(connessione); }	//Permetta la chiusura della connessione

	bool ClientTCP::invia(char* msg) { return connessione->invia(msg); };	//Richiama il metodo di invio della connessione

	char* ClientTCP::ricevi() { return connessione->ricevi(); };	//Richiama il metodo di recezione della connessione

/*##################################### CLIENT_TCP ########################################*/

	ServerTCP::ServerTCP(int port){
		int ret;
		lista_connessione = new Lista();	//Crea una lista dove andare a salvare i client
		Address* mySelf;
		
		mySelf = new Address(COMMON_ADDR,port);	//Prepara l'indirizzo con la porta indicata
		ret = bind(get_sock_id(),(struct sockaddr*)mySelf->get_addr(),(socklen_t)sizeof(struct sockaddr)); //Si collega alla porta per la recezzione dei dati
		if(ret){
			errore("SocketTCP - Errore nell'assegnazione della porta\n",-1);
		}

		ret = listen(get_sock_id(), MAX_CONN);	//Imposta il socket con il numero massimo di connessione a che potrà eseguire

		if(ret){
			errore("Errore nell'assegnazione nel numero di connessioni\n",-3);
		}

		delete(mySelf);
	}

	ServerTCP::~ServerTCP(){
		delete(lista_connessione);	//Richiama il distruttore della lista
	}

	Conn_Server* ServerTCP::accetta(Address* client){	//L'indirizzo verrà compilato dalla funzione
		Conn_Server* conn;
		int id;
		int len_addr;

		len_addr = sizeof(struct sockaddr_in);	//Per evitare errori per i valori non impostati bisogna impostare prima
		id = accept(get_sock_id(), (struct sockaddr*) client->get_addr(),(socklen_t*) &len_addr);		//Aspetta e accetta la connessione da un client scrivendo il suo indirizzo nei parametri client->get_addr

		if(id<=0){
			return NULL;
		}

		conn=new Conn_Server(id);	//Crea la connessione in base all'id

		lista_connessione->add_Nodo(conn);
		return conn;	//Ritorna la connessione per l'utilizzo separato dalla lista
	}	

	void ServerTCP::close_tutte_connessioni(){	
		Iterator* index = lista_connessione->create_Iterator();

		do{	//Fintanto non si è all'ultimo
			delete(index->get_current());	//elimina il nodo
			index->move_next();

		}while(index->is_done());
	}

	void ServerTCP::invia_a_tutti(char* msg){
		Iterator* index = lista_connessione->create_Iterator();

		do{	//Fintanto non si è all'ultimo
			((Conn_Server*)index->get_current())->invia(msg);	//Invia il messaggio
			index->move_next();

		}while(index->is_done());
	}

/*#########################################################################################*/

#endif