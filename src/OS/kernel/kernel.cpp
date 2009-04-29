#include "common.h"
#include "screen.h"
#include "console.h"
#include "gdt.h"

/* Somithing to comply with the multiboot specification */
extern "C" void kmain(struct multiboot_data* mbd, unsigned int magic);

/* To enable pure virtual functions you need a fallback method: */
extern "C" void __cxa_pure_virtual()
{
	//optional error message
}
/* to make classes work */
void *__gxx_personality_v0;
void *_Unwind_Resume;

void kmain(struct multiboot_data* mbd, unsigned int magic )
{
	if(magic != 0x2BADB002)
	{
		/* Something went not according to specs.  Print an error */
		/* message and halt, bot do *not* rely on the multiboot */
		/* data structure */
	}

	/* You could either use multiboot.h */
	/* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
	/* or do your offsets yourself. The following is merely an example. */
	char * boot_loader_name = (char *)mbd + 64;

	/* Declare our screen (0xB8000 is the start of video ram */
	screen monitor( (unsigned char*)0xB8000);
	monitor.clear();
	console terminal(monitor);
	terminal << "Width = " << terminal.getSizeX() << ", height = " << terminal.getSizeY() << console::endl;
	for(int i=0; i<5; ++i)
	{
		terminal << "Hello World!" << console::endl << console::endl << "Hello on the next line \\o/" << console::endl << "And another" << console::endl;
	}
	terminal << "cursorX = " << terminal.getCursorX() << ", cursorY = " << terminal.getCursorY() << console::endl;

	/* Set up the GDT */
	gdt globalDescriptorTable();
	
	while(true)
	{
		
	}
	/* Write your kernel here. */
	++boot_loader_name;
}
