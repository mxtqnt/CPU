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
            if(lr==1){
                a=a-b;
                pc++;
            }else{
                a=a-b;
            } 

        case mul:
            if(lr==1){
                a=a*b;
                pc++;
            }else{
                a=a*b;
            } 

        case div:
            if(lr==1){
                a=a/b;
                pc++;
            }else{
                a=a/b;
            } 


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
        
        case and:
            if(lr==1){
                a=a&b;
                pc++;
            }else{
                a=a&b;
            }
        
        case or:
            if(lr==1){
                a=a|b;
                pc++;
            }else{
                a=a|b;
            }
        
        case xor:
            if(lr==1){
                a=a^b;
                pc++;
            }else{
                a=a^b;
            }
        
        case not:
            if(lr==1){
                a=!a;
                pc++;
            }else{
                a=!a;
            }
        
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
        
        case jmp:
            if(lr==1){
                pc=mar;
                pc++;
            }else{
                pc=mar;
            }
        
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
                }break;
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
                }break;
            }

        
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
        
        case addia:
            if(lr==1){
                a = a + imm; /*???????????????*/
                pc++;
            }else{
                a = a + imm; /*???????????????*/
            }
        
        case subia:
            if(lr==1){
                a = a - imm; /*???????????????*/
                pc++;
            }else{
                a = a - imm; /*???????????????*/
            }

        case mulia:
            if(lr==1){
                a = a * imm; /*???????????????*/
                pc++;
            }else{
                a = a * imm; /*???????????????*/
            }

        case divia:
            if(lr==1){
                a = a / imm; /*???????????????*/
                pc++;
            }else{
                a = a / imm; /*???????????????*/
            }

        case lsh:
            if(lr==1){
                a = a << imm;
                pc++;
            }else{
                a = a << imm;
            }

        case rsh:
            if(lr==1){
                a = a >> imm;
                pc++;
            }else{
                a = a >> imm;
            }
    }
    lr!=lr;
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