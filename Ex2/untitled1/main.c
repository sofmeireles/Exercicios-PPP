#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#define MAX_TEXTO 3000
#define TAM_LINHA 80


int main() {
    char string[MAX_TEXTO + 1];
    const char chars[30] = "1235467890.,:;-_!?/'() ''\n\r\"";

    inicializa();


    if(ler_texto(string)==true) {
        strtobase_u8(string, string);

        char *token = strtok(string, chars);
        while (token != NULL) {
            colocar_ordenado(token);
            token = strtok(NULL, chars);
        }
        print_lista();
        libertaLista();

    }
    else{
        printf("Erro a ler o ficheiro\n");
    }
    return 0;
}
