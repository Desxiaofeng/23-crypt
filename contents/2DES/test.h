#pragma once
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "mbedtls/cipher.h"


int aes_test(mbedtls_cipher_type_t cipher_type, uint8_t* key, int key_length, uint8_t* msg, int msg_length, uint8_t* cipher, int* cipher_length, const mbedtls_operation_t operation);