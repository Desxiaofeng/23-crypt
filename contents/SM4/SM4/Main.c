#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include "define.h"

void print_arr(uint32_t* op, int length) {
	printf("\n");
	for (int i = 0; i < length; i++) {
		printf("%X\n", op[i]);
	}
	printf("\n");
}
void test() {
	uint32_t key[4] = {
	0x01234567,0x89abcdef,0xfedcba98,0x76543210
	};
	uint32_t msg[4] = {
	0x01234567,0x89abcdef,0xfedcba98,0x76543210
	};
	uint32_t out[4] = { 0 };
	encrypt(key, msg, out);
	print_arr(out, 4);
}

int main() {
	clock_t start, end;
	start = clock();

	test();

	end = clock();
	double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%.3fs\n", elapsed);
} 
