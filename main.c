#include <stdio.h>

int soma(int primeiroregistrador, int segundoregistrador){
    int resultadosoma;
    primeiroregistrador = primeiroregistrador + segundoregistrador;
    return(resultadosoma);
};

int main(void) {

    unsigned int mbr, mar, imm, pc;
    unsigned int reg[8];
    unsigned char ir, ro0, ro1, e, l, g, memoria[154];

    //Memória falsa
    memoria[0] = 0x13;
    memoria[1] = 0x0;
    memoria[2] = 0x0;
    memoria[3] = 0x1E;

    memoria[4] = 0x13;
    memoria[5] = 0x20;
    memoria[6] = 0x0;
    memoria[7] = 0x24;

    memoria[8] = 0x2;
    memoria[9] = 0x4;
    memoria[10] = 0x0; //??????????
    memoria[11] = 0x0;

    memoria[12] = 0x0;
    memoria[13] = 0x0;
    memoria[14] = 0x0;
    memoria[15] = 0x0;

    memoria[16] = 0x0;
    memoria[17] = 0x0;
    memoria[18] = 0x0;
    memoria[19] = 0x0;



    //Instruções
    int hlt     = 00000000,
        nop     = 00000001;

    int add     = 00000010,
        sub     = 00000011,
        mul     = 00000100,
        div     = 00000101,
        cmp     = 00000110,
        movr    = 00000111,
        and     = 00001000,
        or      = 00001001,
        xor     = 00001010;

    int not     = 00001011;


    //0000 0000     000     000
    //Opcode        Reg0    Reg1

    pc = 0x0;

    //Depois da leitura





    if (ir == hlt) {
        //Não faz nada
    };

    if (ir == nop) {
        pc = pc + 1;
    };

    if (ir == add) {
        //Soma dois registradores
        primeiroregistrador = soma(primeiroregistrador, segundoregistrador);
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
