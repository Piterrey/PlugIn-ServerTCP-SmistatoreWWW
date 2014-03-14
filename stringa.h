#ifndef STRINGA_H
#define STRINGA_H

#include <string.h>	

/*############# Prototipi ###############*/
int getFistIndex(char* str1, char* str2);	//Indica la prima occorrenza della stringa str2 in str1
int getFistIndexFrom(char* str1, char* str2, int start);	//Indica la prima occorrenza della stringa str2 in str1 a partire dal carattere start
char* getSubString(char* str,int start, int lenght);	//Restituisce la sottostringa indicata
char* stringConcat(char* str1, char* str2);	//Concatena due stringhe in una sola

/*########### Implementazione ##############*/
int getFistIndex(char* str1, char* str2){
	getFistIndexFrom(str1,str2,0);	//Parto dal primo carattere in str1
}

int getFistIndexFrom(char* str1, char* str2,int start){
	int i,j;
	for (i = start; i < strlen(str1); ++i)	//Per ogni caratere in str1 a partire da start compreso
	{
		j=0;
		while(str1[i+j]==str2[j]) j++;	//Comparo le due stringhe se trovo occorrenza
		if(j==strlen(str2)) return i;	//Se le occorrenze sono tante quanti i caratteri restituisco l'indice iniziale della prima occorrenza
	}

	return -1;
}

char* getSubString(char* str,int start, int lenght){
	char ret[lenght];	//Imposto la nuova stringa di lunghezza ret
	int i;

	for(i=0;i<lenght;i++)ret[i]=str[start+i];	//Copio ogni carattere a partire da start per lenght
	ret[lenght]='\0';	//Imposto il fine stringa come ultimo elemento
	return strdup(ret);	//Duplico ret poichè è una variabile locale
}

char* stringConcat(char* str1, char* str2){
	char ret[strlen(str1)+strlen(str2)];	//La stringa deve essere la somme delle precedenti
	int i,j;
	for (i = 0; i < strlen(str1); ++i) ret[i]=str1[i];	//Copio la prima stringa
	for (j = 0; j < strlen(str2); ++j) ret[i+j]=str2[j];	//Seguita dalla successiva
	ret[strlen(str1)+strlen(str2)]='\0';	//Imposto il carattere di fine stringa
	return strdup(ret);	//Duplico la variabile locale
}
#endif 