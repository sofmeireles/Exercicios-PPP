/*
 Sofia Meireles Fonseca Costa 2018296218


 Escolhas feitas:

 Quando o utilizador insere valores pares, é impossível que o quadrado fique no centro, uma vez que não existem "meios espaços".
 Deste modo, a opção tomada foi que o programa não pedisse novos valores, mas sim imprimisse algo semelhante ao enunciado, com um aviso antes.
 Assim:
  - Relativamente ao M, o centro do quadro fica "meio espaço" acima do que deveria ficar;
  - Relativamente ao N, o centro do quadrado fica "meio espaço" à direita do que deveria ficar;
 */


#include <stdio.h>
#include "header.h"


int main() {
    int m=0, n=0;
    int first=1;
    bool correct=false;
    while(!correct){
        if(first!=1){
            printf("Valor errado. Os valores tem de estar entre 13 e 30.\n");
        }
        printf("Insira o tamanho da tela\nM: ");
        scanf("%d",&m);
        printf("N: ");
        scanf("%d",&n);
        first=0;
        correct=verify_input(m,n);
    }
    int matrix[m][n];
    draw(m,n,matrix);
    print(m,n,matrix);
    return 0;
}
