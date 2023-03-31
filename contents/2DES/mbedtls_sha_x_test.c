/**
 * @brief   SHAX Function demo
 * @author  mculover666
 * @date    2020/09/22
*/

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

//#if defined(MBEDTLS_MD_C)

#include <stdio.h>
#include "string.h"
#include "mbedtls/md.h"

int mbedtls_shax_test(mbedtls_md_type_t md_type)
{
    int len, i;
    int ret;
    const char *message = "02909F793E6255A1932002848BE1C7EFB25F97542114EDB6109D781AC44F9D84B8FD91DCCFDF713E42CB83242764E4C6C8C24EF856A7374A6F2770932FA6D3D0830780E114F80F4B759FD89F351EA7F75D5C88FCB23E37EA9A1EACB6C45AF94CE2F573CD4EF6C7CD67EC19774DD84AB5D5595220270B80DB1D4AA83A90047CD1C273F76B363DE08EBA884C1A3B6DDF9DA309DDA1E8D3B022B917D0CC5907ECD6E301B5DDF42999627732F9009B20BCD5EF1853D160AE8E66C2BBDFD9A4FEAC1B816A69592D3EABABDD8058445EB7DD440D4AA7EA02E2CCAF1607C6C722A7F71A8CF81299AF6409A2ACDE1A8B37ECADCFA4032A6E43AE4D4AEFA1EF6B084C6335";
    unsigned char digest[32];
    
    mbedtls_md_context_t ctx;
    const mbedtls_md_info_t *info;

    printf("message is:%s\r\n", message);

    /* 1. init mbedtls_md_context_t structure */
    mbedtls_md_init(&ctx);
    
    /* 2. get md info structure pointer */
    info = mbedtls_md_info_from_type(md_type);
    
    /* 3. setup md info structure */
    ret = mbedtls_md_setup(&ctx, info, 0);
    if (ret != 0) {
        goto exit;
    }
    
    /* 4. start */
    ret = mbedtls_md_starts(&ctx);
     if (ret != 0) {
        goto exit;
    }
     
    /* 5. update */
    ret = mbedtls_md_update(&ctx, (unsigned char *)message, strlen(message));
    if (ret != 0) {
        goto exit;
    }
     
    /* 6. finish */
    ret = mbedtls_md_finish(&ctx, digest);
    if (ret != 0) {
        goto exit;
    }
    
    /* show */
    printf("%s digest context is:[", mbedtls_md_get_name(info));
    len= mbedtls_md_get_size(info);
    for (i = 0; i < len; i++) {
      printf("%02x", digest[i]);
    }
    printf("]\r\n");

    exit:
    /* 7. free */
    mbedtls_md_free(&ctx);
    
    return ret;
}
/*
int main()
{
    mbedtls_shax_test(MBEDTLS_MD_SHA512);
    return 1;
}*/

//#endif /* MBEDTLS_MD_C */
