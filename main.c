#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int contador = 0, classificacao;
unsigned int mbr, mar = 0x0, imm;
unsigned int pc = 0x0;
unsigned int reg[8];
unsigned char memoria[154], ir, ro0, ro1, e, l, g;

// Leitura
unsigned int indicememoria, conteudo;
unsigned char linha[];
FILE *programa;
unsigned char *partestr;

void preenchendo(unsigned int mem , unsigned int aux){
    memoria[mem++] = (aux & 0xff000000) >> 24;
    memoria[mem++] = (aux & 0x00ff0000) >> 16;
    memoria[mem++] = (aux & 0x0000ff00) >> 8;
    memoria[mem] = (aux & 0x0000ff);
}

instrucaoaddtoxor(num, word, registrador, memoriaimediato){
    word = num;
    word = (word << 3) | registrador;
    word = (word << 3) | memoriaimediato;
    word =  word << 18;
}

instrucaojetojmp(num, word, memoriaimediato){
    word = num;
    word = (word << 24)| memoriaimediato;
}

preenchermemoria(indicememoria){
    unsigned char *p, minemonico[10], registrador;
    unsigned int contar = 0, memoriaimediato, word;
    p = strtok(p, " ,");
    while (p){
        if(contar == 0){
            strcpy(minemonico, p);
        }
        if (contar == 1){
            registrador = (int) strtol(p, NULL, 16);
        }
        if (contar == 2){
            memoriaimediato = (int) strtol(p, NULL, 16);
        }
        p = strtok(NULL, " ,r");
        contar++;
    }
    // PQ não faz com hlt?
    if (strcmp(minemonico, "nop") == 0){
        word = 1;
        word = word << 24;
        preenchendo(indicememoria, word);
    }
    else if (strcmp(minemonico, "add")== 0){
        instrucaoaddtoxor(2, word, registrador, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if (strcmp(minemonico, "sub")== 0) {
        instrucaoaddtoxor(3, word, registrador, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if (strcmp(minemonico, "mul")== 0) {
        instrucaoaddtoxor(4, word, registrador, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if (strcmp(minemonico, "div")== 0) {
        instrucaoaddtoxor(5, word, registrador, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if (strcmp(minemonico, "cmp")== 0) {
        instrucaoaddtoxor(6, word, registrador, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if (strcmp(minemonico, "movr")== 0) {
        instrucaoaddtoxor(7, word, registrador, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if (strcmp(minemonico, "and")== 0) {
        instrucaoaddtoxor(8, word, registrador, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if (strcmp(minemonico, "or")== 0) {
        instrucaoaddtoxor(9, word, registrador, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if (strcmp(minemonico, "xor")== 0) {
        instrucaoaddtoxor(10, word, registrador, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "not")== 0) {
        word = 11;
        word = ((word << 3)|registrador) << 21;
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "je")== 0) {
        instrucaojetojmp(12, word, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "jne")== 0) {
        instrucaojetojmp(13, word, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "jl")== 0) {
        instrucaojetojmp(14, word, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "jle")== 0) {
        instrucaojetojmp(15, word, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "jg")== 0) {
        instrucaojetojmp(16, word, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "jge")== 0) {
        instrucaojetojmp(17, word, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "jmp")== 0) {
        instrucaojetojmp(18, word, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "ld")== 0){
        instrucaojetojmp(19, word, memoriaimediato);
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "st")== 0){
        word = 20;
        word = (word << 3) | registrador;
        word = (word << 21)| memoriaimediato;
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "movi")== 0) {
        word = 21;
        word = (word << 3) | registrador;
        word = (word << 21) | memoriaimediato;
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "addi")== 0) {
        word = 22;
        word = (word << 3) | registrador;
        word = (word << 21) | memoriaimediato;
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "subi")== 0) {
        word = 23;
        word = (word << 3) | registrador;
        word = (word << 21) | memoriaimediato;
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "muli")== 0) {
        word = 24;
        word = (word << 3) | registrador;
        word = (word << 21) | memoriaimediato;
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "divi")== 0) {
        word = 25;
        word = (word << 3) | registrador;
        word = (word << 21) | memoriaimediato;
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "lsh")== 0) {
        word = 26;
        word = (word << 3) | registrador;
        word = (word << 21) | memoriaimediato;
        preenchendo(indicememoria, word);
    }
    else if(strcmp(minemonico, "rsh")== 0) {
        word = 27;
        word = (word << 3) | registrador;
        word = (word << 21) | memoriaimediato;
        preenchendo(indicememoria, word);
    }
    else{
        word  = 0;
        preenchendo(indicememoria, word);
    }
}

void carregartxt(){
    programa = fdopen("programa.txt", "r");
    while (fgets(linha, 50, programa) != NULL){
        partestr = strtok(linha, "; ");
        indicememoria = (int) strtol(partestr, NULL, 16);
        while (partestr){
            if (contador == 1){
                classificacao = partestr;
            }
            else if (contador == 2){
                if(classificacao == 0x64) {//d
                    conteudo = (int) strtol(partestr, NULL, 16);
                        memoria[indicememoria++] = (conteudo & 0xff000000) >> 24;
                        memoria[indicememoria++] = (conteudo & 0x00ff0000) >> 16;
                        memoria[indicememoria++] = (conteudo & 0x0000ff00) >> 8;
                        memoria[indicememoria]   = (conteudo & 0x000000ff);
                }
                else{
                    preenchermemoria(indicememoria);
                }
            }
            partestr = strtok(NULL, ";");
            contador++;
        }
        contador = 0;
    }
    if (NULL == programa){
        printf("ERRO AO ABRIR SEU PROGRAMA\n");
        fclose(programa);
    }
};


void buscaNaMemoria(){
    mbr = memoria[mar];
    mbr = (mbr<<8) | ++mar;
    mbr = (mbr<<8) | ++mar;
    mbr = (mbr<<8) | ++mar;
};

void busca() {
    mbr = memoria[pc++] << 8;
    mbr = (mbr | memoria[pc++]) << 8;
    mbr = (mbr | memoria[pc++]) << 8;
    mbr = mbr | memoria[pc++];
};

void opcode(){
    ir = (mbr) >> 24;
};

void registradorRo0(){
    ro0 = (mbr & 0x00e00000) >> 21;
};

void registradorRo1(){
    ro1 = (mbr & 0x001c0000) >> 18;
};

void registradorImm(){
    imm = mbr & 0x001fffff;
};

void registradorMar(){
    mar = mbr & 0x001fffff;
}
int main(void) {
    while (contador != 154){
        printf("\nMemória[%d]: %x", contador, memoria[contador]);
        contador = contador + 1;
    };
    // Busca -----------------------------------------------------------------------------------------------------------
    busca();


    // Decodificação ---------------------------------------------------------------------------------------------------
    opcode();
    if (ir >= 3 & ir <= 11) {
        registradorRo0();
        registradorRo1();
    }

    if (ir == 11) {
        registradorRo0();
    }

    if (ir > 12 & ir <= 18) {
        registradorMar();
    }

    if (ir == 19 | ir == 20) {
        registradorRo0();
        registradorMar();
    }

    if (ir >= 21 & ir <= 27) {
        registradorRo0();
        registradorImm();
    }

    while (ir != 0x0) {
        // Execução --------------------------------------------------------------------------------------------------------

        if (ir <= 2) {
            if (ir == 0) {//hlt
            };
            if (ir == 1) {//nop
                pc += 4;
            };
        };

        if (ir >= 3 & ir <= 11) {
            if (ir == 2) {//add
                reg[ro0] = reg[ro0] + reg[ro1];
                pc += 4;
            } else if (ir == 3) {//sub
                reg[ro0] = reg[ro0] - reg[ro1];
                pc += 4;
            } else if (ir == 4) {//mul
                reg[ro0] = reg[ro0] * reg[ro1];
                pc += 4;
            } else if (ir == 5) {//div
                reg[ro0] = reg[ro0] / reg[ro1];
                pc += 4;
            } else if (ir == 6) {//cmp
                e = 0x00;
                l = 0x00;
                g = 0x00;

                if (ro0 == ro1) {
                    e = 0x01;
                    pc += 4;
                } else if (ro0 < ro1) {
                    l = 0x01;
                    pc += 4;
                } else if (ro0 > ro1) {
                    g = 0x01;
                    pc += 4;
                };
            } else if (ir == 7) {//movr
                reg[ro0] = reg[ro1];
                pc += 4;
            } else if (ir == 8) {//and
                reg[ro0] = reg[ro0] & reg[ro1];
                pc += 4;
            } else if (ir == 9) {//or
                reg[ro0] = reg[ro0] | reg[ro1];
                pc += 4;
            } else if (ir == 10) {//xor
                reg[ro0] = reg[ro0] ^ reg[ro1];
                pc += 4;
            };
        };

        if (ir == 11) {
            reg[ro0] = !(reg[ro0]);
            pc += 4;
        };

        if (ir > 12 & ir <= 18) {
            if (ir == 12) {//je
                if (e == 1) {
                    pc = mar;
                };
            } else if (ir == 13) {//jne
                if (e == 0) {
                    pc = mar;
                };
            } else if (ir == 14) {//jl
                if (l == 1) {
                    pc = mar;
                };
            } else if (ir == 15) {//jle
                if (e == 1 | l == 1) {
                    pc = mar;
                };
            } else if (ir == 16) {//jg
                if (g == 1) {
                    pc = mar;
                };
            } else if (ir == 17) {//jge
                if (e == 1 | g == 1) {
                    pc = mar;
                };
            } else if (ir == 18) {//jmp
                pc = mar;
            };
        };

        if (ir == 19 | ir == 20) {
            if (ir == 19) {//ld;
                //mbr = (memoria[mar]) << 8;
                mbr = (memoria[mar++]) << 8;
                mbr = (mbr | memoria[mar++]) << 8;
                mbr = (mbr | memoria[mar++]) << 8;
                mbr = (mbr | memoria[mar++]);
                reg[ro0] = mbr;
                pc += 4;
            } else if (ir == 20) {//st
                //memoria = // 1010 1010 1011 1011 1100 1100 1101 1101
                memoria[mar++] = mbr >> 24;
                //             0000 0000 0000 0000 0000 0000 1010 1010
                memoria[mar++] = (mbr >> 16) & 0xff;
                //             0000 0000 0000 0000 0000 0000 1011 1011
                memoria[mar++] = (mbr >> 8) & 0xff;
                //             0000 0000 0000 0000 0000 0000 1100 1100
                memoria[mar++] = mbr & 0xff;
                //             0000 0000 0000 0000 0000 0000 1101 1101
                pc += 4;
            };
        };

        if (ir >= 21 & ir <= 27) {
            if (ir == 21) {//movi
                reg[ro0] = imm;
                pc += 4;
            } else if (ir == 22) {//addi
                reg[ro0] = reg[ro0] + imm;
                pc += 4;
            } else if (ir == 23) {//subi
                reg[ro0] = reg[ro0] - imm;
                pc += 4;
            } else if (ir == 24) {//muli
                reg[ro0] = reg[ro0] - imm;
                pc += 4;
            } else if (ir == 25) {//divi
                reg[ro0] = reg[ro0] / imm;
                pc += 4;
            } else if (ir == 26) {//lsh
                reg[ro0] = reg[ro0] << imm;
                pc += 4;
            } else if (ir == 27) {//rsh
                reg[ro0] = reg[ro0] >> imm;
                pc += 4;
            };
        };

        printf("\nMbr: %x", mbr);
        printf("\nMar: %x", mar);
        printf("\nImm: %x", imm);
        printf("\nPc: %x", pc);
        printf("\nReg[0]: %x", reg[0]);
        printf("\nReg[1]: %x", reg[1]);
        printf("\nReg[2]: %x", reg[2]);
        printf("\nReg[3]: %x", reg[3]);
        printf("\nReg[4]: %x", reg[4]);
        printf("\nReg[5]: %x", reg[5]);
        printf("\nReg[6]: %x", reg[6]);
        printf("\nReg[7]: %x", reg[7]);
        printf("\nIr: %x", ir);
        printf("\nRo0: %x", ro0);
        printf("\nRo1: %x", ro1);
        printf("\nE: %x", e);
        printf("\nL: %x", l);
        printf("\nG: %x", g);

        while (contador != 154){
            printf("\nMemória[%d]: %x", contador, memoria[contador]);
            contador = contador + 1;
        };
        printf("\n------------ Acaba instrução ------------\n\n");
    };
    return 0;
};
