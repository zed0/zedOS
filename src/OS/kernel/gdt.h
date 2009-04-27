#ifndef GDT_H
#define GDT_H

/* The structure of a GDT entry */
struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));

/* Our pointer to the GDT */
struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

#endif
