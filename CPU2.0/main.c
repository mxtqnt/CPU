#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruct.h"

unsigned char memoria[154],
              ir,
              e,l,g,
              lr=0;

unsigned char *ponteiro;

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
            break;

        case nop:
            if(lr=1){
                pc++;
                lr!=lr;
            }else{
                lr!=lr;
            }
            break;
            
        case add:
            if(lr==1){
                a=a+b;
                pc++;
            }else{
                a=a+b;
            }            
            break;

        case sub:
            if(lr==1){
                a=a-b;
                pc++;
            }else{
                a=a-b;
            } 
            break;

        case mul:
            if(lr==1){
                a=a*b;
                pc++;
            }else{
                a=a*b;
            } 
            break;

        case div:
            if(lr==1){
                a=a/b;
                pc++;
            }else{
                a=a/b;
            } 
            break;


        case cmp:
            if(lr==1){
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
                pc++;
            }else{
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
            } 
            break;

        case xchg:
            if(lr==1){
                t=a;
                a=b;
                b=t;
                pc++;
            }else{
                t=a;
                a=b;
                b=t;
            }
            break;
        
        case and:
            if(lr==1){
                a=a&b;
                pc++;
            }else{
                a=a&b;
            }
            break;
        
        case or:
            if(lr==1){
                a=a|b;
                pc++;
            }else{
                a=a|b;
            }
            break;
        
        case xor:
            if(lr==1){
                a=a^b;
                pc++;
            }else{
                a=a^b;
            }
            break;
        
        case not:
            if(lr==1){
                a=!a;
                pc++;
            }else{
                a=!a;
            }
            break;
        
        case je:
            if(lr==1){
                if(e=1){
                    pc=mar;
                }
                pc++;
            }else{
                if(e=1){
                    pc=mar;
                }
            }
            break;
        
        case jne:
            if(lr==1){
                if(e=0){
                    pc=mar;
                }
                pc++;
            }else{
                if(e=0){
                    pc=mar;
                }
            }
            break;

        case jl:
            if(lr==1){
                if(l=1){
                    pc=mar;
                }
                pc++;
            }else{
                if(l=1){
                    pc=mar;
                }
            }
            break;
        
        case jle:
            if(lr==1){
                if(l==1 || e==1){
                    pc=mar;
                }
                pc++;
            }else{
                if(l==1 || e==1){
                    pc=mar;
                }
            }
            break;
        
        case jg:
            if(lr==1){
                if(g==1){
                    pc=mar;
                }
                pc++;
            }else{
                if(g==1){
                    pc=mar;
                }
            }
            break;

        case jge:
            if(lr==1){
                if(g==1 || e==1){
                    pc=mar;
                }
                pc++;
            }else{
                if(g==1 || e==1){
                    pc=mar;
                }
            }
            break;
        
        case jmp:
            if(lr==1){
                pc=mar;
                pc++;
            }else{
                pc=mar;
            }
            break;
        
        case lda:
            if(lr==1){
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
                pc++;
            }else{
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
            }
            break;
        
        case ldb:
            if(lr==1){
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
                pc++;
            }else{
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
            }
            break;
        
        case sta:
            if(lr==1){
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
                pc++;
            }else{
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
            }
            break;
        
        case stb:
            if(lr==1){
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
                pc++;
            }else{
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
            }
            break;
        
        case ldrb:
            if(lr==1){
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
                }
                pc++;
            }else{
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
                }
            }
            break;

        
        case movial:
            if(lr==1){
                a = 0;
                a = imm & 0x00FF;
            /*  1010 0000 0000 1110
                0000 0000 1111 1111*/  
                pc++;
            }else{
                a = 0;
                a = imm & 0x00FF;
            /*  1010 0000 0000 1110
                0000 0000 1111 1111*/  
            }
            break;
        
        case moviah:
            if(lr==1){
                a = imm & 0x00FF << 8;
            /*  1010 0000 0000 1110
                0000 0000 1111 1111
                1111 1111 0000 0000*/  
                pc++;
            }else{
                a = imm & 0x00FF << 8;
            /*  1010 0000 0000 1110
                0000 0000 1111 1111
                1111 1111 0000 0000*/  
            }
            break;
        
        case addia:
            if(lr==1){
                a = a + imm; /*???????????????*/
                pc++;
            }else{
                a = a + imm; /*???????????????*/
            }
            break;
        
        case subia:
            if(lr==1){
                a = a - imm; /*???????????????*/
                pc++;
            }else{
                a = a - imm; /*???????????????*/
            }
            break;

        case mulia:
            if(lr==1){
                a = a * imm; /*???????????????*/
                pc++;
            }else{
                a = a * imm; /*???????????????*/
            }
            break;

        case divia:
            if(lr==1){
                a = a / imm; /*???????????????*/
                pc++;
            }else{
                a = a / imm; /*???????????????*/
            }
            break;

        case lsh:
            if(lr==1){
                a = a << imm;
                pc++;
            }else{
                a = a << imm;
            }
            break;

        case rsh:
            if(lr==1){
                a = a >> imm;
                pc++;
            }else{
                a = a >> imm;
            }
            break;
    }
    lr!=lr;
}
void identifica_instr(int memoria){
    unsigned char *ponteiro, a, mine[8]; // aux recebe rg0
    unsigned int count = 0, imediatoMem, palavra;

    ponteiro = strtok(ponteiro," ,");
    while(ponteiro){
        if(count == 0){
            strcpy(mine,ponteiro);
        }
        if (count== 1){
            a = (int)strtol(ponteiro,NULL,16);
        }
        if(count == 2){
            imediatoMem = (int)strtol(ponteiro,NULL,16);
        }
        ponteiro = strtok(NULL," ,r");
        count++;
    }
    if(strcmp(mine,"nop")== 0) {
        palavra = 1;
        palavra = palavra << 11;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"add")== 0){
        palavra = 2;
        palavra =  palavra << 18;
        preencher_memoria(memoria,palavra);
    } else if(strcmp(mine,"sub")== 0) {
        palavra = 3;
        palavra = palavra << 18;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"mul")== 0) {
        palavra = 4;
        palavra = palavra << 18;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"div")== 0) {
        palavra = 5;
        palavra = palavra << 18;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"cmp")== 0) {
        palavra = 6;
        palavra = palavra << 18;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"movr")== 0) {
        palavra = 7;
        palavra = palavra << 18;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"and")== 0) {
        palavra = 8;
        palavra = palavra << 18;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"or")== 0) {
        palavra = 9;
        palavra = palavra << 18;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"xor")== 0) {
        palavra = 10;
        palavra = palavra << 18;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"not")== 0) {
        palavra = 11;
        palavra = (palavra << 3)<<21;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"je")== 0) {
        palavra = 12;
        palavra = (palavra << 24)| imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"jne")== 0) {
        palavra = 13;
        palavra = (palavra << 24)| imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"jl")== 0) {
        palavra = 14;
        palavra = (palavra << 24)| imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"jle")== 0) {
        palavra = 15;
        palavra = (palavra << 24)| imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"jg")== 0) {
        palavra = 16;
        palavra = (palavra << 24)| imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"jge")== 0) {
        palavra = 17;
        palavra = (palavra << 24)| imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"jmp")== 0) {
        palavra = 18;
        palavra = (palavra << 24)| imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"ld")== 0){
        palavra = 19;
        palavra = (palavra << 21)| imediatoMem;
        preencher_memoria(memoria,palavra);
    } else if(strcmp(mine,"st")== 0){
        palavra = 20;
        palavra = (palavra << 21)| imediatoMem;
        preencher_memoria(memoria,palavra);
    } else if(strcmp(mine,"movi")== 0) {
        palavra = 21;
        palavra = (palavra << 21) | imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"addi")== 0) {
        palavra = 22;
        palavra = (palavra << 21) | imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"subi")== 0) {
        palavra = 23;
        palavra = (palavra << 21) | imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"muli")== 0) {
        palavra = 24;
        palavra = (palavra << 21) | imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"divi")== 0) {
        palavra = 25;
        palavra = (palavra << 21) | imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"lsh")== 0) {
        palavra = 26;
        palavra = (palavra << 21) | imediatoMem;
        preencher_memoria(memoria, palavra);
    } else if(strcmp(mine,"rsh")== 0) {
        palavra = 27;
        palavra = (palavra << 21) | imediatoMem;
        preencher_memoria(memoria, palavra);
    } else{
        palavra  = 0;
        preencher_memoria(memoria,palavra);
    }
}


