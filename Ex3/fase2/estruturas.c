#include "header.h"

struct arvore* raiz_arvore;

//imprime no com a posicao
void print_no(struct arvore* aux){
    printf("\npalavra: %s\n",aux->palavra);
    struct lista* aux_lista = aux->ocorrencias;
    while(aux_lista!=NULL){
        printf("%d ",aux_lista->pos);
        aux_lista=aux_lista->next;
    }
    printf("\n");
}

//imprime a arvore
void print_arvore(struct arvore* no){
    struct arvore* aux = no;
    if(no==NULL){
        printf("acabou\n");
        return;
    }

    print_no(aux);

    if(aux->esquerda!=NULL){
        print_arvore(aux->esquerda);
    }
    if(aux->direita!=NULL){
        print_arvore(aux->direita);
    }
}

//cria o primeiro no da lista de ocorrencias
struct lista* cria_lista(int ocorrencia){
    struct lista* head = (struct lista*)malloc(sizeof(struct lista));
    head->next=NULL;
    head->pos=ocorrencia;
    return head;
}

//cria um no de uma arvora
struct arvore* cria_no_arvore(char* palavra, int ocorrencia){
    struct arvore* no = (struct arvore*)malloc(sizeof(struct arvore));
    //criar a lista de ocorrencias
    no->ocorrencias=cria_lista(ocorrencia);
    strcpy(no->palavra,palavra);
    return no;
}

//adiciona ocorrencia no inicio da lista
void adiciona_ocorrencia(struct arvore* aux, int ocorrencia) {
    struct lista *aux_lista =  (struct lista *) malloc(sizeof(struct lista));
    aux_lista->pos = ocorrencia;
    aux_lista->next = aux->ocorrencias;
    aux->ocorrencias=aux_lista;
}

//adiciona uma palavra, verificando se ja existe
void adiciona_palavra(char * palavra, int ocorrencia){
    struct arvore* aux;

    //se nao existe raiz criar
    if(raiz_arvore==NULL){
        raiz_arvore=cria_no_arvore(palavra,ocorrencia);
        raiz_arvore->esquerda=NULL;
        raiz_arvore->direita=NULL;
        return;
    }

    aux = raiz_arvore;


    while(aux!=NULL){
        //se a palavra for igual
        if(verificaIguais(aux->palavra,palavra)==true){
            adiciona_ocorrencia(aux,ocorrencia);
            return;
        }

        //percorrer para a direita
        if(strcmp(aux->palavra,palavra)<0){
            //se nao houver mais nos a direita, criar um novo
            if(aux->direita==NULL){
                aux->direita=cria_no_arvore(palavra,ocorrencia);
                aux->direita->direita=NULL;
                aux->direita->esquerda=NULL;
                return;
            }
            else{
                aux=aux->direita;
            }

        }

        //percorrer para a esquerda
        else if(strcmp(aux->palavra,palavra)>0){
            //se nao houver mais nos a esquerda, criar um novo
            if(aux->esquerda==NULL){
                aux->esquerda=cria_no_arvore(palavra,ocorrencia);
                aux->esquerda->direita=NULL;
                aux->esquerda->esquerda=NULL;
                return;
            }
            else{
                aux=aux->esquerda;
            }
        }
    }

}

//adiciona palavras
void adiciona_palavras(char* filename){
    //vai buscar o ficheiro da pasta ficheiros
    char path[17+MAXFILENAME] = "../../ficheiros/";
    strcat(path,filename);
    FILE* f = fopen(path,"r");
    if(f==NULL){
        printf("Erro a abrir o ficheiro2\n");
        return;
    }

    char linha[30];
    char* token;
    char palavra[MAXPALAVRA];
    int ocorrencia;

    //le o ficheiro, separa por ; e insere a palavra na arvore
    while(fgets(linha,200,f)){
        token=strtok(linha,";");
        strcpy(palavra,token);
        token=strtok(NULL,";");
        ocorrencia=atoi(token);
        adiciona_palavra(palavra,ocorrencia);
    }

    fclose(f);

}

//procura o no que contem a palavra indicada
struct arvore* encontra_no(char* palavra){
    struct arvore* aux = raiz_arvore;

    while(aux!=NULL){
        //se forem iguais da return do no
        if(verificaIguais(palavra,aux->palavra)==true){
            return aux;
        }

        //pesquisar na direita
        if(strcmp(aux->palavra,palavra)<0){
            aux=aux->direita;
        }

        //pesquisar na esquerda
        else if(strcmp(aux->palavra,palavra)>0){
            aux=aux->esquerda;
        }

    }
    printf("Palavra nao encontrada\n");
    return NULL;
}

//limpa lista de ocorrencias
void limpa_lista(struct lista* no){
    struct lista* aux;
    while(no!=NULL){
        aux=no;
        no=no->next;
        free(aux);
    }
}

//limpa arvore
void limpa_arvore(struct arvore* no){
    struct arvore* aux;
    if(no==NULL){
        return;
    }

    aux=no;
    limpa_arvore(aux->direita);
    limpa_arvore(aux->esquerda);

    limpa_lista(aux->ocorrencias);
    free(aux);
}