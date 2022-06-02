#pragma once

typedef unsigned char byte;
typedef unsigned int word32;

#define UNUSED(x) (void)(x)

#if defined (_MSC_VER)
// this version of the macro is fastest on Pentium 3 and Pentium 4 with MSVC 6 SP5 w/ Processor Pack
#define GETBYTE(x, y) (unsigned int)byte((x)>>(8*(y)))
#else
// these may be faster on other CPUs/compilers
 //#define GETBYTE(x, y) (unsigned int)(((x)>>(8*(y)))&255)
 //#define GETBYTE(x, y) (((byte *)&(x))[y])
#endif


#define ROL32(a,n) (((a)<<(n)) | (((a)&0xffffffff)>>(32-(n))))
//#define ROL64(a,n) (((a)<<(n))|((a)>>(64-(n))))
//
//#define ROR32(a,n) ROL32((a),32-(n))
//#define ROR64(a,n) ROL64(a,64-n)


/*************************************************************/

/*
* Convert data with big endian or little endian 
* Referece from Gmssl and Openssl but the implementation of Crytopp is much eligant and efficient (Need to be checked)
*/

#define STRICT_ALIGNMENT 1
#ifndef PEDANTIC
# if defined(__i386)    || defined(__i386__)    || \
     defined(__x86_64)  || defined(__x86_64__)  || \
     defined(_M_IX86)   || defined(_M_AMD64)    || defined(_M_X64) || \
     defined(__aarch64__)                       || \
     defined(__s390__)  || defined(__s390x__)
#  undef STRICT_ALIGNMENT
# endif
#endif

#if defined (_MSC_VER)
#if _MSC_VER >= 1300
# include <stdlib.h>
# pragma intrinsic(_byteswap_uint64,_byteswap_ulong)
# define BSWAP8(x)    _byteswap_uint64((u64)(x))
# define BSWAP4(x)    _byteswap_ulong((u32)(x))
#endif
#endif


#define STRICT_ALIGNMENT 1 // TODO: Temp defined, need to fix
#if defined (BSWAP4) && !defined(STRICT_ALIGNMENT)
# define GETWORD32(p)       BSWAP4(*(const word32 *)(p))
# define PUTWORD32(p,v)     *(word32 *)(p) = BSWAP4(v)
#else
# define GETWORD32(p)       ((word32)(p)[0]<<24|(word32)(p)[1]<<16|(word32)(p)[2]<<8|(word32)(p)[3])
# define PUTWORD32(p,v)     ((p)[0]=(byte)((v)>>24),(p)[1]=(byte)((v)>>16),(p)[2]=(byte)((v)>>8),(p)[3]=(byte)(v))
#endif
#undef STRICT_ALIGNMENT

/*************************************************************/
