#include <stdio.h>
#include <stdlib.h>
#include "WebPage.h"

int main(int argc,char** argv){
	char* word;
	char* sup="";

	if(argc!=2){ printf("USAGE: %s WORD\n",argv[0]); return -1; }
	word=argv[1];

	sup = CheckHttpRequest(word);
	if(sup) printf("\n\n\n%s\n", sup);
	else printf("RICHIESTA NON CORRETTA\n");

	return 0;
}