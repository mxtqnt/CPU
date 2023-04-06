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
    }
}

void decodifica(){

    if(lr=1){
        ir = (ibr & 0x0000F800) >> 11;
        /*  1001 1000 0000 1100 1010 0000 0000 1110
            0000 0000 0000 0000 1111 1000 0000 0000
            0000 0000 0000 0000 0000 0000 0001 1111 */

        if(ir >= hlt && ir <= stb){
            mar = mbr & 0x7FF00000 >> 11;
        /*  1001 1000 0000 1100 1010 0000 0000 1110
            0000 0000 0000 0000 1111 1000 0000 0000
            0000 0000 0000 0000 0000 0000 0001 1111 */
            
        }else if(ir>=je && ir<= stb){
            mar = mbr & 0x000007FF;
        /*  1001 1000 0000 1100 1010 0000 0000 1110
            0000 0000 0000 0000 0000 0111 1111 1111 */

        }else if(ir >= movial && ir <= rsh){
            imm= mbr & 0x000007FF;
        /*  1001 1000 0000 1100 1010 0000 0000 1110
            0000 0000 0000 0000 0000 0111 1111 1111 */
        }
    }else{
        ir = mbr >> 27;
        /*  1001 1000 0000 1100 1010 0000 0000 1110
            0000 0000 0000 0000 0000 0000 0001 0011*/

        ibr = mbr & 0x0000FFFF;
        /*  0000 0000 0000 0000 0000 0000 0001 0011
            0000 0000 0000 0000 1111 1111 1111 1111*/
    
        if(ir >= hlt && ir <= ldrb){
            mar = mbr & 0x7FF >> 16;
        /*  1001 1000 0000 1100 1010 0000 0000 1110
            0000 0000 0000 0000 1111 1000 0000 0000*/
            
        }else if(ir>=je && ir<= stb){
            mar = mbr & 0x07ff0000 >> 16;
        /*  1001 1000 0000 1100 1010 0000 0000 1110
            0000 0111 1111 1111 0000 0000 0000 0000
            0000 0000 0000 0000 0000 0111 1111 1111*/
        }
        else if(ir >= movial && ir <= rsh){
            imm = mbr & 0x07ff0000 >> 16;
        /*  1001 1000 0000 1100 1010 0000 0000 1110
            0000 0111 1111 1111 0000 0000 0000 0000
            0000 0000 0000 0000 0000 0111 1111 1111*/            
        }
    }
}

void executa(){

    switch(ir){

        case hlt:

        case nop:
            pc++;

        case add:
            if(lr==1){
                a=a+b;
                pc++;
            }else{
                a=a+b;
            }            

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
                pc++;
            }else{
                mbr=memoria[mar];
                mbr=((mbr<<16)|memoria[mar++]);
                mar=mbr&0x7ff;
                a=memoria[mar];
            }
        
        case ldb:
            mar=pc;
            if(lr=1){
                mbr=memoria[mar];
                mar=ibr&0x7ff;
                b=memoria[mar];
                pc++;
            }else{
                mbr=memoria[mar];
                mbr=((mbr<<16)|memoria[mar++]);
                mar=mbr&0x7ff;
                b=memoria[mar];
            }
        
        case sta:
            mar=pc;
            if(lr=1){
                mbr=memoria[mar];
                mar=ibr&0x7ff;
                a=memoria[mar];
                pc++;
            }else{
                mbr=memoria[mar];
                mbr=((mbr<<16)|memoria[mar++]);
                mar=mbr&0x7ff;
                a=memoria[mar];
            }
        
        case stb:
            mar=pc;
            if(lr=1){
                mbr=memoria[mar];
                mar=ibr&0x7ff;
                b=memoria[mar];
                pc++;
            }else{
                mbr=memoria[mar];
                mbr=((mbr<<16)|memoria[mar++]);
                mar=mbr&0x7ff;
                b=memoria[mar];
            }
        
        case ldrb:
            mar=pc;
            if(lr=1){
                mbr=memoria[mar];
                mar=ibr&0x7ff;
                a=b;
                pc++;
            }else{
                mbr=memoria[mar];
                mbr=((mbr<<16)|memoria[mar++]);
                mar=mbr&0x7ff;
                a=b;
            }break;

        lr!=lr;
        
        
        case movial:
            a = 0;
            a = imm & 0x00FF;
        /*  1010 0000 0000 1110
            0000 0000 1111 1111*/  
        
        case moviah:
            a = imm & 0x00FF << 8;
        /*  1010 0000 0000 1110
            0000 0000 1111 1111
            1111 1111 0000 0000*/  
        
        case addia:
            a = a + imm; /*???????????????*/
        
        case subia:
            a = a - imm; /*???????????????*/

        case mulia:
            a = a * imm; /*???????????????*/

        case divia:
            a = a / imm; /*???????????????*/

        case lsh:
            a = a << imm;

        case rsh:
            a = a >> imm;

        
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
    
    if(lr==1){
        decodifica();
        executa();
    }else{
        busca();
        decodifica();
        executa();
    }
    
    printf("%08x", mbr);
    
    getchar();
    return 0;
}