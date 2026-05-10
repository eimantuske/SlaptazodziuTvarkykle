#ifndef _AES_HPP_
#define _AES_HPP_

#define CBC 1
#define AES256 1
#define AES_BLOCKLEN 16

#include <stdint.h>
#include <stddef.h>

struct AES_ctx {
    uint8_t RoundKey[240];
    uint8_t Iv[16];
};

// BŪTINA ŠI DALIS:
#ifdef __cplusplus
extern "C" {
#endif

    void AES_init_ctx_iv(struct AES_ctx* ctx, const uint8_t* key, const uint8_t* iv);
    void AES_CBC_encrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, size_t length);
    void AES_CBC_decrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, size_t length);

#ifdef __cplusplus
}
#endif

#endif