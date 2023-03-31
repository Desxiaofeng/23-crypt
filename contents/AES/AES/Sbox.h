#pragma once
#include <stdio.h>
unsigned char sbox[16][16];
unsigned char isbox[16][16];
unsigned char get_sbox(unsigned char pos);
unsigned char get_i_sbox(unsigned char pos);
void substitute(unsigned char* op);
