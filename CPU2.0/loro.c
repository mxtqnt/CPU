#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int mbr, mar = 0, imm, pc = 0, reg[8];
unsigned char ir, ro0, ro1, e, l, g, memoria[154];

void ciclo() {
	
	mar = pc;
	mbr = memoria[mar++];
	mbr = (mbr << 8) | memoria[mar++];
	mbr = (mbr << 8) | memoria[mar++];
	mbr = (mbr << 8) | memoria[mar++];
		
	ir = (mbr >> 24);

	if (ir == 0 || ir == 1) {
		if (ir == 0) {
			//nao fazz nada
		} else if (ir == 1){
			pc += 4;
		}	
	}
	else if (ir >= 2 && ir <= 10){
		ro0 = ((mbr & 0xe00000) >> 21);
		ro1 = ((mbr & 0x1c0000) >> 18);
		if (ir == 2) {
			reg[ro0] = reg[ro0] + reg[ro1];
			pc += 4;
		} else if (ir == 3) {
			reg[ro0] = reg[ro0] - reg[ro1];
			pc += 4;
		} else if (ir == 4) {
			reg[ro0] = reg[ro0] * reg[ro1];
			pc += 4;
		} else if (ir == 5) {
			reg[ro0] = reg[ro0] / reg[ro1];
			pc += 4;
		} else if (ir == 6) {
			if (reg[ro0] == reg[ro1]){
				e = 0x0001;
				pc += 4;
			} else {
				e = 0x0000;
				pc += 4;
			};
			if (reg[ro0] < reg[ro1]){
				l = 0x0001;
				pc += 4;
			} else {
				l = 0x0000;
				pc += 4;
			};
			if (reg[ro0] > reg[ro1]){
				g = 0x0001;
				pc += 4;
			} else {
				g = 0x0000;
				pc += 4;
			};
		} else if (ir == 7) {
			reg[ro0] = reg[ro1];
			pc += 4;
		} else if (ir == 8) {
			reg[ro0] = (reg[ro0] & reg[ro1]);
			pc += 4;
		} else if (ir == 9) {
			reg[ro0] = (reg[ro0] | reg[ro1]);
			pc += 4;
		} else if (ir == 10) {
			reg[ro0] = (reg[ro0] ^ reg[ro1]);
			pc += 4;
		};					
	}
	else if (ir == 11) {
		ro0 = ((mbr & 0xe00000) >> 21);
		reg[ro0] = !reg[ro0];
		pc += 4;
	}
	else if (ir >= 12 && ir <= 18){
		mar = (mbr & 0x1fffff);
		
		if (ir == 12) {
			if (e == 0x01) {
				pc = mar;
			};
		} else if (ir == 13) {
			if (e == 0x00) {
				pc = mar;
			};
		} else if (ir == 14) {
			if (l == 0x01) {
				pc = mar;
			};
		} else if (ir == 15) {
			if (e == 0x01 || l == 0x01) {
				pc = mar;
			};
		} else if (ir == 16) {
			if (g == 0x01) {
				pc = mar;
			};
		} else if (ir == 17) {
			if (e == 0x01 || g == 0x01) {
				pc = mar;
			};
		} else if (ir == 18) {
			pc = mar;
		};	
	}
	else if (ir == 19 || ir == 20) {
		ro0 = ((mbr & 0xe00000) >> 21);
		mar = (mbr & 0x1fffff);

		if (ir == 19) {
			//printf("entrei no segundo \n");
			mbr = memoria[mar++];
			mbr = (mbr << 8) | memoria[mar++];
			mbr = (mbr << 8) | memoria[mar++];
			mbr = (mbr << 8) | memoria[mar++];
			reg[ro0] = mbr;
			pc += 4;
			//printf("%x", reg[ro0], "\n");
		} else if (ir == 20) {
			mbr = reg[ro0];
			memoria[mar++] = (mbr >> 24);
			memoria[mar++] = (mbr >> 16);
			memoria[mar++] = (mbr >> 8);
			memoria[mar++] = mbr;
			pc += 4;
		};

	} else if (ir >= 21 && ir <= 27) {
		ro0 = ((mbr & 0xe00000) >> 21);
		imm = (mbr & 0x1fffff);
		
		if (ir == 21) {
			reg[ro0] = imm;
			pc += 4;
		} else if (ir == 22) {
			reg[ro0] = (reg[ro0] + imm);
			pc += 4;
		} else if (ir == 23) {
			reg[ro0] = (reg[ro0] - imm);
			pc += 4;
		} else if (ir == 24) {
			reg[ro0] = (reg[ro0] * imm);
			pc += 4;
		} else if (ir == 25) {
			reg[ro0] = (reg[ro0] / imm);
			pc += 4;
		} else if (ir == 26) {
			reg[ro0] = (reg[ro0] << imm);
			pc += 4;
		} else if (ir == 27) {
			reg[ro0] = (reg[ro0] >> imm);
			pc += 4;
		};
	};
		
}

