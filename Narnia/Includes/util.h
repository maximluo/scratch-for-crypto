#pragma once

typedef unsigned char byte;
typedef unsigned int word32;

#define UNUSED(x) (void)(x)

// this version of the macro is fastest on Pentium 3 and Pentium 4 with MSVC 6 SP5 w/ Processor Pack
#define GETBYTE(x, y) (unsigned int)byte((x)>>(8*(y)))
// these may be faster on other CPUs/compilers
// #define GETBYTE(x, y) (unsigned int)(((x)>>(8*(y)))&255)
// #define GETBYTE(x, y) (((byte *)&(x))[y])

#define ROL32(a,n) (((a)<<(n)) | (((a)&0xffffffff)>>(32-(n))))
//#define ROL64(a,n) (((a)<<(n))|((a)>>(64-(n))))
//
//#define ROR32(a,n) ROL32((a),32-(n))
//#define ROR64(a,n) ROL64(a,64-n)


/*************************************************************/

/*
* Convert big endian data to little endian data 
* Note: Referece from Gmssl but the implementation of Crytopp is much eligant and efficient (Need to be checked)
*/

//#define GETU16(p) \
//    ((uint16_t)(p)[0] <<  8 | \
//     (uint16_t)(p)[1])

#define GETWORd32(p) \
    ((word32)(p)[0] << 24 | \
     (word32)(p)[1] << 16 | \
     (word32)(p)[2] <<  8 | \
     (word32)(p)[3])

//#define GETU64(p) \
//    ((uint64_t)(p)[0] << 56 | \
//     (uint64_t)(p)[1] << 48 | \
//     (uint64_t)(p)[2] << 40 | \
//     (uint64_t)(p)[3] << 32 | \
//     (uint64_t)(p)[4] << 24 | \
//     (uint64_t)(p)[5] << 16 | \
//     (uint64_t)(p)[6] <<  8 | \
//     (uint64_t)(p)[7])

/*************************************************************/
