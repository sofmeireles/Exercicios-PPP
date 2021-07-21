#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

extern struct Dados * lista;
extern struct Palavra * palavra_mais;
extern int menor;

static char acentuadas_minusculas[][8] =
        {"á", "à", "ã", "â", "ä", "ç", "é", "è", "ê", "í", "ì", "î",
         "ó", "ò", "õ", "ô", "ö", "ú", "ù", "û", "\0"};
static char acentuadas_maiusculas[][8] =
        {"Á", "À", "Ã", "Â", "Ä", "Ç", "É", "È", "Ê", "Í", "Ì", "Î",
         "Ó", "Ò", "Õ", "Ô", "Ö", "Ú", "Ù", "Û", "\0"};

static char base_minusculas[] =
        {'a', 'a', 'a', 'a', 'a', 'c',
         'a', 'a', 'a', 'a', 'a', 'c',
         'e', 'e', 'e', 'i', 'i', 'i',
         'o', 'o', 'o', 'o', 'o', 'u',
         'u', 'u', '\0'};

static char base_maiusculas[] =
        {'A', 'A', 'A', 'A', 'A', 'C',
         'E', 'E', 'E', 'I', 'I', 'I',
         'O', 'O', 'O', 'O', 'O', 'U',
         'U', 'U', '\0'};

// comparar dois carateres multibyte, sob a forma de string, tendo o primeiro de ser terminado por zero
// devolve zero se são diferentes; devolve o número de bytes do carater se são iguais
static int comp_mchar(const char *um, const char *outro) {
    int i = 0;
    while (um[i] != 0) {
        if (um[i] != outro[i])
            return 0;
        i++;
    }
    return i;
}

void strtobase_u8(char *dest, const char *orig) {
    int i = 0, j = 0, c;
    // percorrer a string origem
    c = (unsigned char) orig[0];
    while (c != 0) {
        if ((c & 0x80) == 0) {
            // é um carater ASCII, basta converter as letras para minusculas
            /*if (c <= 'Z' && c >= 'A')
                c = c + 'a' - 'A';*/
            i++;
            dest[j] = (char) c;
            j++;
        } else {
            // é um carater UTF-8 com mais de um byte
            int k = 0, tc = 0;
            while (acentuadas_minusculas[k][0] != 0) {
                // se for uma das letras acentuadas, retira-se o acento
                if ((tc = comp_mchar(&acentuadas_minusculas[k][0], &orig[i])) != 0) {
                    // encontramos uma minúscula acentuada
                    dest[j] = base_minusculas[k];
                    j++;
                    i = i + tc;
                    break;
                }
                else if((tc = comp_mchar(&acentuadas_maiusculas[k][0], &orig[i])) != 0){
                    // encontramos uma maiuscula acentuada
                    dest[j] = base_maiusculas[k];
                    j++;
                    i = i + tc;
                    break;
                }
                k++;
            }
            if (tc == 0) {
                // não é uma letra acentuada, logo é de copiar para
                //   o destino, sem alterações, todos os carateres UTF-8
                do {
                    dest[j] = orig[i];
                    i++;
                    j++;
                } while ((orig[i] & 0xC0) == 0x80);
            }
        }
        c = (unsigned char) orig[i];
    }
    dest[j] = 0;
}

bool ler_texto(char *ptexto) {
    FILE *fich1;
    int i, c;
    fich1 = fopen("texto.txt", "r");
    if (fich1 == NULL) {
        // Ficheiro texto.txt não existe
        //printf("file does not exist\n");
        return false;
    }
    i = 0;
    while (i < (MAX_TEXTO) && (c = fgetc(fich1)) != EOF) {
        ptexto[i] = (char) c;
        // detetar e eliminar o UTF BOM
        if (i == 2 && ptexto[0] == (char)0xEF && ptexto[1] == (char) 0xBB && ptexto[2] == (char) 0xBF)
            i = 0;
        else
            i++;
    }
    ptexto[i] = 0;
    i++;
    fclose(fich1);
    if (i <= MAX_TEXTO)
        return true;
    else
        // limite de bytes ultrapassado
        //printf("limite ultrapassado\n");
        return false;
}


void encontra_menor(){
    //encontra o menor numero de ocorrencias
    struct Dados* atual = lista;
    while (atual!=NULL){
        if(atual->palavra->ocorrencias<menor){
            menor=atual->palavra->ocorrencias;
        }
        atual=atual->next;
    }
}

int calcula_espacos(struct Palavra * palavra){
    if(palavra->ocorrencias == palavra_mais->ocorrencias){
        return 0;
    }
    //espaços necessarios para ficar encostada
    int necessario = TAM_LINHA-strlen(palavra_mais->palavra);

    return(TAM_LINHA - palavra->ocorrencias*necessario/palavra_mais->ocorrencias);


}

void print_lista(){
    struct Dados* atual = lista;
    int contaTotal=0;
    encontra_menor();
    while(atual!=NULL){
        int i;
        for(i=0; i<calcula_espacos(atual->palavra);i++){
            printf(" ");
            contaTotal++;
        }
        //printf("%s - ocorrencias: %d\n",atual->palavra->palavra,atual->palavra->ocorrencias);
        printf("%s \n",atual->palavra->palavra);

        atual=atual->next;
    }

}
