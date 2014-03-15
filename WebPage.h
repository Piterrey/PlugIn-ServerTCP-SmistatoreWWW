#ifndef WEBPAGE_H
#define WEBPAGE_H

#include "stringa.h"
#include <stdio.h>
#include <stdlib.h>

#define HTTP_GET_HEAD "GET "
#define HTTP_GET_FOOT " HTTP"
#define HTTP_HEADER_LEN 4

#define PAGE404 "./404.html"

/*############# Prototipi ###############*/
char* GetPathByRequest(char* HTTP_Request);
char* CheckPageExistence(char* path);
char* CheckHttpRequest(char* HTTP_Request);
MultiFile* ConcactMulti(char* str1, MultiFile* str2);

/*############# Struttura ###############*/

typedef struct 
{
	char* content;
	int lenght;	
} MultiFile;

/*########### Implementazione ##############*/
char* CheckHttpRequest(char* HTTP_Request){
	char* sup;

	sup = GetPathByRequest(HTTP_Request);
	if(!sup) return sup;

	sup = stringConcat("./www",GetPathByRequest(HTTP_Request));
	sup = CheckPageExistence(sup);

	if(sup) return sup;
	else return CheckPageExistence(PAGE404);
}

MultiFile* CheckPageExistence(char* path){
	MultiFile* ret;
	FILE* fp;
	char* text;
	int size;
	
	fp = fopen(path, "rb+");
	if(fp){
		ret = (MultiFile*)malloc(sizeof(MultiFile));

		fseek(fp, 0, SEEK_END); 
		ret->lenght = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		
		ret->content = (char*)calloc(sizeof(char),(ret->lenght+1)*sizeof(char));

		fread(ret->content,sizeof(char),ret->lenght,fp);

		fclose(fp);
		return ret;
	}
	else return NULL;
}

char* GetPathByRequest(char* HTTP_Request){
	int start,stop;

	start = getFistIndex(HTTP_Request,HTTP_GET_HEAD);
	stop = getFistIndex(HTTP_Request,HTTP_GET_FOOT);
	if(start>=0 && stop>=0) return getSubString(HTTP_Request, start+strlen(HTTP_GET_HEAD), stop-start-strlen(HTTP_GET_HEAD));
	return NULL;
}

MultiFile* ConcactMulti(char* str1, MultiFile* str2)
{
	MultiFile* ret;
	int i,j,lg;

	ret = (MultiFile*)malloc(sizeof(MultiFile));

	lg = strlen(str1);
	ret->lenght = lg+str2->lenght;
	ret->content = (char*)malloc((sizeof(char)*ret->lenght)+1);
	
	for (i = 0; i < lg; ++i) ret->content[i]=str1[i];	//Copio la prima stringa
	for (j = 0; j < str2->lenght; ++j) ret->content[i+j]=str2->content[j];	//Seguita dalla successiva

	ret->content[ret->lenght + 1]='\0';	//Imposto il carattere di fine stringa

	return ret;	//Duplico la variabile locale
}

#endif 