#include <stdio.h>
#include "operation.h"

unsigned char mix_columns_matrix[16] = {
	0x02,0x01,0x01,0x03,0x03,0x02,0x01,0x01,0x01,0x03,0x02,0x01,0x01,0x01,0x03,0x02
};

void xor128(unsigned char * op1, unsigned char * op2, unsigned char * res) {
	for (int i = 0; i < 16; i++) {
		*res = *op1 ^ *op2;
		res++;
		op1++;
		op2++;
	}
}

//以op2为主
unsigned char mul(unsigned char op1, unsigned char op2) {
	unsigned char res=0b00000000;

	if ((0b00000001 & op1) == 0b00000001) {
		res = op2;
	}
	for (int j = 1; j < 8; j++) {
		op1 = op1 >> 1;
		if ((0b00000001 & op1) == 0b00000001) {
			unsigned char tmp = op2;
			for (int i = 0; i < j; i++) {
				if ((0b10000000 & tmp) == 0b10000000) {
					tmp = (tmp << 1) ^ 0b00011011;
				}
				else {
					tmp = (tmp << 1);
				}
			}
			res = res ^ tmp;
		}
	}
	return res;
}

void shift_row(unsigned char op[]) {
	unsigned char tmp = op[1];
	//第二行
	op[1] = op[5];
	op[5] = op[9];
	op[9] = op[13];
	op[13] = tmp;
	//第三行
	tmp = op[2];
	op[2] = op[10];
	op[10] = tmp;
	tmp = op[6];
	op[6] = op[14];
	op[14] = tmp;
	//第四行
	tmp = op[15];
	op[15] = op[11];
	op[11] = op[7];
	op[7] = op[3];
	op[3] = tmp;
}

void mix_columns(unsigned char* op) {
	unsigned char tmp[16];
	for (int i = 0; i < 16; i++) {
		tmp[i] = op[i];
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			unsigned char res=0;
			for (int k = 0; k < 4; k++) {
				res = res ^ mul(mix_columns_matrix[4*k+j], tmp[4*i+k]);
			}
			op[4 * i + j] = res;
		}
	}
}