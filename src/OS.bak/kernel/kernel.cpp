extern "C" void kmain(struct multiboot_data* mbd, unsigned int magic);

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

	/* Print a letter to screen to see everything is working: */
	unsigned char *videoram = (unsigned char *) 0xb8000;
	videoram[0] = 65; /* character 'A' */
	videoram[1] = 0x07; /* foreground, background color. */

	/* Write your kernel here. */
	videoram[2] = *boot_loader_name;
}
