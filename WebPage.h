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

char* CheckPageExistence(char* path){
	FILE* fp;
	char* text;
	int size;
	int ret;
	
	fp = fopen(path, "rb+");
	if(fp) {
		fseek(fp, 0, SEEK_END); 
		size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		
		text = (char*)calloc(sizeof(char),(size+1)*sizeof(char));

		fread(text,sizeof(char),size,fp);

		fclose(fp);
		return text;
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

#endif 