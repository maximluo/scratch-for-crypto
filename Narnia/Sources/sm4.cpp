#include "sm4.h"
#include <cstring>
#include <cstdio>

const byte S[256] =
{
    0xD6, 0x90, 0xE9, 0xFE, 0xCC, 0xE1, 0x3D, 0xB7, 0x16, 0xB6, 0x14, 0xC2, 0x28, 0xFB, 0x2C, 0x05,
    0x2B, 0x67, 0x9A, 0x76, 0x2A, 0xBE, 0x04, 0xC3, 0xAA, 0x44, 0x13, 0x26, 0x49, 0x86, 0x06, 0x99,
    0x9C, 0x42, 0x50, 0xF4, 0x91, 0xEF, 0x98, 0x7A, 0x33, 0x54, 0x0B, 0x43, 0xED, 0xCF, 0xAC, 0x62,
    0xE4, 0xB3, 0x1C, 0xA9, 0xC9, 0x08, 0xE8, 0x95, 0x80, 0xDF, 0x94, 0xFA, 0x75, 0x8F, 0x3F, 0xA6,
    0x47, 0x07, 0xA7, 0xFC, 0xF3, 0x73, 0x17, 0xBA, 0x83, 0x59, 0x3C, 0x19, 0xE6, 0x85, 0x4F, 0xA8,
    0x68, 0x6B, 0x81, 0xB2, 0x71, 0x64, 0xDA, 0x8B, 0xF8, 0xEB, 0x0F, 0x4B, 0x70, 0x56, 0x9D, 0x35,
    0x1E, 0x24, 0x0E, 0x5E, 0x63, 0x58, 0xD1, 0xA2, 0x25, 0x22, 0x7C, 0x3B, 0x01, 0x21, 0x78, 0x87,
    0xD4, 0x00, 0x46, 0x57, 0x9F, 0xD3, 0x27, 0x52, 0x4C, 0x36, 0x02, 0xE7, 0xA0, 0xC4, 0xC8, 0x9E,
    0xEA, 0xBF, 0x8A, 0xD2, 0x40, 0xC7, 0x38, 0xB5, 0xA3, 0xF7, 0xF2, 0xCE, 0xF9, 0x61, 0x15, 0xA1,
    0xE0, 0xAE, 0x5D, 0xA4, 0x9B, 0x34, 0x1A, 0x55, 0xAD, 0x93, 0x32, 0x30, 0xF5, 0x8C, 0xB1, 0xE3,
    0x1D, 0xF6, 0xE2, 0x2E, 0x82, 0x66, 0xCA, 0x60, 0xC0, 0x29, 0x23, 0xAB, 0x0D, 0x53, 0x4E, 0x6F,
    0xD5, 0xDB, 0x37, 0x45, 0xDE, 0xFD, 0x8E, 0x2F, 0x03, 0xFF, 0x6A, 0x72, 0x6D, 0x6C, 0x5B, 0x51,
    0x8D, 0x1B, 0xAF, 0x92, 0xBB, 0xDD, 0xBC, 0x7F, 0x11, 0xD9, 0x5C, 0x41, 0x1F, 0x10, 0x5A, 0xD8,
    0x0A, 0xC1, 0x31, 0x88, 0xA5, 0xCD, 0x7B, 0xBD, 0x2D, 0x74, 0xD0, 0x12, 0xB8, 0xE5, 0xB4, 0xB0,
    0x89, 0x69, 0x97, 0x4A, 0x0C, 0x96, 0x77, 0x7E, 0x65, 0xB9, 0xF1, 0x09, 0xC5, 0x6E, 0xC6, 0x84,
    0x18, 0xF0, 0x7D, 0xEC, 0x3A, 0xDC, 0x4D, 0x20, 0x79, 0xEE, 0x5F, 0x3E, 0xD7, 0xCB, 0x39, 0x48
};

