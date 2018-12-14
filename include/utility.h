#pragma once

#include "types.h"

void Sleep(unsigned int milliseconds);
void ReadMemory(uint64_t address, void* buffer, int length);
void WriteMemory(uint64_t address, void* buffer, int length);
void NOP(uint64_t address, size_t length);
void printf(const char *fmt, ...);