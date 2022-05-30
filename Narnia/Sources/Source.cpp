#include <iostream>
#include "sm4.h"

int main(int argc, char** argv)
{
	UNUSED(argc);
	UNUSED(argv);

	std::cout << "hello world" << std::endl;

	unsigned char key[16] =
	{
		0x01, 0x23, 0x45, 0x67,
		0x89, 0xab, 0xcd, 0xef,
		0xfe, 0xdc, 0xba, 0x98,
		0x76, 0x54, 0x32, 0x10
	};

	SM4 sm4;
	sm4.UncheckedSetKey(key, 16);
	return 0;
}