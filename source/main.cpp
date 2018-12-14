#include <stdint.h>
#include <stdarg.h>

#include "../include/types.h"
#include "../include/imports.h"
#include "../include/syscall.h"
#include "../include/detour.h"

extern "C" void _main(void) {
	initImports();

	sceSysUtilSendSystemNotificationWithText(222, "Clean PS4 ELF Loaded");
}
