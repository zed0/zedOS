#include "gdt.h"

void gdt::gdt_flush()
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
