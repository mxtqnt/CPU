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
        if (ir == 1) {//nop
            pc += 4;
        };
    };

    if(ir >= 3 & ir <= 11) {
        ro0 = (mbr & 0x00e00000) >> 21;
        ro1 = (mbr & 0x001c0000) >> 18;

        if (ir == 2) {//add
            reg[ro0] = reg[ro0] + reg[ro1];
        };

        if (ir == 3) {//sub
            reg[ro0] = reg[ro0] - reg[ro1];
        };

        if (ir == 4) {//mul
            reg[ro0] = reg[ro0] * reg[ro1];
        };

        if (ir == 5) {//div
            reg[ro0] = reg[ro0] / reg[ro1];
        };

        if (ir == 6) {//cmp
            e = 0x00;
            l = 0x00;
            g = 0x00;

            if (ro0 == ro1){
                e = 0x01;
            };

            if (ro0 < ro1){
               l = 0x01;
            };

            if (ro0 > ro1){
                g = 0x01;
            };
        };

        if (ir == 7) {//movr
            reg[ro0] = reg[ro1];
        };

        if (ir == 8) {//and
            reg[ro0] = reg[ro0] & reg[ro1];
        };

        if (ir == 9) {//or
            reg[ro0] = reg[ro0] | reg[ro1];
        };

        if (ir == 10) {//xor
            reg[ro0] = reg[ro0] ^ reg[ro1];
        };
    };

    if(ir == 11){
        ro0 = (mbr & 0x00e00000) >> 21;
        reg[ro0] = !(reg[ro0]);
    };

    if(ir > 12 & ir <= 18){
        mar = mbr & 0x001fffff;

        if (ir == 12){//je
            if(e == 1){
              pc = mar; //???????
            };
        };

        if (ir == 13){//jne
            if(e == 0){
                pc = mar; //???????
            };
        };

        if (ir == 14){//jl
            if(l == 1){
                pc = mar; //???????
            };
        };

        if (ir == 15){//jle
            if(e == 1 | l == 1){
                pc = mar; //???????
            };
        };

        if (ir == 16){//jg
            if(g == 1){
                pc = mar; //???????
            };
        };

        if (ir == 17){//jge
            if(e == 1 | g == 1){
                pc = mar; //???????
            };
        };

        if (ir == 18){//jmp
            pc = mar; //???????
        };
    };

    if(ir == 19 | ir == 20){
        ro0 = (mbr & 0x00e00000) >> 21;
        mar = mbr & 0x001fffff;

        if (ir == 19){//ld
            // 1100 1010 1111 1110 1100 1010 1111 1110
            // C    A    F    E    C    A    F    E
            // MAR
            // 
            //
            //
            //
            //
            

            reg[ro0] = memoria[mar];
        };

        if (ir == 20){//st
        };
    };
};
