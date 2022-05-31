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