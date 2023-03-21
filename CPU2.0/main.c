#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void busca(){

}

void decodifica(){

}

void executa(){

}

void texto(){
    FILE *arq;
    char caracter;

    arq = fopen("programa.txt", "r");

    if (arq == NULL){
        printf("Arquivo não encontrado \n");
    }else{
        while ((caracter = getc(arq)) != EOF) {
            printf("%c", caracter);
        }

    }
    fclose(arq); 
}

int main(void){
   
    texto();


    return 0;
}