unsigned char *pt;

void guardarMemoria(unsigned int mem ,unsigned int aux){
    memoria[mem++] = (aux & 0xff000000) >> 24;
    memoria[mem++] = (aux & 0x00ff0000) >> 16;
    memoria[mem++] = (aux & 0x0000ff00) >> 8;
    memoria[mem] = (aux & 0x0000ff);
}

void colocarInstru(int mem){
    unsigned char *ponteiro, rg0, mine[8]; // aux recebe rg0
    unsigned int count = 0, imediatoMem, palavra;

    ponteiro = strtok(pt," ,");
    while(ponteiro){
        if(count == 0){
            strcpy(mine,ponteiro);
        }
        if (count== 1){
            rg0 = (int)strtol(ponteiro,NULL,16);
        }
        if(count == 2){
            imediatoMem = (int)strtol(ponteiro,NULL,16);
        }
        ponteiro = strtok(NULL," ,r");
        count++;
    }
    if(strcmp(mine,"nop")== 0) {
        palavra = 1;
        palavra = palavra << 24;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"add")== 0){
        palavra = 2;
        palavra = (palavra << 3) |rg0;
        palavra = (palavra << 3) | imediatoMem;
        palavra =  palavra << 18;
        guardarMemoria(mem,palavra);
    } else if(strcmp(mine,"sub")== 0) {
        palavra = 3;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 3) | imediatoMem;
        palavra = palavra << 18;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"mul")== 0) {
        palavra = 4;
        palavra = palavra << 18;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"div")== 0) {
        palavra = 5;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 3) | imediatoMem;
        palavra = palavra << 18;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"cmp")== 0) {
        palavra = 6;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 3) | imediatoMem;
        palavra = palavra << 18;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"movr")== 0) {
        palavra = 7;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 3) | imediatoMem;
        palavra = palavra << 18;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"and")== 0) {
        palavra = 8;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 3) | imediatoMem;
        palavra = palavra << 18;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"or")== 0) {
        palavra = 9;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 3) | imediatoMem;
        palavra = palavra << 18;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"xor")== 0) {
        palavra = 10;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 3) | imediatoMem;
        palavra = palavra << 18;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"not")== 0) {
        palavra = 11;
        palavra = ((palavra << 3)|rg0)<<21;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"je")== 0) {
        palavra = 12;
        palavra = (palavra << 24)| imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"jne")== 0) {
        palavra = 13;
        palavra = (palavra << 24)| imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"jl")== 0) {
        palavra = 14;
        palavra = (palavra << 24)| imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"jle")== 0) {
        palavra = 15;
        palavra = (palavra << 24)| imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"jg")== 0) {
        palavra = 16;
        palavra = (palavra << 24)| imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"jge")== 0) {
        palavra = 17;
        palavra = (palavra << 24)| imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"jmp")== 0) {
        palavra = 18;
        palavra = (palavra << 24)| imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"ld")== 0){
        palavra = 19;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 21)| imediatoMem;
        guardarMemoria(mem,palavra);
    } else if(strcmp(mine,"st")== 0){
        palavra = 20;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 21)| imediatoMem;
        guardarMemoria(mem,palavra);
    } else if(strcmp(mine,"movi")== 0) {
        palavra = 21;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 21) | imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"addi")== 0) {
        palavra = 22;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 21) | imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"subi")== 0) {
        palavra = 23;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 21) | imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"muli")== 0) {
        palavra = 24;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 21) | imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"divi")== 0) {
        palavra = 25;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 21) | imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"lsh")== 0) {
        palavra = 26;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 21) | imediatoMem;
        guardarMemoria(mem, palavra);
    } else if(strcmp(mine,"rsh")== 0) {
        palavra = 27;
        palavra = (palavra << 3) | rg0;
        palavra = (palavra << 21) | imediatoMem;
        guardarMemoria(mem, palavra);
    } else{
        palavra  = 0;
        guardarMemoria(mem,palavra);
    }
}

