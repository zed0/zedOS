#include "common.h"

void outb(unsigned short port, unsigned char value)
{
	asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

unsigned char inb(unsigned short port)
{
	unsigned char result;
	asm volatile("inb %1, %0" : "=a" (result) : "dN" (port));
	return result;
}

unsigned short inw(unsigned short port)
{
	unsigned short result;
	asm volatile("inw %1, %0" : "=a" (result) : "dN" (port));
	return result;
}
