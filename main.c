#include <stdio.h>

// Busca
unsigned int busca(unsigned int pc, char memoria[], unsigned char ir, unsigned int mbr) {
    //Carregar mbr - buscar instrução -
    mbr = memoria[pc++] << 8;
    mbr = (mbr | memoria[pc++]) << 8;
    mbr = (mbr | memoria[pc++]) << 8;
    mbr = mbr | memoria[pc++];
    return(mbr);
};

// Decodificação
unsigned int opcode(unsigned int mbr){
    unsigned char ir;
    ir = (mbr) >> 24;
    return(ir);
};

unsigned int mbr = 0, mar, imm, pc = 0;
unsigned int reg[8];
unsigned char ir, ro0, ro1, e, l, g;
char memoria[154];

int main(void) {
    mbr = busca(pc, memoria, ir, mbr);
    ir  = opcode(mbr);

    // Execução
    if (ir <= 2){
        if (ir == 0){//hlt
            pc = 154;
        };
        if (ir == 1){//nop
            pc += 4;
    };

    if(ir >= 3 & ir <= 11){
        ro0 = (mbr & 0x00e00000) >> 21;
        ro1 = (mbr & 0x001c0000) >> 18;

        if (ir == 2){//add
            reg[ro0] = reg[ro0] + reg[ro1];
        };

        if (ir == 3){//sub
            reg[ro0] = reg[ro0] - reg[ro1];
        };

        if (ir == 4){//mul
            reg[ro0] = reg[ro0] * reg[ro1];
        };

        if (ir == 5){//div
            reg[ro0] = reg[ro0] / reg[ro1];
        };

        if (ir == 6){//cmp

        };

        if (ir == 7){//movr
            reg[ro0] = reg[ro1];
        };

        if (ir == 8){//and
            reg[ro0] = reg[ro0] & reg[ro1];
        };

        if (ir == 9){//or
            reg[ro0] = reg[ro0] | reg[ro1];
        };

        if (ir == 10){//xor
            reg[ro0] = reg[ro0] ^ reg[ro1];
        };





    };
}






















    };





    if (ir == 00001011){//not };
    if (ir == 00001100){//je };
    if (ir == 00001101){//jne };
    if (ir == 00001110){//jl };
    if (ir == 00001111){//jle };
    if (ir == 00010000){//jg };
    if (ir == 00010001){//jge };
    if (ir == 00010010){//jmp };
    if (ir == 00010011){//ld };
    if (ir == 00010100){//st };
    if (ir == 00010101){//movi };
    if (ir == 00010110){//addi };
    if (ir == 00010111){//subi };
    if (ir == 00011000){//muli };
    if (ir == 00011001){//divi };
    if (ir == 00011010){//lsh };
    if (ir == 00011011){//rsh };
}