void texto(){
    unsigned int memo, valor;
    FILE *arq;
    unsigned char tipo, linha[40];
    unsigned int count = 0;
    arq = fopen("programa.txt", "r");

    while (fgets(linha, 40, arq) != NULL){
        ponteiro = strtok(linha, "; ");
        memo = (int)strtol(ponteiro,NULL,16);
        while(ponteiro){
            if(count == 1){
                tipo = *ponteiro;
            }else if(count == 2){
                if(tipo == 0x64){
                    valor = (int)strtol(ponteiro,NULL,16);
                    memoria[memo++] = (valor & 0xff000000) >> 24;
                    memoria[memo++] = (valor & 0x00ff0000) >> 16;
                    memoria[memo++] = (valor & 0x0000ff00) >> 8;
                    memoria[memo]   = (valor & 0x000000ff);
                }else{
                    identifica_instr(memo);
                }
            }

            ponteiro = strtok(NULL ,";");
            count++;
        }
        count = 0;
    }

    if (NULL == arq)
        printf("Erro ao tentar abrir programa.txt \n");
    fclose(arq); 
}

int main(void){
    char count;
    
    
      //Fim da busca
    // lerTexto();
    while(count!='s'){
        if(lr==1){
            // decodifica();
            // executa();
        }else{
            // busca();
            // decodifica();
            // executa();
        }
      printf("CPU:\n\tA:   %x  B:   %x  T:   %x\n",a,b,t);
      printf("\tMBR: %x  MAR: %x  IMM: %x\n",mbr,mar,imm);
      printf("\tPC:  %x  IR:  %x  LR:  %x\n",pc,ir,lr);
      printf("\tE:   %x  L:   %x  G:   %x\n",e,l,g);
      
      printf("Memoria:\n");
        for(int i = 0 ; i< 155;i++){
            printf("[%x]=%x\t",i,memoria[i]);
            if(i%10 == 0 && i !=0)
                printf("\n");
        }
      printf("\n\nAperte enter para um novo ciclo ou aperte a tecla S para parar o programa ");
      scanf("%c",&count);
  }
  
}