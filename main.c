#include <stdio.h>

int contador = 0;
unsigned int mbr, mar = 0x0, imm;
unsigned int pc = 0x0;
unsigned int reg[8];
unsigned char memoria[154], ir, ro0, ro1, e, l, g;

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
    memoria[0] = 0x13;
    memoria[1] = 0x00;
    memoria[2] = 0x00;
    memoria[3] = 0x92;
    memoria[146] = 0x00;
    memoria[147] = 0x00;
    memoria[148] = 0x00;
    memoria[149] = 0x05;

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
            printf("\nMemória[%d]: %x", contador, reg[contador]);
            contador = contador + 1;
        };
        printf("\n------------ Acaba instrução ------------\n\n\n\n");
    };
    return 0;
};
