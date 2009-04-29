#include "gdt.h"

void gdt::flush()
{
	/* Load GDT pointer (gp) */
	asm volatile("lgdt %0" : "=m" (gp));
	/* Jump to new segment (0x08 in this case) */
	asm volatile("ljmp $(0x08), $reload_segments");
	asm volatile("reload_segments:");
	asm volatile("movl $0x10, %eax");
	asm volatile("movl %eax, %ds");
	asm volatile("movl %eax, %es");
	asm volatile("movl %eax, %fs");
	asm volatile("movl %eax, %gs");
	asm volatile("movl %eax, %ss");
}

void gdt::setGate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
	/* Set up the descriptor base address */
	globalDescriptorTable[num].baseLow = (base & 0xFFFF);
	globalDescriptorTable[num].baseMiddle = (base >> 16) & 0xFF;
	globalDescriptorTable[num].baseHigh = (base >> 24) & 0xFF;

	/* Set up the descriptor limits */
	globalDescriptorTable[num].limitLow = (limit & 0xFFFF);
	globalDescriptorTable[num].granularity = ((limit >> 16) & 0x0F);

	/* Finally, set up the granularity and access flags */
	globalDescriptorTable[num].granularity |= (gran & 0xF0);
	globalDescriptorTable[num].access = access;
}

void gdt::init()
{
	/* Set the gdt pointer and limit */
	gp.limit = (sizeof(struct gdtEntry) * 3) - 1;
	gp.base = &gdt;

	/* Our NULL descriptor */
	setGate(0, 0, 0, 0, 0);

	/* Our Code Segment. */
	setGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

	/* Our Data Segment. */
	setGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	/* Flush out the old GDT and install ours */
	flush();
}
