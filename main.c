#include <stdio.h>
#include <stdlib.h>
#include "WebPage.h"	//Insieme alla libreria "stringa.h", richiamata al suo interno, rappresentano le funzioni per individuare la presenza dei file nelle cartelle

int main(int argc,char** argv){
	char* word;
	char* sup;

	if(argc!=2){ printf("USAGE: %s WORD\n",argv[0]); return -1; }	//	./main "GET /prova.html HTTP1/1"
	word=argv[1];

	sup = CheckHttpRequest(word);	//Eseguo l'analisi della richiesta HTTP
	if(sup) printf("\n\n\n%s\n", sup);	//Se è una richiesta HTTP restituisce una pagina
	else printf("RICHIESTA NON CORRETTA\n");	//Altrimenti messaggio d'errore

	return 0;
}