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

class gdt
{
	private:
/* Our minimal GDT with 3 entries and our GDT pointer */
		struct gdt_entry gdt[3];
		struct gdt_ptr gp;
	public:
		void gdt_flush();
};

#endif
