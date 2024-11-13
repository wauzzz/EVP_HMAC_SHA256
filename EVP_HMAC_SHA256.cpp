#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>


int EVP_HMAC_SHA256(const char *key, const char *msg, unsigned char *retmsg) {
    EVP_MAC *mac = EVP_MAC_fetch(NULL, "HMAC", NULL);
    const char *digest = "SHA256";
    EVP_MAC_CTX *ctx = NULL;
    unsigned char buf[4096];
    strcpy((char*)buf, msg);
    size_t read_l = strlen((char*)buf);
    size_t final_l;
    size_t i;
    OSSL_PARAM params[2];
    params[0] =
        OSSL_PARAM_construct_utf8_string("digest", (char*)"SHA256", 0);
    params[1] = OSSL_PARAM_construct_end();

    if (mac == NULL
        || key == NULL
        || (ctx = EVP_MAC_CTX_new(mac)) == NULL
        || !EVP_MAC_init(ctx, (const unsigned char *)key, strlen(key),
                         params))
        goto err;

    if (!EVP_MAC_update(ctx, buf, read_l)) goto err;
    if (!EVP_MAC_final(ctx, buf, &final_l, sizeof(buf))) goto err;
    for (i = 0; i < final_l; i++)
        sprintf((char*)retmsg + i*2, "%02x", buf[i]);
    EVP_MAC_CTX_free(ctx);
    EVP_MAC_free(mac);
    return 0;

 err:
    EVP_MAC_CTX_free(ctx);
    EVP_MAC_free(mac);
    fprintf(stderr, "Something went wrong\n");
    ERR_print_errors_fp(stderr);
    exit (1);
}
