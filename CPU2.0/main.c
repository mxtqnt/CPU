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
            }else{
                lr!=lr;
            }
            break;
            
        case add:
            if(lr==1){
                a=a+b;
                pc++;
                lr=!lr;
            }else{
                a=a+b;
                lr=!lr;
            }            
            break;

        case sub:
            if(lr==1){
                a=a-b;
                pc++;
                lr=!lr;
            }else{
                a=a-b;
                lr=!lr;
            } 
            break;

        case mul:
            if(lr==1){
                a=a*b;
                pc++;
                lr=!lr;
            }else{
                a=a*b;
                lr=!lr;
            } 
            break;

        case div:
            if(lr==1){
                a=a/b;
                pc++;
                lr=!lr;
            }else{
                a=a/b;
                lr=!lr;
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
                lr=!lr;
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
                lr=!lr;
            } 
            break;

        case xchg:
            if(lr==1){
                t=a;
                a=b;
                b=t;
                pc++;
                lr=!lr;
            }else{
                t=a;
                a=b;
                b=t;
                lr=!lr;
            }
            break;
        
        case and:
            if(lr==1){
                a=a&b;
                pc++;
                lr=!lr;
            }else{
                a=a&b;
                lr=!lr;
            }
            break;
        
        case or:
            if(lr==1){
                a=a|b;
                pc++;
                lr=!lr;
            }else{
                a=a|b;
                lr=!lr;
            }
            break;
        
        case xor:
            if(lr==1){
                a=a^b;
                pc++;
                lr=!lr;
            }else{
                a=a^b;
                lr=!lr;
            }
            break;
        
        case not:
            if(lr==1){
                a=!a;
                pc++;
                lr=!lr;
            }else{
                a=!a;
                lr=!lr;
            }
            break;
        
        case je:
            if(lr==1){
                if(e=1){
                    pc=mar;
                }
                pc++;
                lr=!lr;
            }else{
                if(e=1){
                    pc=mar;
                }
                lr=!lr;
            }
            break;
        
        case jne:
            if(lr==1){
                if(e=0){
                    pc=mar;
                }
                pc++;
                lr=!lr;
            }else{
                if(e=0){
                    pc=mar;
                }
                lr=!lr;
            }
            break;

        case jl:
            if(lr==1){
                if(l=1){
                    pc=mar;
                }
                pc++;
                lr=!lr;
            }else{
                if(l=1){
                    pc=mar;
                }
                lr=!lr;
            }
            break;
        
        case jle:
            if(lr==1){
                if(l==1 || e==1){
                    pc=mar;
                }
                pc++;
                lr=!lr;
            }else{
                if(l==1 || e==1){
                    pc=mar;
                }
                lr=!lr;
            }
            break;
        
        case jg:
            if(lr==1){
                if(g==1){
                    pc=mar;
                }
                pc++;
                lr=!lr;
            }else{
                if(g==1){
                    pc=mar;
                }
                lr=!lr;
            }
            break;

        case jge:
            if(lr==1){
                if(g==1 || e==1){
                    pc=mar;
                }
                pc++;
                lr=!lr;
            }else{
                if(g==1 || e==1){
                    pc=mar;
                }
                lr=!lr;
            }
            break;
        
        case jmp:
            if(lr==1){
                pc=mar;
                pc++;
                lr=!lr;
            }else{
                pc=mar;
                lr=!lr;
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
                lr=!lr;
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
                lr=!lr;
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
                lr=!lr;
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
                lr=!lr;
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
                lr=!lr;
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
                lr=!lr;
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
                lr=!lr;
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
                lr=!lr;
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
                lr=!lr;
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
                lr=!lr;
            }
            break;

        
        case movial:
            if(lr==1){
                a = 0;
                a = imm & 0x00FF;
            /*  1010 0000 0000 1110
                0000 0000 1111 1111*/  
                pc++;
                lr=!lr;
            }else{
                a = 0;
                a = imm & 0x00FF;
            /*  1010 0000 0000 1110
                0000 0000 1111 1111*/  
                lr=!lr;
            }
            break;
        
        case moviah:
            if(lr==1){
                a = imm & 0x00FF << 8;
            /*  1010 0000 0000 1110
                0000 0000 1111 1111
                1111 1111 0000 0000*/  
                pc++;
                lr=!lr;
            }else{
                a = imm & 0x00FF << 8;
            /*  1010 0000 0000 1110
                0000 0000 1111 1111
                1111 1111 0000 0000*/  
                lr=!lr;
            }
            break;
        
        case addia:
            if(lr==1){
                a = a + imm; /*???????????????*/
                pc++;
                lr=!lr;
            }else{
                a = a + imm; /*???????????????*/
                lr=!lr;
            }
            break;
        
        case subia:
            if(lr==1){
                a = a - imm; /*???????????????*/
                pc++;
                lr=!lr;
            }else{
                a = a - imm; /*???????????????*/
                lr=!lr;
            }
            break;

        case mulia:
            if(lr==1){
                a = a * imm; /*???????????????*/
                pc++;
                lr=!lr;
            }else{
                a = a * imm; /*???????????????*/
                lr=!lr;
            }
            break;

        case divia:
            if(lr==1){
                a = a / imm; /*???????????????*/
                pc++;
                lr=!lr;
            }else{
                a = a / imm; /*???????????????*/
                lr=!lr;
            }
            break;

        case lsh:
            if(lr==1){
                a = a << imm;
                pc++;
                lr=!lr;
            }else{
                a = a << imm;
                lr=!lr;
            }
            break;

        case rsh:
            if(lr==1){
                a = a >> imm;
                pc++;
                lr=!lr;
            }else{
                a = a >> imm;
                lr=!lr;
            }
            break;
    }
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
    memoria[0]=0x98;
    memoria[1]=0x96;
    memoria[2]=0xa0;
    memoria[3]=0x98;
    memoria[4]=0x18;
    memoria[5]=0x00;
    memoria[6]=0x38;
    memoria[7]=0x00;
    memoria[8]=0x98;
    memoria[9]=0x94;
    memoria[10]=0x28;
    memoria[11]=0x00;
    memoria[12]=0xa0;
    memoria[13]=0x92;
    memoria[14]=0x20;
    memoria[15]=0x00;
    memoria[16]=0xa0;
    memoria[17]=0x90;
    memoria[18]=0x10;
    memoria[19]=0x00;
    memoria[20]=0xa8;
    memoria[21]=0x8e;
    memoria[22]=0x00;
    memoria[23]=0x00;
    memoria[24]=0x00;
    memoria[25]=0x00;
    memoria[26]=0x00;
    memoria[27]=0x00;
    memoria[28]=0x00;
    memoria[29]=0x00;
    memoria[30]=0x00;
    memoria[31]=0x00;
    memoria[32]=0x00;
    memoria[33]=0x00;
    memoria[34]=0x00;
    memoria[35]=0x00;
    memoria[36]=0x00;
    memoria[37]=0x00;
    memoria[38]=0x00;
    memoria[39]=0x00;
    memoria[40]=0x00;
    memoria[41]=0x00;
    memoria[42]=0x00;
    memoria[43]=0x00;
    memoria[44]=0x00;
    memoria[45]=0x00;
    memoria[46]=0x00;
    memoria[47]=0x00;
    memoria[48]=0x00;
    memoria[49]=0x00;
    memoria[50]=0x00;
    memoria[51]=0x00;
    memoria[52]=0x00;
    memoria[53]=0x00;
    memoria[54]=0x00;
    memoria[55]=0x00;
    memoria[56]=0x00;
    memoria[57]=0x00;
    memoria[58]=0x00;
    memoria[59]=0x00;
    memoria[60]=0x00;
    memoria[61]=0x00;
    memoria[62]=0x00;
    memoria[63]=0x00;
    memoria[64]=0x00;
    memoria[65]=0x00;
    memoria[66]=0x00;
    memoria[67]=0x00;
    memoria[68]=0x00;
    memoria[69]=0x00;
    memoria[70]=0x00;
    memoria[71]=0x00;
    memoria[72]=0x00;
    memoria[73]=0x00;
    memoria[74]=0x00;
    memoria[75]=0x00;
    memoria[76]=0x00;
    memoria[77]=0x00;
    memoria[78]=0x00;
    memoria[79]=0x00;
    memoria[80]=0x00;
    memoria[81]=0x00;
    memoria[82]=0x00;
    memoria[83]=0x00;
    memoria[84]=0x00;
    memoria[85]=0x00;
    memoria[86]=0x00;
    memoria[87]=0x00;
    memoria[88]=0x00;
    memoria[89]=0x00;
    memoria[90]=0x00;
    memoria[91]=0x00;
    memoria[92]=0x00;
    memoria[93]=0x00;
    memoria[94]=0x00;
    memoria[95]=0x00;
    memoria[96]=0x00;
    memoria[97]=0x00;
    memoria[98]=0x00;
    memoria[99]=0x00;
    memoria[100]=0x00;
    memoria[101]=0x00;
    memoria[102]=0x00;
    memoria[103]=0x00;
    memoria[104]=0x00;
    memoria[105]=0x00;
    memoria[106]=0x00;
    memoria[107]=0x00;
    memoria[108]=0x00;
    memoria[109]=0x00;
    memoria[110]=0x00;
    memoria[111]=0x00;
    memoria[112]=0x00;
    memoria[113]=0x00;
    memoria[114]=0x00;
    memoria[115]=0x00;
    memoria[116]=0x00;
    memoria[117]=0x00;
    memoria[118]=0x00;
    memoria[119]=0x00;
    memoria[120]=0x00;
    memoria[121]=0x00;
    memoria[122]=0x00;
    memoria[123]=0x00;
    memoria[124]=0x00;
    memoria[125]=0x00;
    memoria[126]=0x00;
    memoria[127]=0x00;
    memoria[128]=0x00;
    memoria[129]=0x00;
    memoria[130]=0x00;
    memoria[131]=0x00;
    memoria[132]=0x00;
    memoria[133]=0x00;
    memoria[134]=0x00;
    memoria[135]=0x00;
    memoria[136]=0x00;
    memoria[137]=0x00;
    memoria[138]=0x00;
    memoria[139]=0x00;
    memoria[140]=0x00;
    memoria[141]=0x00;
    memoria[142]=0x00;
    memoria[143]=0x00;
    memoria[144]=0x00;
    memoria[145]=0x20;
    memoria[146]=0x00;
    memoria[147]=0x03;
    memoria[148]=0x00;
    memoria[149]=0x04;
    memoria[150]=0x00;
    memoria[151]=0x05;
    memoria[152]=0x00;
    memoria[153]=0x03;


    char count;
    
      //Fim da busca
    // lerTexto();
    while(count!='s'){
        if(lr==1){
            decodifica();
            executa();
        }else{
            busca();
            decodifica();
            executa();
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