#pragma once
void xor128(unsigned char* op1, unsigned char* op2, unsigned char* res);
unsigned char mul(unsigned char op1, unsigned char op2);
void shift_row(unsigned char op[]);
void mix_columns(unsigned char* op);
