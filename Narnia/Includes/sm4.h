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
	word32 m_rkeys[SM4_NUM_ROUNDS];
};