const word32 CK[32] =
{
    0x00070E15, 0x1C232A31, 0x383F464D, 0x545B6269,
    0x70777E85, 0x8C939AA1, 0xA8AFB6BD, 0xC4CBD2D9,
    0xE0E7EEF5, 0xFC030A11, 0x181F262D, 0x343B4249,
    0x50575E65, 0x6C737A81, 0x888F969D, 0xA4ABB2B9,
    0xC0C7CED5, 0xDCE3EAF1, 0xF8FF060D, 0x141B2229,
    0x30373E45, 0x4C535A61, 0x686F767D, 0x848B9299,
    0xA0A7AEB5, 0xBCC3CAD1, 0xD8DFE6ED, 0xF4FB0209,
    0x10171E25, 0x2C333A41, 0x484F565D, 0x646B7279
};

const word32 FK[4] =
{
    0xa3b1bac6, 0x56aa3350, 0x677d9197, 0xb27022dc
};

SM4::SM4()
{
    std::memset(m_rKeys, 0, SM4_NUM_ROUNDS);
    std::memset(m_wSpace, 0, sizeof(m_wSpace));
}

SM4::~SM4()
{

}

void SM4::UncheckedSetKey(const byte* mainKey, unsigned int keyLength)
{
    // TODO: need to check keyLength
    (void)keyLength;

    ConvertBigEndianToLittleEndian(mainKey, keyLength);

    // Get value of K0, K1, K2 and K3
    m_wSpace[0] ^= FK[0];
    m_wSpace[1] ^= FK[1];
    m_wSpace[2] ^= FK[2];
    m_wSpace[3] ^= FK[3];

    // Get round keys
    for (int i = 0; i < SM4_NUM_ROUNDS;)
    {
        m_rKeys[i] = (m_wSpace[0] ^= SM4_G(m_wSpace[1] ^ m_wSpace[2] ^ m_wSpace[3] ^ CK[i])); i++;
        m_rKeys[i] = (m_wSpace[1] ^= SM4_G(m_wSpace[2] ^ m_wSpace[3] ^ m_wSpace[0] ^ CK[i])); i++;
        m_rKeys[i] = (m_wSpace[2] ^= SM4_G(m_wSpace[3] ^ m_wSpace[0] ^ m_wSpace[1] ^ CK[i])); i++;
        m_rKeys[i] = (m_wSpace[3] ^= SM4_G(m_wSpace[0] ^ m_wSpace[1] ^ m_wSpace[2] ^ CK[i])); i++;
    }
}

void SM4::ConvertBigEndianToLittleEndian(const byte* data, unsigned int size)
{
    (void)size;

    std::memset(m_wSpace, 0, sizeof(m_wSpace));

    // Brute force to convert
    m_wSpace[0] = GETWORD32(data);
    m_wSpace[1] = GETWORD32(data + 4);
    m_wSpace[2] = GETWORD32(data + 8);
    m_wSpace[3] = GETWORD32(data + 12);
}

void SM4::ConvertLittleEndianToBigEndian(byte* data, unsigned int size)
{
    std::memset(data, 0, size);

    // Brute force to convert
    PUTWORD32(data, m_wSpace[3]);
    PUTWORD32(data + 4, m_wSpace[2]);
    PUTWORD32(data + 8, m_wSpace[1]);
    PUTWORD32(data + 12, m_wSpace[0]);
}

word32 SM4::SM4_G(word32 x)
{
    const word32 t = SM4_H(x);
    
    // The linear transform L' for round keys
    return t ^ ROL32(t,13) ^ ROL32(t,23);
}

word32 SM4::SM4_H(word32 x)
{
    return (S[GETBYTE(x, 3)] << 24) | (S[GETBYTE(x, 2)] << 16) | (S[GETBYTE(x, 1)] << 8) | (S[GETBYTE(x, 0)]);
}

word32 SM4::SM4_F(word32 x)
{
    const word32 t = SM4_H(x);

    // The linear transform L for encrypt/decrypt
    return t ^ ROL32(t, 2) ^ ROL32(t, 10) ^ ROL32(t, 18) ^ ROL32(t, 24);
}

