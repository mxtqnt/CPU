#include <stdio.h>

unsigned char memoria[154];
unsigned int mbr, mar, imm, pc;
unsigned int reg[8];
unsigned char ir, ro0, ro1, e, l, g;

//Instruções
int hlt     = 00000000,
    nop     = 00000001,
    add     = 00000010,
    sub     = 00000011,
    mul     = 00000100,
    div     = 00000101,
    cmp     = 00000110,
    movr    = 00000111,
    and     = 00001000,
    or      = 00001001,
    xor     = 00001010,
    not     = 00001011;

int main(void) {
    pc = 0x0;

    if (ir == hlt) {
        //Não faz nada
    };

    if (ir == nop) {

    };

    if (ir == add) {

    };

    if (ir == sub) {

    };

    if (ir == mul) {

    };

    if (ir == div) {

    };

    if (ir == cmp) {

    };

    if (ir == movr) {

    };
    if (ir == and) {

    };

    if (ir == or) {

    };

    if (ir == xor) {

    };

    if (ir == not) {

    };

    return 0;
}
