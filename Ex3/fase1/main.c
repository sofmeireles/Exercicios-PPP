/***
 * Sofia Meireles F. Costa 2018296218
 * 
 **/

#include <stdio.h>
#include <string.h>
#include "header.h"
#define MAXPALAVRA 25
#define MAXLINHA 255
#define MAXFILENAME 30

int main(int argc, char *argv[ ]) {
    if(argc!=2){
        printf("Indique um nome de ficheiro.\n");
        return -1;
    }
    char tab[MAXFILENAME+5] = "tab_";
    strcat(tab,argv[1]);

    le_palavras(argv[1],tab);

    return 0;
}