void lerArquivo(){

    unsigned int mem, valor;
    FILE *arq;
    unsigned char tipo, linha[99];
    unsigned int count = 0;
    arq = fopen("programa.txt", "r");

    while (fgets(linha, 99, arq) != NULL){
        pt = strtok(linha, "; ");
        mem = (int)strtol(pt,NULL,16);
        while(pt){
            if(count == 1){
                tipo = *pt;
            }else if(count == 2){
                if(tipo == 0x64){
                    valor = (int)strtol(pt,NULL,16);
                    memoria[mem++] = (valor & 0xff000000) >> 24;
                    memoria[mem++] = (valor & 0x00ff0000) >> 16;
                    memoria[mem++] = (valor & 0x0000ff00) >> 8;
                    memoria[mem]   = (valor & 0x000000ff);
                }else{
                    colocarInstru(mem);
                }
            }

            pt = strtok(NULL ,";");
            count++;
        }
        count = 0;
    }

    if (NULL == arq)
        printf("Erro ao tentar abrir programa.txt \n");
    fclose(arq);
}

int main (void) {
	
	lerArquivo();
	
	int teste = 0;
	int aux = 0;
	
	while (aux != 3){
		printf(" Aperte 1 para executar, 2 para mostrar a memoria, 3 para finalizar");
		scanf("%d", &aux);
		
		if (aux == 1) {
			ciclo();
			printf("MBR: %x MAR: %x  IMM: %x PC: %x \n",mbr, mar, imm,pc);
			printf("REG1: %x REG2: %x REG3: %x  REG4: %x \n", reg[0], reg[1], reg[2], reg[3]);
			printf("REG5: %x  REG6: %x  REG7: %x  REG8: %x \n", reg[4], reg[5], reg[6], reg[7]);
			printf("IR: %x  RO0: %x  RO1: %x  E: %x  L: %x G: %x \n", ir, ro0, ro1, e, l, g);
			if (ir == 0) {
				while(teste < 154){
					printf("Posicao %d : %x \n", teste, memoria[teste++]);
				};
				break;
			}
		} else if (aux == 2) {
			while(teste < 154){
				printf("Posicao %d : %x \n", teste, memoria[teste]);
				teste++;
			};
		} else {
			break;
		}
	};

	printf("MBR: %x MAR: %x  IMM: %x PC: %x \n",mbr, mar, imm,pc);
	printf("REG1: %x REG2: %x REG3: %x  REG4: %x \n", reg[0], reg[1], reg[2], reg[3]);
	printf("REG5: %x  REG6: %x  REG7: %x  REG8: %x \n", reg[4], reg[5], reg[6], reg[7]);
	printf("IR: %x  RO0: %x  RO1: %x  E: %x  L: %x G: %x \n", ir, ro0, ro1, e, l, g);
	
	return 0;
}