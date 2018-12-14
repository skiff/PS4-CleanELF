#include "../include/syscall.h"

unsigned long syscall(unsigned int n, ...) {
	asm(".intel_syntax noprefix");
	asm("xor rax, rax");
	asm("mov r10, rcx");
	asm("syscall");
	asm("ret");
}