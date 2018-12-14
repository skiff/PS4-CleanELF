#include "../include/imports.h"

unsigned int(*sceKernelSleep)(unsigned int seconds);
int(*sceKernelUsleep)(unsigned int microseconds);

//threads
int(*scePthreadCreate)(ScePthread *thread, const ScePthreadAttr *attr, void *(*entry) (void *), void *arg, const char *name);
void(*scePthreadExit)(void *value);
int(*scePthreadDetach)(ScePthread thread);
int(*scePthreadJoin)(ScePthread thread, void **value_ptr);

//network
int(*sceNetSocket)(const char *, int, int, int);
int(*sceNetSocketClose)(int);
int(*sceNetConnect)(int, struct sockaddr *, int);
int(*sceNetSend)(int, const void *, size_t, int);

//sys
int(*sceKernelLoadStartModule)(const char *name, size_t argc, const void *argv, unsigned int flags, int, int);

//notifications
int(*sceSysUtilSendSystemNotificationWithText)(int messageType, const char* message);

//libc
void *(*malloc)(size_t size);
void(*free)(void *ptr);
void *(*calloc)(size_t num, size_t size);
void *(*realloc)(void* ptr, size_t size);
void *(*memset)(void *destination, int value, size_t num);
void *(*memcpy)(void *destination, const void *source, size_t num);
int(*memcmp)(const void *s1, const void *s2, size_t n);
char *(*strcpy)(char *destination, const char *source);
char *(*strncpy)(char *destination, const char *source, size_t num);
char *(*strcat)(char *dest, const char *src);
char *(*strncat)(char *dest, const char *src, size_t n);
size_t(*strlen)(const char *s);
int(*strcmp)(const char *s1, const char *s2);
int(*strncmp)(const char *s1, const char *s2, size_t n);
int(*sprintf)(char *str, const char *format, ...);
int(*snprintf)(char *str, size_t size, const char *format, ...);
int(*vsprintf)(char * s, const char * format, va_list arg);
int(*sscanf)(const char *str, const char *format, ...);
char *(*strchr)(const char *s, int c);
char *(*strrchr)(const char *s, int c);
char *(*strstr)(char *str1, char *str2);
int(*atoi)(const char * str);
double(*atof)(const char * str);
double(*sin)(double x);
double(*cos)(double x);
double(*atan2)(double x, double y);
double(*sqrt)(double vec);

void* sys_mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset) {
	return (void*)syscall(477, addr, len, prot, flags, fd, offset);
}

void* sys_munmap(void *addr, size_t len) {
	return (void*)syscall(479, addr, len);
}

int sys_dynlib_dlsym(int loadedModuleID, const char *name, void *destination) {
	return syscall(591, loadedModuleID, name, destination);
}

int sys_dynlib_load_prx(const char *name, int *idDestination) {
	return syscall(594, name, 0, idDestination, 0);
}

void initImports() {
	int h = 0;

	//kernel imports
	sys_dynlib_load_prx("libkernel.sprx", &h);
	sys_dynlib_dlsym(h, "sceKernelSleep", &sceKernelSleep);
	sys_dynlib_dlsym(h, "sceKernelUsleep", &sceKernelUsleep);

	//thread imports
	sys_dynlib_dlsym(h, "scePthreadCreate", &scePthreadCreate);
	sys_dynlib_dlsym(h, "scePthreadExit", &scePthreadExit);
	sys_dynlib_dlsym(h, "scePthreadDetach", &scePthreadDetach);
	sys_dynlib_dlsym(h, "scePthreadJoin", &scePthreadJoin);

	//network imports
	sys_dynlib_load_prx("libSceNet.sprx", &h);
	sys_dynlib_dlsym(h, "sceNetSocket", &sceNetSocket);
	sys_dynlib_dlsym(h, "sceNetSocketClose", &sceNetSocketClose);
	sys_dynlib_dlsym(h, "sceNetConnect", &sceNetConnect);
	sys_dynlib_dlsym(h, "sceNetSend", &sceNetSend);

	//libc imports
	sys_dynlib_load_prx("libSceLibcInternal.sprx", &h);
	sys_dynlib_dlsym(h, "malloc", &malloc);
	sys_dynlib_dlsym(h, "free", &free);
	sys_dynlib_dlsym(h, "calloc", &calloc);
	sys_dynlib_dlsym(h, "realloc", &realloc);
	sys_dynlib_dlsym(h, "memset", &memset);
	sys_dynlib_dlsym(h, "memcpy", &memcpy);
	sys_dynlib_dlsym(h, "memcmp", &memcmp);
	sys_dynlib_dlsym(h, "strcpy", &strcpy);
	sys_dynlib_dlsym(h, "strncpy", &strncpy);
	sys_dynlib_dlsym(h, "strcat", &strcat);
	sys_dynlib_dlsym(h, "strncat", &strncat);
	sys_dynlib_dlsym(h, "strlen", &strlen);
	sys_dynlib_dlsym(h, "strcmp", &strcmp);
	sys_dynlib_dlsym(h, "strncmp", &strncmp);
	sys_dynlib_dlsym(h, "sprintf", &sprintf);
	sys_dynlib_dlsym(h, "snprintf", &snprintf);
	sys_dynlib_dlsym(h, "vsprintf", &vsprintf);
	sys_dynlib_dlsym(h, "sscanf", &sscanf);
	sys_dynlib_dlsym(h, "strchr", &strchr);
	sys_dynlib_dlsym(h, "strrchr", &strrchr);
	sys_dynlib_dlsym(h, "strstr", &strstr);
	sys_dynlib_dlsym(h, "atoi", &atoi);
	sys_dynlib_dlsym(h, "atof", &atof);
	sys_dynlib_dlsym(h, "sin", &sin);
	sys_dynlib_dlsym(h, "cos", &cos);
	sys_dynlib_dlsym(h, "atan2", &atan2);
	sys_dynlib_dlsym(h, "sqrt", &sqrt);

	//sys
	if (sys_dynlib_load_prx("libkernel.sprx", &h))
		if (sys_dynlib_load_prx("libkernel_web.sprx", &h))
			sys_dynlib_load_prx("libkernel_sys.sprx", &h);

	sys_dynlib_dlsym(h, "sceKernelLoadStartModule", &sceKernelLoadStartModule);

	//notify
	int sysUtilHandle = sceKernelLoadStartModule("libSceSysUtil.sprx", 0, NULL, 0, 0, 0);
	sys_dynlib_dlsym(sysUtilHandle, "sceSysUtilSendSystemNotificationWithText", &sceSysUtilSendSystemNotificationWithText);
}