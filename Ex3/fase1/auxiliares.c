#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXPALAVRA 25
#define MAXLINHA 255
#define MAXFILENAME 30


//remove a pontuacao das palavras
void remove_pontuacao(char* str){
    const char* dem  = ".,:;_!?/'()<> ''+=»«\"\n\r";

    int i, j;
    for(i=0;i<(int)strlen(dem);i++){
        for(j=0;j<(int)strlen(str);j++){
            if(str[j]==dem[i]){
                str[j]='\0';
            }
        }
    }
}

void le_palavras(char* file, char* tab){
    //vai buscar o ficheiro da pasta ficheiros
    char path[17+MAXFILENAME] = "../../ficheiros/";
    strcat(path,file);

    FILE* f = fopen(path, "r" );
    if(f==NULL){
        printf("Ficheiro nao encontrado\n");
        return;
    }

    //ficheiro tab_
    strcpy(path,"../../ficheiros/");
    strcat(path,tab);
    FILE* w = fopen(path, "w" );
    if(w==NULL){
        printf("Erro a criar o ficheiro\n");
        return;
    }

    char *palavra = (char * )malloc(MAXPALAVRA);
    char str[MAXLINHA] = "";
    int pos=0;

    //percorre o ficheiro e tira as palavras e a posicao
    while(fscanf(f," %25s",palavra) == 1){
        remove_pontuacao(palavra);
        if(strlen(palavra)!=0){
            sprintf(str,"%s;%d\n",palavra,pos);
            fputs(str,w);
            pos = (int)ftell(f);
        }

    }

    fclose(f);
    fclose(w);
    printf("Palavras inseridas no ficheiro com sucesso\n");
}