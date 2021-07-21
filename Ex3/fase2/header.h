#ifndef PPP3_HEADER_H
#define PPP3_HEADER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXPALAVRA 25
#define MAXFILENAME 30

struct lista{
    int pos;
    struct lista* next;
};


struct arvore{
    char palavra[MAXPALAVRA];
    struct lista* ocorrencias;
    struct arvore* direita;
    struct arvore* esquerda;
};

void strtobase_u8(char *dest, const char *orig);

void print_no(struct arvore* aux);

void print_arvore(struct arvore* no);

bool verificaIguais(char* str1, char* str2);

void le_palavras(char* file, char* tab);

struct lista* cria_lista(int ocorrencia);

struct arvore* cria_no_arvore(char* palavra, int ocorrencia);

void adiciona_ocorrencia(struct arvore* aux, int ocorrencia);

void adiciona_palavra(char * palavra, int ocorrencia);

void adiciona_palavras(char* filename);

void print_contexto(struct arvore* no, char* filename);

void print_palavra(struct arvore* no,char letra);

void print_palavras(struct arvore* no,char letra);

void pedir_letras();

void limpa_lista(struct lista* no);

void limpa_arvore(struct arvore* no);

void pede_contexto(char* filename);

void menu(char* filename);

struct arvore* encontra_no(char* palavra);



#endif //PPP3_HEADER_H
