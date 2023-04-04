#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruct.h"

unsigned char memoria[154],
              ir,
              e,l,g,
              lr=0;


unsigned int mbr;

unsigned short int mar,
                   ibr,
                   pc=0,
                   imm,
                   a,b,t;

char count;


void preencher_memoria(unsigned int memo , unsigned int aux){
    memoria[memo++] = (aux & masc1) >> 24;
    memoria[memo++] = (aux & masc2) >> 16;
    memoria[memo++] = (aux & masc3) >> 8;
    memoria[memo] = (aux & masc4);
}

void busca(){
    mar=pc;
    mbr=memoria[mar++];

    for(int i=1;i<4;i++){
        mbr = mbr<<8;
        mbr = (mbr | memoria[mar++]);
        pc++;
    }
}

void decodifica(){
    if(lr=0){
        mbr = (mbr & 0xffff0000) >> 16;
        /*  1001 1000 0000 1100 | 1010 0000 0000 1110 (Na memória)
            1001 1000 0000 1100 | 0000 0000 0000 0000 (Máscara)
            0000 0000 0000 0000 | 1001 1000 0000 1100 (Delocado)
        */
    }
    else{
        mbr = mbr & 0x0000ffff;
        /*  1001 1000 0000 1100 | 1010 0000 0000 1110 (Na memória)
            0000 0000 0000 0000 | 1010 0000 0000 1110 (Deslocado)
        */
    }
    
    ir = mbr >> 11;
        /*  1001 1000 0000 1100 (No mbr)
            0000 0000 0001 0011 (Desclocado)
        */

    if(ir >= hlt && ir <= stb){
            mar = mbr & 0x07ff;
        /*  1010 0000 0000 1110 (No mbr)
            0000 0111 1111 1111 (Máscara)
            0    7    f    f
        */            
        }
        
        else if(ir >= movial && ir <= rsh){
            imm = mbr & 0x07ff;
        /*  1010 0000 0000 1110 (No mbr)
            0000 0111 1111 1111 (Máscara)
            0    7    f    f
        */
        }

    }

void executa(){

}

void texto(){
    FILE *arquivo;
    char caracter;

    arquivo = fopen("programa.txt", "r");

    if (arquivo == NULL){
        printf("Arquivo não encontrado \n");
    }else{
        while ((caracter = getc(arquivo)) != EOF) {
            printf("%c", caracter);
        }

    }
    fclose(arquivo); 
}

int main(void){
    //teste do busca
    // memoria[0] = 0x12;
    // memoria[1] = 0x34;
    // memoria[2] = 0x56;
    // memoria[3] = 0x78;

    //teste do preencher_memoria
    unsigned int valor = 0x12345678;
    preencher_memoria(0, valor);

    for (int i = 0; i < 154; i++){
        printf("%x ", memoria[i]);
    }

    busca();
    printf("%08x", mbr);
    
    getchar();
    return 0;
}