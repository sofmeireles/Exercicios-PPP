#include "header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAXPALAVRA 25
#define MAXFILENAME 30

extern struct arvore* raiz_arvore;

static char acentuadas[][8] =
        {"á", "Á", "à", "À", "ã", "Ã", "â", "Â", "ä", "Ä", "ç", "Ç",
         "é", "É", "è", "È", "ê", "Ê", "í", "Í", "ì", "Ì", "î", "Î",
         "ó", "Ó", "ò", "Ò", "õ", "Õ", "ô", "Ô", "ö", "Ö", "ú", "Ú",
         "ù", "Ù", "û", "Û", "\0"};
static char base[] =
        {'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'c', 'c',
         'e', 'e', 'e', 'e', 'e', 'e', 'i', 'i', 'i', 'i', 'i', 'i',
         'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'o', 'u', 'u',
         'u', 'u', 'u', 'u', '\0'};


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
            if (c <= 'Z' && c >= 'A')
                c = c + 'a' - 'A';
            i++;
            dest[j] = (char) c;
            j++;
        } else {
            // é um carater UTF-8 com mais de um byte
            int k = 0, tc = 0;
            while (acentuadas[k][0] != 0) {
                // se for uma das letras acentuadas, retira-se o acento
                if ((tc = comp_mchar(&acentuadas[k][0], &orig[i])) != 0) {
                    // encontramos uma minúscula acentuada
                    dest[j] = base[k];
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

//verifica se as palavras sao iguais apesar de acentos
bool verificaIguais(char* str1, char* str2){
    char aux[22], aux2[22];
    strtobase_u8(aux,str1);
    strtobase_u8(aux2,str2);

    if(comp_mchar(aux,aux2)==0){
        return false;
    } else{
        return true;
    }
}

//imprime com o contexto
void print_contexto(struct arvore* no, char* filename){
    struct lista* aux_lista = no->ocorrencias;
    //vai buscar o ficheiro da pasta ficheiros
    char path[17+MAXFILENAME] = "../../ficheiros/";
    strcat(path,filename);

    FILE * f = fopen(path,"r");
    if(f==NULL){
        printf("Erro a abrir o ficheiro1\n");
        return;
    }
    int conta_espacos;
    long pos_atual;
    int c;
    //colocar o ponteiro no fim
    fseek(f,0,SEEK_END);
    //retirar o ultimo valor
    long eof = ftell(f);

    printf("\nPalavra: %s\n",no->palavra);

    //percorrer a lista
    while(aux_lista!=NULL){
        printf("\n\n");
        conta_espacos=0;
        pos_atual=(long)aux_lista->pos;

        while(conta_espacos!=9){
            //colocar o ponteiro do file na ocorrencia ate onde der
            if(fseek(f,pos_atual-1,SEEK_SET)!=0){
                break;
            }
            c=fgetc(f);
            if(c==' '|| c=='\n'){
                conta_espacos++;
            }
            pos_atual=pos_atual-1;
        }


        //imprimir ate a palavra
        if(pos_atual!=0){
            pos_atual=pos_atual-1;
        }
        //colocar o ponteiro na posicao certa
        fseek(f,pos_atual,SEEK_SET);
        while(pos_atual < aux_lista->pos){
            c=fgetc(f);
            printf("%c",c);
            pos_atual=ftell(f);
        }
        conta_espacos=0;

        //imprimir depois da palavra
        while(conta_espacos!=7){
            c=fgetc(f);
            printf("%c",c);

            if(ftell(f)==eof){
                break;
            }

            if(c==' ' || c=='\n'){
                conta_espacos++;
            }
        }
        aux_lista=aux_lista->next;
        printf("\n");
    }
    fclose(f);
}

//imprime palavra
void print_palavra(struct arvore* no,char letra){
    if(no->palavra[0]==tolower(letra) || no->palavra[0]==toupper(letra)){
        printf("%s ",no->palavra);
    }
}

//imprime palavras comecadas por uma letra
void print_palavras(struct arvore* no,char letra){
    struct arvore* aux = no;
    if(raiz_arvore==NULL){
        return;
    }

    print_palavra(aux,letra);

    if(aux->esquerda!=NULL){
        print_palavras(aux->esquerda,letra);
    }
    if(aux->direita!=NULL){
        print_palavras(aux->direita,letra);
    }
}

//pede um inteiro e verifica se e inteiro
int pedir_int(char * msg){
    char input[4] = "a";
    
    while(!isdigit(input[0])){
        printf("%s",msg);
        scanf("%s",input);
        if(strlen(input)>2){
            printf("numero demasiado grande\n");
            strcpy(input,"");
        }
    }
    return atoi(input);
}

//pede as letras para a pesquisa de palavras
void pedir_letras(){
    int i, j;
    int n;
    char letra[1];
    char *letras;
  
    n=pedir_int("Quantas letras deseja procurar?\n");

    letras = (char*)malloc(n);
    for(i = 0; i<n; i++){
        printf("\nletra: ");
        scanf(" %c",letra);
        letras[i]= letra[0];
    }

    //imprime as palvras comecadas pela letra
    for(j = 0; j<n; j++){
        printf("\nletra %c:\n",letras[j]);
        print_palavras(raiz_arvore, letras[j]);
        printf("\n");
    }
}


//pede a palavra para se imprimir o contexto
void pede_contexto(char* filename){
    char palavra[MAXPALAVRA];

    printf("Insira a palavra que pretende procurar:\n");
    scanf("%s",palavra);

    struct arvore* no = encontra_no(palavra);
    if(no==NULL){
        return;
    }

    print_contexto(no,filename);
}

void menu(char* filename){
    int op=-1;

    while(op!=0){
        printf("\nMenu\n");
        printf("1-Contexto\n");
        printf("2-Pesquisar palavras por letra\n");
        printf("0-Sair\n");

        while(op<0 || op>2){
            op=pedir_int("");
        }

        if(op==1){
            pede_contexto(filename);
        }
        else if(op==2){
            pedir_letras();
        }
        else{
            limpa_arvore(raiz_arvore);
            return;
        }
        op=-1;
    }
}
