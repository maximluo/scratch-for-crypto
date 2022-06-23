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
    void UncheckedSetKey(const byte* mainKey, unsigned int keyLength);

    /**
     * Encrypt data
     * @param inBlock Input data block with big endian
     * @param inBlockSize The size of input data block in bytes
     * @param outBlock Output data block with big endian
     * @param outBlockSize The size of output data block in bytes
     */
    void Encrypt(const byte *inBlock, unsigned int inBlockSize, byte* outBlock, unsigned int outBlockSize);

    /**
     * Encrypt data
     * @param inBlock Input data block with big endian
     * @param inBlockSize The size of input data block in bytes
     * @param outBlock Output data block with big endian
     * @param outBlockSize The size of output data block in bytes
     */
    void Decrypt(const byte* inBlock, unsigned int inBlockSize, byte* outBlock, unsigned int outBlockSize);

private:
    /**
     * Convert big endian data to little endian data
     * @param data Input big endian data
     * @param size Data size in bytes
     */
    void ConvertBigEndianToLittleEndian(const byte* data, unsigned int size);

    /**
     * Convert little endian data to big endian data
     * @param data Output big endian data
     * @param size Data size in bytes
     */
    void ConvertLittleEndianToBigEndian(byte* data, unsigned int size);

    /**
     * The transform T'(x) for round keys
     * @param x Result from SM4_H
     */
    word32 SM4_G(word32 x);

    /*
     * The nonlinear transform B(x) with S box
     */
    word32 SM4_H(word32 x);

    /*
     * The transform T(x) for encrypt/decrypt
     */
    word32 SM4_F(word32 x);

    /**
     * 32 rounds encryption or decryption
     * @param data Plain data or encrypted data
     * @param rkeys Round keys
     * @param round Started round's number
     * @param bEncrypt If it's true for encryption, false for decryption
     */
    void SM4_Round(word32* data, const word32* rkeys, unsigned int round, bool bEncrypt);

    word32 m_rKeys[SM4_NUM_ROUNDS];

    word32 m_wSpace[SM4_ARRAY_SIZE];
};