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
    ir = mbr >> 24;

    if(ir >= hlt && ir <= nop){
        
    }else if(ir >= add && ir <= cmp){
        a = (mbr & 0x00e00000) >> 21;
        b = (mbr & 0x001c0000) >> 18;

    }else if(ir == xchg){
        a = (mbr & 0x00e00000) >> 21;
        b = (mbr & 0x001c0000) >> 18;
        t = (mbr & 0x0003e000) >> 13;
    
    }else if(ir == ldrb){
        a = (mbr & 0x00e00000) >> 21;
        b = (mbr & 0x001c0000) >> 18;
    }    
    else if(ir >= and && ir <= xor){
        a = (mbr & 0x00e00000) >> 21;
        b = (mbr & 0x001c0000) >> 18;
    }
    else if(ir == not){
        a = (mbr & 0x00e00000) >> 21;
    
    }else if(ir >= je && ir <= jmp){
        mar = mbr & 0x001fffff;
    
    }else if(ir >= lda && ir<=stb){
        a = (mbr & 0x00e00000) >> 21;
        mar = mbr & 0x001fffff;
    
    }else if(ir >= movial && ir <= divia){
        a = (mbr & 0x00e00000) >> 21;
        imm = (mbr & 0x0000ffff);
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