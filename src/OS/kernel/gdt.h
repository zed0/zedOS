#ifndef GDT_H
#define GDT_H

/* The structure of a GDT entry */
struct gdtEntry
{
	unsigned short limitLow;
	unsigned short baseLow;
	unsigned char baseMiddle;
	unsigned char access;
	unsigned char granularity;
	unsigned char baseHigh;
} __attribute__((packed));

/* Our pointer to the GDT */
struct gdtPointer
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

class gdt
{
	private:
/* Our minimal GDT with 3 entries and our GDT pointer */
		struct gdtEntry globalDescriptorTable[3];
		//static struct gdtPointer gp;
		struct gdtPointer gp;
	public:
		gdt();
		void setGate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
		void flush();
};

#endif
