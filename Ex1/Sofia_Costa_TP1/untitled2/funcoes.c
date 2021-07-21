#include <stdio.h>
#include <stdbool.h>
#include "header.h"
#define SPACE 2

bool verify_input(int n1, int n2){
    if(13 <= n1 && n1 <= 30 && 13 <= n2 && n2 <= 30){
        if(n1%2==0 || n2%2==0){
            printf("Atenção! O(s) valor(es) inserido(s) é/são par(es) pelo que o quadrado vai ficar deslocado.\n");
        }
        return true;
    }
    else
        return false;
}

void print(int m, int n, int matrix[m][n]){
    int i,j;
    int flag=0;

    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(matrix[i][j]==0){
                if(flag==0 && matrix[i][j+1]==1 && i!=m-1){
                    printf("I");
                    flag=1;
                }
                else if(flag==1 && matrix[i][j-1]==1){
                    printf("I");

                }
                else{
                    printf("~");
                }
            }
            else{
                printf("H");
            }
        }
        flag=0;
        printf("\n");
    }

}

void draw(int m, int n, int matrix[m][n]){
    int x,y;
    double size;

    int center_y=(m/2)-SPACE;
    int center_x=(n/2);

    if(m-n>4 && n%2==0){
        size=center_x-1;
    }
    else if(m-n>4 && n%2!=0){
        size=center_y-1;
    }
    else if(m-n==4 && m%2==0 && n%2==0){
        size=center_x-1;
    }
    else{
        size=center_y;
    }

    //borda mais proxima é a do lado
    if(center_x < center_y){
        //printf("size: %fl\n",size);

        for(y=0;y<m;y++){
            for(x=0;x<n;x++){
                if(x<SPACE || x >=SPACE+size || y<(m/2.0-2-size/2)-1 || y>=(m/2.0+size-size/2-2)-1 ){
                    matrix[y][x]=0;
                }
                else{
                    matrix[y][x]=1;
                }
            }
        }
    }

    //borda mais proxima é a de cima
    else{
        //printf("size: %fl\n",size);

        for(y=0;y<m;y++){
            for(x=0;x<n;x++){
                if(y<SPACE || y >(SPACE+size-1) || x<(center_x-size/2.0) || x>=(center_x+size/2.0)){
                    matrix[y][x]=0;
                }
                else{
                    matrix[y][x]=1;
                }
            }
        }
    }
}