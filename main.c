#include <stdio.h>

unsigned int busca(unsigned int pc, char memoria[], unsigned char ir, unsigned int mbr) {
    //Carregar mbr - buscar instrução -
    mbr = memoria[pc++] << 8;
    mbr = (mbr | memoria[pc++]) << 8;
    mbr = (mbr | memoria[pc++]) << 8;
    mbr = mbr | memoria[pc++];

    return(mbr);
};

unsigned int opcode(unsigned int mbr){
    unsigned char ir;
    ir = (mbr) >> 24;
    return(ir);
};

unsigned int mbr = 0, mar, imm, pc = 0;
unsigned int reg[8], nreg[8];
unsigned char ir, ro0, ro1, e, l, g;
char memoria[154];

int main(void) {
    //Instruções
    int hlt     = 0x0,
        nop     = 0x1,
        add     = 0x2,
        sub     = 0x3,
        mul     = 0x4,
        div     = 0x5,
        cmp     = 0x6,
        movr    = 0x7,
        and     = 0x8,
        or      = 0x9,
        xor     = 0xA,
        not     = 0xB,
        je      = 0xC,
        jne     = 0xD,
        jl      = 0xE,
        jle     = 0xF,
        jg      = 0x10,
        jge     = 0x11,
        jmp     = 0x12,
        ld      = 0x13,
        st      = 0x14,
        movi    = 0x15,
        addi    = 0x16,
        subi    = 0x17,
        muli    = 0x18,
        divi    = 0x19,
        lsh     = 0x1A,
        rsh     = 0x1B;

    nreg[0] = 0;
    nreg[1] = 1;
    nreg[2] = 10;
    nreg[3] = 11;
    nreg[4] = 100;
    nreg[5] = 101;
    nreg[6] = 110;
    nreg[7] = 111;

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

    memoria[8] = 0x14;
    memoria[9] = 0x0;
    memoria[10] = 0x0;
    memoria[11] = 0x12;

    memoria[12] = 0x2;
    memoria[13] = 0x4;
    memoria[14] = 0x0;
    memoria[15] = 0x0;

    // 0000 0011 0000 0100 0000 0000 0000 0000
    // 0    3    0    4    0    0    0    0
    memoria[16] = 0x3;
    memoria[17] = 0x4;
    memoria[18] = 0x0;
    memoria[19] = 0x0;

    // 0000 0100 0000 0100 0000 0000 0000 0000
    // 0    4    0    4    0    0    0    0
    memoria[20] = 0x4;
    memoria[21] = 0x4;
    memoria[22] = 0x0;
    memoria[23] = 0x0;

    // 0000 0101 0000 0100 0000 0000 0000 0000
    // 0    5    0    4    0    0    0    0
    memoria[24] = 0x5;
    memoria[25] = 0x4;
    memoria[26] = 0x0;
    memoria[27] = 0x0;

    memoria[30] = 0x15;
    memoria[36] = 0x8;

    retorno:
    mbr = busca(pc, memoria, ir, mbr);
    ir  = opcode(mbr);

    printf("MBR = %08x\n", mbr);
    printf("IR = %08x\n", ir);

    //achar instrução
    if (ir == hlt) {
        pc = 154;
    };
    if (ir == nop) {
        pc += 4;
    };
    if (ir == add) {
        printf("Início instrução ADD\n");
        int primeiroregistrador     = (mbr & 0x00e00000) >> 21;
        int segundoregistrador      = (mbr & 0x001c0000) >> 18;

        if (primeiroregistrador == nreg[0]){ primeiroregistrador = reg[0]; };
        if (primeiroregistrador == nreg[1]){ primeiroregistrador = reg[1]; };
        if (primeiroregistrador == nreg[2]){ primeiroregistrador = reg[2]; };
        if (primeiroregistrador == nreg[3]){ primeiroregistrador = reg[3]; };
        if (primeiroregistrador == nreg[4]){ primeiroregistrador = reg[4]; };
        if (primeiroregistrador == nreg[5]){ primeiroregistrador = reg[5]; };
        if (primeiroregistrador == nreg[6]){ primeiroregistrador = reg[6]; };
        if (primeiroregistrador == nreg[7]){ primeiroregistrador = reg[7]; };

        if (segundoregistrador == nreg[0]){ segundoregistrador = reg[0]; primeiroregistrador = primeiroregistrador + segundoregistrador; };
        if (segundoregistrador == nreg[1]){ segundoregistrador = reg[1]; primeiroregistrador = primeiroregistrador + segundoregistrador; };
        if (segundoregistrador == nreg[2]){ segundoregistrador = reg[2]; primeiroregistrador = primeiroregistrador + segundoregistrador; };
        if (segundoregistrador == nreg[3]){ segundoregistrador = reg[3]; primeiroregistrador = primeiroregistrador + segundoregistrador; };
        if (segundoregistrador == nreg[4]){ segundoregistrador = reg[4]; primeiroregistrador = primeiroregistrador + segundoregistrador; };
        if (segundoregistrador == nreg[5]){ segundoregistrador = reg[5]; primeiroregistrador = primeiroregistrador + segundoregistrador; };
        if (segundoregistrador == nreg[6]){ segundoregistrador = reg[6]; primeiroregistrador = primeiroregistrador + segundoregistrador; };
        if (segundoregistrador == nreg[7]){ segundoregistrador = reg[7]; primeiroregistrador = primeiroregistrador + segundoregistrador; };

        printf("Soma %0x\n", primeiroregistrador);

        pc += 4;
        printf("PC = %d\n", pc);
        goto retorno;
    };

    if (ir == sub) {
        printf("sub começa\n");
        int primeiroregistrador     = (mbr & 0x00e00000) >> 21;
        int segundoregistrador      = (mbr & 0x001c0000) >> 18;

        if (primeiroregistrador == nreg[0]){ primeiroregistrador = reg[0]; };
        if (primeiroregistrador == nreg[1]){ primeiroregistrador = reg[1]; };
        if (primeiroregistrador == nreg[2]){ primeiroregistrador = reg[2]; };
        if (primeiroregistrador == nreg[3]){ primeiroregistrador = reg[3]; };
        if (primeiroregistrador == nreg[4]){ primeiroregistrador = reg[4]; };
        if (primeiroregistrador == nreg[5]){ primeiroregistrador = reg[5]; };
        if (primeiroregistrador == nreg[6]){ primeiroregistrador = reg[6]; };
        if (primeiroregistrador == nreg[7]){ primeiroregistrador = reg[7]; };

        if (segundoregistrador == nreg[0]){ segundoregistrador = reg[0]; primeiroregistrador = primeiroregistrador - segundoregistrador; };
        if (segundoregistrador == nreg[1]){ segundoregistrador = reg[1]; primeiroregistrador = primeiroregistrador - segundoregistrador; };
        if (segundoregistrador == nreg[2]){ segundoregistrador = reg[2]; primeiroregistrador = primeiroregistrador - segundoregistrador; };
        if (segundoregistrador == nreg[3]){ segundoregistrador = reg[3]; primeiroregistrador = primeiroregistrador - segundoregistrador; };
        if (segundoregistrador == nreg[4]){ segundoregistrador = reg[4]; primeiroregistrador = primeiroregistrador - segundoregistrador; };
        if (segundoregistrador == nreg[5]){ segundoregistrador = reg[5]; primeiroregistrador = primeiroregistrador - segundoregistrador; };
        if (segundoregistrador == nreg[6]){ segundoregistrador = reg[6]; primeiroregistrador = primeiroregistrador - segundoregistrador; };
        if (segundoregistrador == nreg[7]){ segundoregistrador = reg[7]; primeiroregistrador = primeiroregistrador - segundoregistrador; };

        printf("Subtração = %0x\n", primeiroregistrador);

        pc += 4;
        printf("PC = %d\n", pc);
        goto retorno;
    };
    if (ir == mul) {
        printf("Começa multiplicação\n");
        reg[0] = 0x14;
        reg[1] = 0x2;
        int primeiroregistrador     = (mbr & 0x00e00000) >> 21;
        int segundoregistrador      = (mbr & 0x001c0000) >> 18;

        if (primeiroregistrador == nreg[0]){ primeiroregistrador = reg[0]; };
        if (primeiroregistrador == nreg[1]){ primeiroregistrador = reg[1]; };
        if (primeiroregistrador == nreg[2]){ primeiroregistrador = reg[2]; };
        if (primeiroregistrador == nreg[3]){ primeiroregistrador = reg[3]; };
        if (primeiroregistrador == nreg[4]){ primeiroregistrador = reg[4]; };
        if (primeiroregistrador == nreg[5]){ primeiroregistrador = reg[5]; };
        if (primeiroregistrador == nreg[6]){ primeiroregistrador = reg[6]; };
        if (primeiroregistrador == nreg[7]){ primeiroregistrador = reg[7]; };

        if (segundoregistrador == nreg[0]){ segundoregistrador = reg[0]; primeiroregistrador = primeiroregistrador * segundoregistrador; };
        if (segundoregistrador == nreg[1]){ segundoregistrador = reg[1]; primeiroregistrador = primeiroregistrador * segundoregistrador; };
        if (segundoregistrador == nreg[2]){ segundoregistrador = reg[2]; primeiroregistrador = primeiroregistrador * segundoregistrador; };
        if (segundoregistrador == nreg[3]){ segundoregistrador = reg[3]; primeiroregistrador = primeiroregistrador * segundoregistrador; };
        if (segundoregistrador == nreg[4]){ segundoregistrador = reg[4]; primeiroregistrador = primeiroregistrador * segundoregistrador; };
        if (segundoregistrador == nreg[5]){ segundoregistrador = reg[5]; primeiroregistrador = primeiroregistrador * segundoregistrador; };
        if (segundoregistrador == nreg[6]){ segundoregistrador = reg[6]; primeiroregistrador = primeiroregistrador * segundoregistrador; };
        if (segundoregistrador == nreg[7]){ segundoregistrador = reg[7]; primeiroregistrador = primeiroregistrador * segundoregistrador; };

        printf("Multiplicação = %0x\n", primeiroregistrador);

        pc += 4;
        printf("PC = %d\n", pc);
        goto retorno;
    };
    if (ir == div) {
        printf("Início instrução DIV\n");
        int primeiroregistrador     = (mbr & 0x00e00000) >> 21;
        int segundoregistrador      = (mbr & 0x001c0000) >> 18;

        if (primeiroregistrador == nreg[0]){ primeiroregistrador = reg[0]; };
        if (primeiroregistrador == nreg[1]){ primeiroregistrador = reg[1]; };
        if (primeiroregistrador == nreg[2]){ primeiroregistrador = reg[2]; };
        if (primeiroregistrador == nreg[3]){ primeiroregistrador = reg[3]; };
        if (primeiroregistrador == nreg[4]){ primeiroregistrador = reg[4]; };
        if (primeiroregistrador == nreg[5]){ primeiroregistrador = reg[5]; };
        if (primeiroregistrador == nreg[6]){ primeiroregistrador = reg[6]; };
        if (primeiroregistrador == nreg[7]){ primeiroregistrador = reg[7]; };

        if (segundoregistrador == nreg[0]){ segundoregistrador = reg[0]; primeiroregistrador = primeiroregistrador / segundoregistrador; };
        if (segundoregistrador == nreg[1]){ segundoregistrador = reg[1]; primeiroregistrador = primeiroregistrador / segundoregistrador; };
        if (segundoregistrador == nreg[2]){ segundoregistrador = reg[2]; primeiroregistrador = primeiroregistrador / segundoregistrador; };
        if (segundoregistrador == nreg[3]){ segundoregistrador = reg[3]; primeiroregistrador = primeiroregistrador / segundoregistrador; };
        if (segundoregistrador == nreg[4]){ segundoregistrador = reg[4]; primeiroregistrador = primeiroregistrador / segundoregistrador; };
        if (segundoregistrador == nreg[5]){ segundoregistrador = reg[5]; primeiroregistrador = primeiroregistrador / segundoregistrador; };
        if (segundoregistrador == nreg[6]){ segundoregistrador = reg[6]; primeiroregistrador = primeiroregistrador / segundoregistrador; };
        if (segundoregistrador == nreg[7]){ segundoregistrador = reg[7]; primeiroregistrador = primeiroregistrador / segundoregistrador; };

        printf("Divisão %0x\n", primeiroregistrador);

        pc += 4;
        printf("PC = %d\n", pc);
        goto retorno;
    };
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

    if (ir == ld) {
        int posicao = (mbr & 0x001fffff);
        //0000 0000 1110 0000 0000 0000
        int tmp     = (mbr & 0x00e00000) >> 21;

        if (tmp == nreg[0]){ reg[0] = memoria[posicao]; };
        if (tmp == nreg[1]){ reg[1] = memoria[posicao]; };
        if (tmp == nreg[2]){ reg[2] = memoria[posicao]; };
        if (tmp == nreg[3]){ reg[3] = memoria[posicao]; };
        if (tmp == nreg[4]){ reg[4] = memoria[posicao]; };
        if (tmp == nreg[5]){ reg[5] = memoria[posicao]; };
        if (tmp == nreg[6]){ reg[6] = memoria[posicao]; };
        if (tmp == nreg[7]){ reg[7] = memoria[posicao]; };

        printf("Conteúdo reg[0] = %x\n", reg[0]);
        printf("Conteúdo reg[1] = %x\n", reg[1]);
        printf("Conteúdo reg[2] = %x\n", reg[2]);
        printf("Conteúdo reg[3] = %x\n", reg[3]);
        printf("Conteúdo reg[4] = %x\n", reg[4]);
        printf("Conteúdo reg[5] = %x\n", reg[5]);
        printf("Conteúdo reg[6] = %x\n", reg[6]);
        printf("Conteúdo reg[7] = %x\n", reg[7]);

        pc += 4;
        printf("PC = %d\n", pc);
        goto retorno;
    };

    if (ir == st) {
        int endereco = (mbr & 0x001fffff);
        int tmp     = (mbr & 0x00e00000) >> 21;

        if (tmp == nreg[0]){ memoria[endereco] = reg[0]; };

        printf("Memoria alterada = %x\n", memoria[endereco]);

        printf("Conteúdo reg[0] = %x\n", reg[0]);
        printf("Conteúdo reg[1] = %x\n", reg[1]);
        printf("Conteúdo reg[2] = %x\n", reg[2]);
        printf("Conteúdo reg[3] = %x\n", reg[3]);
        printf("Conteúdo reg[4] = %x\n", reg[4]);
        printf("Conteúdo reg[5] = %x\n", reg[5]);
        printf("Conteúdo reg[6] = %x\n", reg[6]);
        printf("Conteúdo reg[7] = %x\n", reg[7]);

        pc += 4;
        printf("PC = %d\n", pc);

        goto retorno;
    };
    if (ir == movi) {};
    if (ir == addi) {};
    if (ir == subi ) {};
    if (ir == muli ) {};
    if (ir == divi ) {};
    if (ir == lsh ) {};
    if (ir == rsh) {};

    return 0;
}
