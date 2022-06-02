#include "sm4.h"
#include <cstdio>

int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);
    
    const unsigned char key[16] =
    {
        0x01, 0x23, 0x45, 0x67,
        0x89, 0xab, 0xcd, 0xef,
        0xfe, 0xdc, 0xba, 0x98,
        0x76, 0x54, 0x32, 0x10
    };
    
    const unsigned char inputDataBlock[16] =
    {
        0x01, 0x23, 0x45, 0x67,
        0x89, 0xab, 0xcd, 0xef,
        0xfe, 0xdc, 0xba, 0x98,
        0x76, 0x54, 0x32, 0x10
    };

    unsigned char encryptionDataBlock[16] = { 0 };
    unsigned char decryptionDataBlock[16] = { 0 };
    
    SM4 sm4;

    std::printf("User (Master) key is:\n");
    for (int i = 0; i < 16; i++)
    {
        std::printf("%02X ", key[i]);
    }
    std::printf("\n\n");

    std::printf("Plain text is:\n");
    for (int i = 0; i < 16; i++)
    {
        std::printf("%02X ", inputDataBlock[i]);
    }
    std::printf("\n\n");

    sm4.UncheckedSetKey(key, sizeof(key)/sizeof(unsigned char));
    sm4.Encrypt(inputDataBlock, sizeof(inputDataBlock) / sizeof(unsigned char) , encryptionDataBlock, sizeof(encryptionDataBlock) / sizeof(unsigned char));
    sm4.Decrypt(encryptionDataBlock, sizeof(encryptionDataBlock) / sizeof(unsigned char), decryptionDataBlock, sizeof(decryptionDataBlock) / sizeof(unsigned char));

    std::printf("Encryption text is:\n");
    for (int i = 0; i < 16; i++)
    {
        std::printf("%02X ", encryptionDataBlock[i]);
    }
    std::printf("\n");

    return 0;
}