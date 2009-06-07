#include "common.h"

void outb(u16int port, u8int value)
{
	asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
	u8int result;
	asm volatile("inb %1, %0" : "=a" (result) : "dN" (port));
	return result;
}

u16int inw(u16int port)
{
	u16int result;
	asm volatile("inw %1, %0" : "=a" (result) : "dN" (port));
	return result;
}

void *memset(void *dest, u8int val, u32int len)
{
	u8int* current = reinterpret_cast<u8int*>(dest);
	for(u32int i=0; i<len; ++i)
	{
		*current++ = u8int(val);
	}
	return dest;
}
