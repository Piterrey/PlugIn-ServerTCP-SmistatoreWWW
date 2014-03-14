#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <iostream>
using namespace std;

#include <unistd.h>

typedef struct sockaddr_in Addr_bin;	//Definizione del socket

/*Classe che gestisce gli indirizzi*/
class Address {
	private: 
		char* 	ip;	//Indirizzo IP
		int 	port;	//Porta

	public: 
		Address();	//Costruttore della classe vuoto
		Address(char* _ip, int _port);	//Costruttore della classe con indirizzo e porta
		Address(Addr_bin* _addr);	//Costruttore clonante da struttura

		char* 	get_ip();	//Restituisce l'indirizzo IP
		int 	get_port();	//Restituisce la porta dell'indirizzo
		void	set_ip(char* _ip);	//Imposta l'indirizzo IP
		void 	set_port(int _port);	//Imposta la porta dell'indirizzo IP

		void 	show();	//Mostra a consolo i dati contenuti nella glasse
		void 	set_addr( Addr_bin* _addr); //Imposta i parametri interni come l'indirizzo fornito
		Addr_bin* get_addr();	//Restituisce la struttura dell'indirizzo

		~Address();	//Distruttore
};




/*#################################### IMPLEMENTAZIONE ####################################*/
	
	//Costruttori
	Address::Address():Address("0.0.0.0",0) { }	//Passa dei valore di default per il costruttore senza parametri

	Address::Address(char* _ip, int _port){	
		ip = strdup(_ip);	//Copia la stringa e non solo il puntatore
		port = _port;
	}

	Address::Address(Addr_bin* _addr){
		ip=strdup(inet_ntoa(_addr->sin_addr));	//Estrae la stringa dalla struttura e ne esegue un duplicato
		port = ntohs(_addr->sin_port);	//Estrae la porta
	}

	//Proprietà
	char* 	Address::get_ip() { return strdup(ip); }	//Esegue duplicato

	int 	Address::get_port() { return port; }	//Wrapper

	void	Address::set_ip(char* _ip) {
		free(ip);	//Dealloca il contenuto di IP
		ip = strdup(_ip);	//Imposta la nuova stringa
	}

	void 	Address::set_port(int _port) { port=_port; }

	void 	Address::show(){
		cout << "addr:" << ip << ":" << port << endl;
	}

	//Metodi d'accesso
	void 	Address::set_addr( Addr_bin* _addr){
		free(ip);	//Dealloca
		ip=strdup(inet_ntoa(_addr->sin_addr));	//Estrae e duplica la stringa
		port = ntohs(_addr->sin_port);
	}

	Addr_bin* Address::get_addr(){
		Addr_bin* ret;
		ret = (Addr_bin*) malloc(sizeof(Addr_bin));	//Alloca lo spazio per la struttura

		ret->sin_family = AF_INET;	//Tipo indirizzo
		inet_aton(ip,&(ret->sin_addr));	//Imposta l'indirizzo IP
		ret->sin_port= htons(port);	//Imposta la porta
		for (int i=0;i<8;i++) { ret->sin_zero[i]=0; }	//Setta a 0 tutti gli elementi di "sin_zero"
		return ret;
	}

	//Distruttore
	Address::~Address() { free(ip); } //Dealloca la stringa

/*#########################################################################################*/

#endif 
