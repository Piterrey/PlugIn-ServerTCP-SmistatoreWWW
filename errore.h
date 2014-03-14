#ifndef ERROR_H
#define ERROR_H

#include <errno.h>

//Funzione per la stampa l'uscita e la stampa degli errori
void errore(char* msg, int ret_code){
	printf(msg);
	printf(" | errcode:%d (%s)\n",errno,strerror(errno));	//Stampa a schermo la l'errore
	exit(ret_code);	//Esce dal processo con il valore impostato
}

#endif