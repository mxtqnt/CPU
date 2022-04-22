#include <stdio.h>

int soma(int primeiroregistrador, int segundoregistrador){
    int resultadosoma;
    primeiroregistrador = primeiroregistrador + segundoregistrador;
    return(resultadosoma);
};

unsigned int mbr = 0, mar, imm, pc = 0;
unsigned int reg[8];
unsigned char ir, ro0, ro1, e, l, g;
char memoria[154];

int main(void) {
    //Instruções
    int hlt     = 00000000, //  |___________|____________________________|
        nop     = 00000001; //  0           7                           31

    int add     = 00000010,
        sub     = 00000011,
        mul     = 00000100,
        div     = 00000101, //  |___________|_____|______|_______________|
        cmp     = 00000110, //  0           7     10     13              31
        movr    = 00000111,
        and     = 00001000,
        or      = 00001001,
        xor     = 00001010;

    int not     = 00001011; //  |___________|_____|______________________|
                            //  0           7     10                     31
    int je      = 00001100,
        jne     = 00001101,
        jl      = 00001110,
        jle     = 00001111, //  |___________|_____|______|_______________|
        jg      = 00010000, //  0           7     10                     31
        jge     = 00010001,
        jmp     = 00010010;


    int ld      = 00010011,
        st      = 00010100,
        movi    = 00010101,
        addi    = 00010110,
        subi    = 00010111,
        muli    = 00011000,
        divi    = 00011001,
        lsh     = 00011010,
        rsh     = 00011011;



    reg[0] = 000;
    reg[1] = 001;
    reg[2] = 010;
    reg[3] = 011;
    reg[4] = 100;
    reg[5] = 101;
    reg[6] = 110;
    reg[7] = 111;

    pc = 0;

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

    memoria[12] = 0x16;
    memoria[13] = 0x0;
    memoria[14] = 0x0;
    memoria[15] = 0x14;

    //Carregar mbr buscar instrução -
    mbr = memoria[pc++] << 8;  //0
    // mbr 0000 0000 0000 0000 0000 0000 0001 0011
    // mbr 0000 0000 0000 0000 0001 0011 0000 0000
    //     00001300

    mbr = (mbr | memoria[pc++]) << 8;   //1
    // mbr      0000 0000 0000 0000 0001 0011 0000 0000 0r
    // memoria  0000 0000 0000 0000 0000 0000 0000 0000
    //          0000 0000 0000 0000 0001 0011 0000 0000
    //          0000 0000 0001 0011 0000 0000 0000 0000
    //          00130000

    mbr = (mbr | memoria[pc++]) << 8;   //1
    // mbr      0000 0000 0001 0011 0000 0000 0000 0000 0r
    // memoria  0000 0000 0000 0000 0000 0000 0000 0000
    //          0000 0000 0001 0011 0000 0000 0000 0000
    //          0001 0011 0000 0000 0000 0000 0000 0000
    //          13000000

    mbr = mbr | memoria[pc++];   //1
    // mbr      0001 0011 0000 0000 0000 0000 0000 0000 0r
    // memoria  0000 0000 0000 0000 0000 0000 0001 1110
    //          0001 0011 0000 0000 0000 0000 0001 1110
    //          1300001e

    // Pegar o Opcode da instrução dentro do mbr
    ir = (mbr) >> 24;

    //achar instrução
    if (ir == hlt) {};
    if (ir == nop) {};
    if (ir == add) {};
    if (ir == sub) {};
    if (ir == mul) {};
    if (ir == div) {};
    if (ir == cmp) {};
    if (ir == movr) {};
    if (ir == and) {};
    if (ir == or) {};
    if (ir == xor) {};
    if (ir == not) {};
    if (ir == je ) {};
    if (ir == jne ) {};
    if (ir == jl ) {};
    if (ir == jle ) {};
    if (ir == jg) {};
    if (ir == jge) {};
    if (ir == jmp) {};
    if (ir == ld) {};
    if (ir == st) {};
    if (ir == movi) {};
    if (ir == addi) {};
    if (ir == subi ) {};
    if (ir == muli ) {};
    if (ir == divi ) {};
    if (ir == lsh ) {};
    if (ir == rsh) {};

    printf("MBR = %08x\n", mbr);
    printf("IR = %08x", ir);

    return 0;
}
