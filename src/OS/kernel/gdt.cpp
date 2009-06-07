#include "gdt.h"

gdt::gdt()
{
	/* Set the gdt pointer and limit */
	gdtPtr.limit = (sizeof(struct gdtEntry) * 3) - 1;
	gdtPtr.base = u32int(&globalDescriptorTable);

	/* Our NULL descriptor */
	setGate(0, 0, 0, 0, 0);

	/* Our Code Segment. */
	setGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

	/* Our Data Segment. */
	setGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	/* Flush out the old GDT and install ours */
	flush();
}

void gdt::setGate(u32int num, u32int base, u32int limit, u8int access, u8int gran)
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

void gdt::flush()
{
	/* Load GDT pointer (gdtPtr) */
	asm volatile("lgdt %0" : "=m" (gdtPtr));
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
