#ifndef WEBPAGE_H
#define WEBPAGE_H

#include "stringa.h"
#include <stdio.h>
#include <stdlib.h>

//La richiesta HTTP si presenta come "GET /index.html HTPP" nella versione 1.0 e 1.1 [20/03/2014]

#define HTTP_GET_HEAD "GET "	//Intestazione della richiesta HTTP
#define HTTP_GET_FOOT " HTTP"	//Coda della richiesta HTTP

#define PAGE404 "./404.html"	//Indirizzo della pagina 404

/*############# Prototipi ###############*/
char* GetPathByRequest(char* HTTP_Request);	//Data una richiesta HTTP restituisce il path del file richiesto o NULL
MultiFile* CheckPageExistence(char* path);	//Dato un path, controlla la sua esistenza e lo legge oppure ritorna la 404

MultiFile* CheckHttpRequest(char* HTTP_Request); //Unione delle due precedenti, data una richiesta HTTP restituisce un file oppure 404

MultiFile* ConcactMulti(char* str1, MultiFile* str2);	//una stringa a un file letto

/*############# Struttura ###############*/

typedef struct 
{
	char* content;	//puntatore a una stringa
	int lenght;		//Lunghezza della stringa (per evitare eventuali falsi tappi '\0' nei file non testuali)

} MultiFile;	//Descrive la struttura di un file 

/*########### Implementazione ##############*/
MultiFile* CheckHttpRequest(char* HTTP_Request){
	char* sup;
	MultiFile* ret;

	sup = GetPathByRequest(HTTP_Request);	//Converte la richiesta HTTP in path
	if(!sup) return sup;	//se non è una richiesta HTTP sup è a NULL

	sup = stringConcat("./www",GetPathByRequest(HTTP_Request));	//aggiunge la cartella di riferimento per vedere se il file è all'interno di essa
	ret = CheckPageExistence(sup);	//Controllo la sua esistenza

	return (ret)? ret : CheckPageExistence(PAGE404);;	//Se esiste il file restituisce esso, altrimenti legge il 404
}

MultiFile* CheckPageExistence(char* path){
	MultiFile* ret;
	FILE* fp;
	char* text;
	int size;
	
	fp = fopen(path, "rb+");	//Apre il file in lettura binaria [con possibilità di scrittura per debug]
	
	if(fp){	//se punta a qualcosa

		ret = (MultiFile*)malloc(sizeof(MultiFile));	//Alloco il contenitore per il contenuto del file

		fseek(fp, 0, SEEK_END); 	//Vado a fine file
		ret->lenght = ftell(fp);	//Mi segno quanti caratterri ci sono dall'inizio del file
		fseek(fp, 0, SEEK_SET);		//Torno all'inizio
		
		ret->content = (char*)calloc((ret->lenght+1),sizeof(char));	//Alloco il numero di elementi (+1 tappo) e metto tutti a zero

		fread(ret->content,sizeof(char),ret->lenght,fp);	//Leggo il contenuto del file e lo inserisco nel conenitore

		fclose(fp);
		return ret;
	}
	else return NULL;	//Se il file non è aperto non esiste
}

char* GetPathByRequest(char* HTTP_Request){	
	int start,stop;

	start = getFistIndex(HTTP_Request,HTTP_GET_HEAD);	//Cerco la prima coincidenza dell'apertura della richiesta della pagina
	stop = getFistIndex(HTTP_Request,HTTP_GET_FOOT);	//Cerco l'ultima corrispondeza per la chiusura della richiesta

	if(start>=0 && stop>=0) return getSubString(HTTP_Request, start+strlen(HTTP_GET_HEAD), stop-start-strlen(HTTP_GET_HEAD));	//Se entrambi sono presenti estraggo la sotto stringa
	return NULL;	//La stringa non è una richiesta HTTP
}

MultiFile* ConcactMulti(char* str1, MultiFile* str2)
{
	MultiFile* ret;
	int i,j,lg;

	ret = (MultiFile*)malloc(sizeof(MultiFile));	//Alloco nuovo contenitore

	lg = strlen(str1);	//Prendo la lunghezza extra
	ret->lenght = lg+str2->lenght;	//Inserisco la nuova lunghezza
	ret->content = (char*)malloc((sizeof(char)*ret->lenght)+1);	//Allogo la nuova stringa
	
	for (i = 0; i < lg; ++i) ret->content[i]=str1[i];	//Copio la prima stringa
	for (j = 0; j < str2->lenght; ++j) ret->content[i+j]=str2->content[j];	//Seguita dalla successiva

	ret->content[ret->lenght + 1]='\0';	//Imposto il carattere di fine stringa

	return ret;	//Duplico la variabile locale
}

#endif 