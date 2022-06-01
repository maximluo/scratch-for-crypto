#pragma once

#include "util.h"

#define SM4_NUM_ROUNDS 32
#define SM4_CIPHER_KEY_LENGTH 16
#define SM4_BLOCK_SIZE 16
#define SM4_ARRAY_SIZE 4 // SM4 works under the 128 bit input data block and 128 bit cipher key 

class SM4 
{
public:
    SM4();
    ~SM4();

    /**
     * Set cipher or de-cipher key
     * @param userKey A 128 bit cipher or de-cipher key with big endian
     * @param keyLength Key's length in bytes
     */
    void UncheckedSetKey(const byte *userKey, unsigned int keyLength);

    /**
     * Encrypt data
     * @param inBlock Input data block with big endian
     * @param blockSize The size of input data block in bytes
     */
    void Encrypt(const byte *inBlock, unsigned int blockSize);

    void Decrypt();

private:
    /**
     * Convert big endian data to little endian data
     * @param data Input big endian data
     * @param size Data size in bytes
     */
    void ConvertBigEndianToLittleEndian(const byte* data, unsigned int size);

    word32 SM4_G(word32 x);
    word32 SM4_H(word32 x);
    word32 SM4_F(word32 x);

    void SM4_Round(word32* data, const word32* rkeys, unsigned int round, bool bEncrypt);

    word32 m_rKeys[SM4_NUM_ROUNDS];

    word32 m_wSpace[SM4_ARRAY_SIZE];
};