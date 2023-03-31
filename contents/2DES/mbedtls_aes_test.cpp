/**
 * @brief   AES Function demo
 * @author  mculover666
 * @date    2020/09/23
*/

#if !defined(MBEDTLS_CONFIG_FILE)
//#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

//#if defined(MBEDTLS_CIPHER_C)

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "mbedtls/cipher.h"

/* Intialization Vector */
uint8_t iv[16] = {
        0x8f,0x99,0x97,0x2d,0x35,0x60,0x45,0x58,
        0xd7,0x31,0xfc,0xdc,0x67,0x6a,0x6a,0x57
};

static void dump_buf(uint8_t *buf, uint32_t len)
{
    int i;
    
    printf("buf:");
    
    for (i = 0; i < len; i++) {
        printf("%s%02X%s", i % 16 == 0 ? "\r\n\t" : " ", 
                           buf[i], 
                           i == len - 1 ? "\r\n" : "");
    }
}

int aes_test(mbedtls_cipher_type_t cipher_type, uint8_t * key , int key_length , uint8_t * msg , int msg_length , uint8_t * cipher , int * cipher_length, const mbedtls_operation_t operation) //可选对称密码算法
{
    int ret;
    size_t len;
    int olen = 0;
    uint8_t output_buf[8];
    
    mbedtls_cipher_context_t ctx;
    const mbedtls_cipher_info_t *info;
    
    /* 1. init cipher structuer */
    mbedtls_cipher_init(&ctx);
    
    /* 2. get info structuer from type */
    info = mbedtls_cipher_info_from_type(cipher_type);
    
    /* 3. setup cipher structuer */
    ret = mbedtls_cipher_setup(&ctx, info);
    if (ret != 0) {
        goto exit;
    }
    /* 4. set key */
    ret = mbedtls_cipher_setkey(&ctx, key, 8*key_length, operation);
    if (ret != 0) {
        goto exit;
    }
    /* 5. set iv */
    ret = mbedtls_cipher_set_iv(&ctx, iv, sizeof(iv));
    if (ret != 0) {
        goto exit;
    }

    /* 6. update cipher */
    ret = mbedtls_cipher_update(&ctx, msg, msg_length, output_buf, &len);
    if (ret != 0) {
        goto exit;
    }
    olen += len;
    
    /* 7. finish cipher */
    ret = mbedtls_cipher_finish(&ctx, output_buf, &len);
    if (ret != 0) {
        goto exit;
    }
    olen += len;
    
    for (int i = 0; i < 8; i++) {
        cipher[i] = output_buf[i];
    }
    //printf("cipher name: %s block size is: %d\r\n", mbedtls_cipher_get_name(&ctx), mbedtls_cipher_get_block_size(&ctx));
    //dump_buf(output_buf, olen);
    
    exit:
    /* 8. free cipher structure */
    mbedtls_cipher_free(&ctx);
    return ret;
}
