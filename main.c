#include <stdio.h>

int main(void) {
    //Memória
    unsigned char memoria[154];

    //1 MBR – Memory Buffer Register
    //2 MAR – Memory Address Register
    //6 IMM – Immediate
    //7 PC – Program Counter
    unsigned int mbr, mar, imm, pc;

    //9 r0 a r7
    unsigned int reg[8];

    //3 IR – Instruction Register
    //4 RO0 – Register Operand 0
    //5 RO1 – Register Operand 1
    //8 E, L e G
    unsigned char ir, ro0, ro1, e, l, g;

    //Instruções ----------------------------------------
    // hlt              0b0000 0000         - Fim
    // nop              0b0000 0001         - Pc incrementado
    // add regX, regY   0b0000 0010         - Soma X = X+Y
    // sub regX, regY   0b0000 0011         - Subtração X = X-Y
    // mul regX, regY   0b0000 0100         - Multiplicação X = X . Y
    // div regX, regY   0b0000 0101         - Divisão X = X÷Y
    // cmp regX, regY   0b0000 0110         - Compara X e Y, = E, < L, > G
    // movr regX, regY  0b0000 0111         - Atribui X = Y
    // and regX, regY   0b0000 1000         - AND X = X & Y
    // or regX, regY    0b0000 1001         - OR X = X | Y
    // xor regX, regY   0b0000 1010         - XOR X = X ^ Y
    // not regX         0b0000 1011         - NOT X = !X
    // je M[X]          0b0000 1100         - IF =, caso E = 1 muda PC para endereço x
    // jne M[X]         0b0000 1101         - IF ≠, caso E = 0 muda PC para endereço x
    // jl M[X]          0b0000 1110         - IF <, caso L = 0 muda PC para endereço x
    // jle M[X]         0b0000 1111         - IF <=, caso L = 0 OU E = 1 muda PC para endereço x
    // jg M[X]          0b0001 0000         - ?????????
    // jge M[X]         0b0001 0001         - ?????????
    // jmp M[X]         0b0001 0010         - Muda PC para posição X
    // ld regX, M[Y]    0b0001 0011         - Carrega registrador X com palavra de Y
    // st regX, M[Y]    0b0001 0100         - Guarda em Y o X
    // movi regX, imm   0b0001 0101         - X = IMM
    // addi regX, imm   0b0001 0110         - X = X + IMM
    // subi regX, imm   0b0001 0111         - X = X - IMM
    // muli regX, imm   0b0001 1000         - X = X . IMM
    // divi regX, imm   0b0001 1001         - X = X ÷ IMM
    // lsh regX, imm    0b0001 1010         - Desloca X em IMM bits a esquerda
    // rsh regX, imm    0b0001 1011         - Desloca X em IMM bits a esquerda


    return 0;
}
