#pragma once

#include "util.h"

#define SM4_NUM_ROUNDS 32

class SM4 
{
public:
	SM4();
	~SM4();

	void UncheckedSetKey(const byte* userKey, unsigned int keyLength);

private:

	void GetUserKey(void* dest, const byte* userKey, int keyLength);

	word32 SM4_G(word32 x);
	word32 SM4_H(word32 x);

	word32 m_rkeys[SM4_NUM_ROUNDS];

	word32 m_wspace[5];
};