void SM4::SM4_Round(word32* wSpace, const word32* rKeys, unsigned int round, bool bEncrypt)
{
    if (!bEncrypt)
    {
        wSpace[0] ^= SM4_F(wSpace[1] ^ wSpace[2] ^ wSpace[3] ^ rKeys[round - 0]);
        wSpace[1] ^= SM4_F(wSpace[0] ^ wSpace[2] ^ wSpace[3] ^ rKeys[round - 1]);
        wSpace[2] ^= SM4_F(wSpace[0] ^ wSpace[1] ^ wSpace[3] ^ rKeys[round - 2]);
        wSpace[3] ^= SM4_F(wSpace[0] ^ wSpace[1] ^ wSpace[2] ^ rKeys[round - 3]);
    }
    else
    {
        wSpace[0] ^= SM4_F(wSpace[1] ^ wSpace[2] ^ wSpace[3] ^ rKeys[round + 0]);
        wSpace[1] ^= SM4_F(wSpace[0] ^ wSpace[2] ^ wSpace[3] ^ rKeys[round + 1]);
        wSpace[2] ^= SM4_F(wSpace[0] ^ wSpace[1] ^ wSpace[3] ^ rKeys[round + 2]);
        wSpace[3] ^= SM4_F(wSpace[0] ^ wSpace[1] ^ wSpace[2] ^ rKeys[round + 3]);

        std::printf("rk[%02d]=%08X     X[%02d]=%08X \n", round + 0, rKeys[round + 0], round + 4, wSpace[0]);
        std::printf("rk[%02d]=%08X     X[%02d]=%08X \n", round + 1, rKeys[round + 1], round + 5, wSpace[1]);
        std::printf("rk[%02d]=%08X     X[%02d]=%08X \n", round + 2, rKeys[round + 2], round + 6, wSpace[2]);
        std::printf("rk[%02d]=%08X     X[%02d]=%08X \n", round + 3, rKeys[round + 3], round + 7, wSpace[3]);
    }
}

void SM4::Encrypt(const byte* inBlock, unsigned int inBlockSize, byte* outBlock, unsigned int outBlockSize)
{
    // TODO: need to check in/out block size

    ConvertBigEndianToLittleEndian(inBlock, inBlockSize);

    // Encrypt the message, the length of stride is 4
    std::printf("Encryption round keys and states are: \n");
    SM4_Round(m_wSpace, m_rKeys, 0, true);
    SM4_Round(m_wSpace, m_rKeys, 4, true);
    SM4_Round(m_wSpace, m_rKeys, 8, true);
    SM4_Round(m_wSpace, m_rKeys, 12, true);
    SM4_Round(m_wSpace, m_rKeys, 16, true);
    SM4_Round(m_wSpace, m_rKeys, 20, true);
    SM4_Round(m_wSpace, m_rKeys, 24, true);
    SM4_Round(m_wSpace, m_rKeys, 28, true);
    std::printf("\n");

    ConvertLittleEndianToBigEndian(outBlock, outBlockSize);
}

void SM4::Decrypt(const byte* inBlock, unsigned int inBlockSize, byte* outBlock, unsigned int outBlockSize)
{
    // TODO: need to check in/out block size

    ConvertBigEndianToLittleEndian(inBlock, inBlockSize);

    // Decrypt the message, the length of stride is 4
    SM4_Round(m_wSpace, m_rKeys, 31, false);
    SM4_Round(m_wSpace, m_rKeys, 27, false);
    SM4_Round(m_wSpace, m_rKeys, 23, false);
    SM4_Round(m_wSpace, m_rKeys, 19, false);
    SM4_Round(m_wSpace, m_rKeys, 15, false);
    SM4_Round(m_wSpace, m_rKeys, 11, false);
    SM4_Round(m_wSpace, m_rKeys, 7, false);
    SM4_Round(m_wSpace, m_rKeys, 3, false);

    ConvertLittleEndianToBigEndian(outBlock, outBlockSize);
}
