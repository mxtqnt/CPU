#include <stdio.h>

int main(void) {
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

    return 0;
}