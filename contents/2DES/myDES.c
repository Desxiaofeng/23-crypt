#include "mbedtls/des.h"
#include <stdio.h>

uint8_t my_key[8] = {
		0x12,0x34,0x56,0x78,0x9a,0xab,0xbc,0xcd
};

int checkAndChangeMsgLength(int length, const char msg[], char input[]) {
	if (length > 8) {
		for (int i = 0; i < 8; i++) {
			input[i] = msg[i];
		}
		printf("your msg is too long, skip the bit larger than 64");
	}
	else if (length < 8) {
		for (int i = 0; i < 8; i++) {
			if (i < length) {
				input[i] = msg[i];
			}
			else {
				input[i] = 0;
			}
		}
		printf("your msg is too short, fill the bit larger than or equal length with 0");
	}
	printf("\n");
	return;
}

static void my_printf(uint8_t* buf, uint32_t len)
{
	int i;

	printf("buf:");

	for (i = 0; i < len; i++) {
		printf("%s%02X%s", i % 16 == 0 ? "\r\n\t" : " ",
			buf[i],
			i == len - 1 ? "\r\n" : "");
	}
}

int myDes() {
	
	mbedtls_des_context ctx;
	mbedtls_des_init(&ctx);

	int ret;
	const char msg[] = "202100460140";
	char input[8];
	char output[8];
	char output2[8];
	
	//修改msg,以满足要求....
	checkAndChangeMsgLength(sizeof(msg), msg, input);
	mbedtls_des_key_set_parity(my_key);

	//打印原始输入
	my_printf(input,8);

	//开始加密步骤
	ret=mbedtls_des_setkey_enc(&ctx, my_key);
	if (ret != 0) {
		goto exit;
	}

	ret=mbedtls_des_crypt_ecb(&ctx, input, output);
	if (ret != 0) {
		goto exit;
	}
	//加密完毕，打印
	my_printf(output,8);

	//开始解密步骤
	ret=mbedtls_des_setkey_dec(&ctx, my_key);
	if (ret != 0) {
		goto exit;
	}

	ret = mbedtls_des_crypt_ecb(&ctx, output, output2);
	if (ret != 0) {
		goto exit;
	}
	//解密完成，加印
	my_printf(output2, 8);

	exit:
	return;


}