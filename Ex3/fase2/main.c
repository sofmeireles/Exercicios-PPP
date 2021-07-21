/***
 * Sofia Meireles F. Costa 2018296218
 * 
 * Nota: Relativamente ao path dos ficheiros, é possível que esteja errado consoante o  IDE que se
 * estiver a usar. No caso do Clion, é necessário que este seja "../../ficheiros/". Isto deve ser
 * alterado no ficheiro estruturas.c linha 116 e no ficheiro auxiliares.c linha 94
 * Caso se esteja a correr no terminal o path deve ser "../ficheiros/" apenas
 * 
 **/


#include "header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXPALAVRA 25
#define MAXFILENAME 30


int main() {
    char filename[MAXFILENAME];
    printf("Insira o nome do ficheiro:\n");
    scanf("%s",filename);

    char tab[MAXFILENAME+5] = "tab_";
    strcat(tab,filename);

    adiciona_palavras(tab);
    menu(filename);

    return 0;
}
