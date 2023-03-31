#include "mbedtls/cipher.h"
#include "mbedtls/dhm.h"
#include "mbedtls/md.h"
#include "test.h"
#include <map>
#include <time.h>

using namespace std;

map<long long, uint8_t *> test;

uint8_t K[1<<24][16];

int p2_len=0;
uint8_t p2[1 << 24][24];

int isEqual(uint8_t * op1, uint8_t * p1) {
    for (int i = 0; i < 8; i++) {
        if (op1[i] != p1[i]) {
            return 0;
         }
    }
    return 1;
    
    
}

void saveK(uint8_t* k2, uint8_t* p1) {
    for (int i = 0; i < 8; i++) {
        p2[p2_len][i] = p1[i + 8];
    }
    for (int i = 8; i < 16; i++) {
        p2[p2_len][i] = k2[i - 8];
    }
    p2_len++;
}



void printfP2(uint8_t * tmp) {
    for (int i = 0; i < 16; i++) {
        if (i < 8) {
            if (i == 0) {
                printf("k1:  ");
            }
            
            printf("%x ", tmp[i]);
        }
        else {
            if (i == 8) {
                printf("k2:  ");
            }
            
            printf("%x ", tmp[i]);
        }
    }
    printf("\n");
}

void printf_1(uint8_t* tmp) {
    printf("\n");
    for (int i = 0; i < 8; i++) {
        if (i == 0) {
            printf("1:  ");
        }
        printf("%x ", tmp[i]);
    }
    printf("\n");
}

int main()
{

    clock_t start, end;
    start = clock();

    uint8_t msg1[8] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };
    uint8_t msg2[8] = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
    uint8_t key1[8] = { 0x00,0x00,0x00,0x12,0x35,0x78,0x9a,0xbd };
    uint8_t key2[8] = { 0x00,0x00,0x00,0x12,0x35,0x78,0x9a,0xbd };
    uint8_t cipher1[8] = { 0xb4,0x43,0x60,0x02,0xf9,0x51,0xee,0xa9 };
    uint8_t cipher2[8] = { 0x63,0x8b,0xab,0xaf,0x73,0x13,0x06,0xe6 };
    //uint8_t cipher2[8] = { 0xa4,0xea,0x00,0x45,0xf1,0xa1,0x32,0xcb };

    /*uint8_t cipher1[8] = { 0xc5,0x13,0x83,0xff,0x56,0xe6,0xf9,0x67 };
    uint8_t cipher2[8] = { 0x10,0x2a,0x3b,0x01,0x27,0x55,0xd7,0xd7 };*/


    //建表
    int cipher_length;
    for (int i = 0; i < (1<<7); i++, key1[0] = key1[0] + 2) {
        for (int j = 0; j < (1 << 7); j++, key1[1] = key1[1] + 2) {
            for (int k = 0; k < (1 << 7); k++, key1[2] = key1[2] + 2) {
                aes_test(MBEDTLS_CIPHER_DES_ECB, key1, 8, msg1, 8, K[i*(1<<14)+j* (1 << 7) +k], &cipher_length, MBEDTLS_ENCRYPT);
                
                for (int l = 8; l < 16; l++) {
                    K[i * (1 << 14) + j * (1 << 7) + k][l] = key1[l - 8];
                }

                //用键值对建表
                pair<map<long long, uint8_t*>::iterator,bool> ret =test.insert(map<long long, uint8_t*>::value_type(*(long long*)K[i * (1 << 14) + j * (1 << 7) + k], K[i * (1 << 14) + j * (1 << 7) + k]));
                if (!ret.second) printf("gg\n");
            }
        }
    }
    
    //找第一轮k1 k2
    uint8_t tmp[8];
    for (int i = 0; i < (1 << 7); i++, key2[0] = key2[0] + 2) {
        printf("%d", i);
        for (int j = 0; j < (1 << 7); j++, key2[1] = key2[1] + 2) {
            for (int k = 0; k < (1 << 7); k++, key2[2] = key2[2] + 2) {
                aes_test(MBEDTLS_CIPHER_DES_ECB, key2, 8, cipher1, 8, tmp, &cipher_length, MBEDTLS_DECRYPT);

                map<long long, uint8_t*>::iterator iter = test.find(*(long long*)tmp);
                if (iter != test.end()) {
                    saveK(key2, iter->second);
                }
            }
        }
    }

    printf("\n");
    printf("%d\n", p2_len);
    printfP2(p2[0]);

    //根据第二对名密文对解出密钥
    for (int i = 0; i < p2_len; i++) {
        aes_test(MBEDTLS_CIPHER_DES_ECB, p2[i], 8, msg2, 8, &p2[i][16], &cipher_length, MBEDTLS_ENCRYPT);
    }

    for (int i = 0; i < p2_len; i++) {
        aes_test(MBEDTLS_CIPHER_DES_ECB, &p2[i][8], 8, cipher2, 8, tmp, &cipher_length, MBEDTLS_DECRYPT);
        if (isEqual(tmp, &p2[i][16])) {
            printfP2(p2[i]);
        }
    }

    end = clock();
    printf("time=%fs", ((double)(end-start))/CLK_TCK);

    /*map<long long, int> test2;
    uint8_t key1[8] = { 0xdc,0x70,0xe2,0x12,0x35,0x78,0x9a,0xbd };
    uint8_t key2[8] = { 0xec,0xdc,0xdc,0x12,0x35,0x78,0x9a,0xbd };
    int cipher_length;
    uint8_t tmp[8];
    uint8_t tmp2[8];

    aes_test(MBEDTLS_CIPHER_DES_ECB, key1, 8, msg2, 8, tmp , &cipher_length, MBEDTLS_ENCRYPT);
    printf_1(tmp);
    printf("%llu", *(long long*)tmp);
    test2.insert(map<long long, int>::value_type(*(long long*)tmp, 1));

    aes_test(MBEDTLS_CIPHER_DES_ECB, key2, 8, tmp, 8, tmp2, &cipher_length, MBEDTLS_ENCRYPT);
    printf_1(tmp2);
    printf("%llu", *(long long*)tmp);
    map<long long, uint8_t*>::iterator iter = test.find(*(long long*)tmp);
    if (iter != test.end()) {
        printf("ok");
    }*/
    return 1;
}

