#include <stdio.h>
#include "KeyExtension.h"
#include "Sbox.h"

unsigned char keys[44][4];
unsigned char RC[10] = {
	0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x1B,0x36
};


void key_extension(unsigned char* key) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			keys[i][j] = key[i * 4 + j];
		}
	}

	int turn = 0;
	for (int i = 4; i < 44; i++) {
		if (i % 4 == 0) {
			keys[i][0] = get_sbox(keys[i - 1][1]) ^ RC[turn++] ^ keys[i-4][0];
			keys[i][1] = get_sbox(keys[i - 1][2]) ^ keys[i - 4][1];
			keys[i][2] = get_sbox(keys[i - 1][3]) ^ keys[i - 4][2];
			keys[i][3] = get_sbox(keys[i - 1][0]) ^ keys[i - 4][3];
		}
		else {
			for (int j = 0; j < 4; j++) {
				keys[i][j] = keys[i - 1][j] ^ keys[i - 4][j];
			}
		}
	}
}