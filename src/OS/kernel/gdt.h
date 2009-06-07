#ifndef GDT_H
#define GDT_H

#include "common.h"

/* The structure of a GDT entry */
struct gdtEntry
{
	u16int limitLow;
	u16int baseLow;
	u8int baseMiddle;
	u8int access;
	u8int granularity;
	u8int baseHigh;
} __attribute__((packed));

/* Our pointer to the GDT */
struct gdtPointer
{
	u16int limit;
	unsigned int base;
} __attribute__((packed));

class gdt
{
	private:
/* Our minimal GDT with 3 entries and our GDT pointer */
		struct gdtEntry globalDescriptorTable[3];
		//static struct gdtPointer gp;
		struct gdtPointer gdtPtr;
	public:
		gdt();
		void setGate(u32int num, u32int base, u32int limit, u8int access, u8int gran);
		void flush();
};

#endif
