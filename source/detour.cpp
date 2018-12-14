#include "../include/detour.h"
#include "../include/imports.h"
#include "../include/utility.h"

void PatchInJump(uint64_t address, void* destination) {
	if (!address || !destination)
		return;

	*(uint8_t*)(address) = 0xFF;
	*(uint8_t*)(address + 1) = 0x25;
	*(uint8_t*)(address + 2) = 0x00;
	*(uint8_t*)(address + 3) = 0x00;
	*(uint8_t*)(address + 4) = 0x00;
	*(uint8_t*)(address + 5) = 0x00;
	*(uint64_t*)(address + 6) = (uint64_t)destination;
}

void* DetourFunction(uint64_t address, void* destination, int length) {
	if (!address || !destination)
		return 0;

	if (length < HOOK_LENGTH)
		return 0;

	int stubLength = length + HOOK_LENGTH;
	void* stubAddress = (void*)sys_mmap(0, stubLength, 1 | 2 | 4, 0x1000 | 0x2, -1, 0);

	ReadMemory((uint64_t)address, stubAddress, length);
	PatchInJump((uint64_t)stubAddress + length, (void*)(address + length));
	PatchInJump(address, destination);

	return stubAddress;
}

/*
	Example:
	- hook length must be greater than 14 and has to line up with instructions
	- i.e. if 14 bytes ends up in the middle of the instruction, count how many more ops are in the instruction and add that to 14
	- many functions end up being length 17 or 20

	typedef void (*Function_t)(uint64_t);
	Function_t Function_s;
	void Function_h(uint64_t parameter1)
	{
		Function_s(parameter1);
	}

	extern "C" void _start(void)
	{
		Function_s = (Function_t)DetourFunction(0x0, Function_h, length);
	}
*/