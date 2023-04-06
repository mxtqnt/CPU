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
    

    if(lr=1){
        ir= (ibr & 0x07FF)>>11;

        if(ir >= hlt && ir <= stb){
            mar= mbr & 0x7FF00000;
            
        }else if(ir >= movial && ir <= rsh){
            imm= mbr & 0x7FF00000;
            
        }
    }else{
        ir = mbr >> 27;
        ibr = mbr & 0xF8000000;
    
        if(ir >= hlt && ir <= stb){
            mar= mbr & 0x7FF >> 16;
            
        }else if(ir >= movial && ir <= rsh){
            imm= mbr & 0x7FF >> 16;
            
        }
    }
}

void executa(){

    switch(ir){

        case hlt:

        case nop:
            pc++;

        case add:
            a=a+b;

        case sub:
            a=a-b;

        case mul:
            a=a*b;

        case div:
            a=a/b;

        case cmp:
            if (a==b){
                e=1;
            }else{
                e=0;
            }if(a<b){
                l=1;
            }else{
                l=0;
            }if(a>b){
                g=1;
            }else{
                g=0;
            }

        case xchg:
            t=a;
            a=b;
            b=t;
        
        case and:
            a=a&b;
        
        case or:
            a=a|b;
        
        case xor:
            a=a^b;
        
        case not:
            a=!a;
        
        case je:
            if(e=1){
                pc=mar;
            }
        
        case jne:
            if(e=0){
                pc=mar;
            }
        
        case jl:
            if(l=1){
                pc=mar;
            }
        
        case jle:
            if(l==1 || e==1){
                pc=mar;
            }
        
        case jg:
            if(g==1){
                pc=mar;
            }
        
        case jge:
            if(g==1 || e==1){
                pc=mar;
            }
        
        case jmp:
            pc=mar;
        
        case lda:
            mar=pc;
            if(lr=1){
                mbr=memoria[mar];
                mar=ibr&0x7ff;
                a=memoria[mar];
                pc+=1;
            }else{
                mbr=memoria[mar];
                mbr=((mbr<<16)|memoria[mar++]);
                mar=mbr&0x7ff;
                a=memoria[mar];
                pc+=1;
            }
    }

    

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