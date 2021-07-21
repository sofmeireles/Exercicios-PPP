#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"

struct Dados * lista;
struct Palavra * palavra_mais;
int menor;

struct Dados * cria_no(char* palavra){
    struct Palavra * nova_palavra = (struct Palavra*) malloc(sizeof(struct Palavra));
    strcpy(nova_palavra->palavra,palavra);
    nova_palavra->ocorrencias=1;

    struct Dados * novo_no = (struct Dados*) malloc(sizeof(struct Dados));
    novo_no->palavra=nova_palavra;
    novo_no->back=NULL;
    novo_no->next=NULL;

    return novo_no;
}

void colocar_ordenado(char* palavra) {
    //se a lista estiver vazia
    if (lista == NULL) {
        lista = cria_no(palavra);
        return;
    }
    //percorrer a lista
    struct Dados *atual = lista;
    while (atual != NULL) {

        //se as palavras forem iguais
        if (strcmp(atual->palavra->palavra, palavra) == 0) {
            atual->palavra->ocorrencias++;
            if (atual->palavra->ocorrencias > palavra_mais->ocorrencias) {
                palavra_mais = atual->palavra;
            }
            return;
        } else if (strncmp(atual->palavra->palavra, palavra, 2) == 0) {

            //se o numero de letras for menor adicionar antes
            if (strlen(palavra) < strlen(atual->palavra->palavra)) {
                struct Dados *novo_No = cria_no(palavra);
                novo_No->next = atual;

                //se nao for o primeiro elemento da lista
                if (atual->back != NULL) {
                    novo_No->back = atual->back;
                    atual->back->next = novo_No;
                    atual->back = novo_No;
                    novo_No->next = atual;
                    return;
                }

                    //é o primeiro elemento da lista entao o inicio da lista passa a ser o novo no
                else {
                    novo_No->next = atual;
                    atual->back = novo_No;
                    lista = novo_No;
                    return;
                }

            }
        }
            //palavra diferente
        else {
            struct Dados *novo_No = cria_no(palavra);

            //se for menor adicionar antes
            if (strcmp(palavra, atual->palavra->palavra) < 0) {
                novo_No->next = atual;

                //se nao for o primeiro elemento da lista
                if (atual->back != NULL) {
                    novo_No->back = atual->back;
                    atual->back->next = novo_No;
                    atual->back = novo_No;
                    novo_No->next = atual;
                    return;
                }

                    //é o primeiro elemento da lista entao o inicio da lista passa a ser o novo no
                else {
                    novo_No->next = atual;
                    atual->back = novo_No;
                    lista = novo_No;
                    return;
                }
            } else {

                //se for o ultimo elemento
                if (atual->next == NULL) {
                    novo_No->back = atual;
                    atual->next = novo_No;
                    return;
                }
            }
        }
        atual = atual->next;

    }
}

void inicializa(){
    menor=1000000;

    palavra_mais = (struct Palavra*) malloc(sizeof(struct Palavra));
    strcpy(palavra_mais->palavra,"");
    palavra_mais->ocorrencias=0;
}

void libertaLista(){
    struct Dados* aux;

    while (lista != NULL)
    {
        aux = lista;
        lista = lista->next;
        free(aux->palavra);
        free(aux);
    }
}

