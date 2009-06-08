# A basic Makefile for zed0

SOURCES=kernel.o loader.o common.o screen.o console.o gdt.o idt.o isrs.o

# Flags to compile .c(pp) files with
CFLAGS=-Wall -Wextra -Werror -nostdlib -nostartfiles -nodefaultlibs -O
#CFLAGS=-nostdlib -nostartfiles -nodefaultlibs
# Flags to complie .ld files with
LDFLAGS=-T linker.ld
# Flags to compile .s files with
ASFLAGS=-f elf

# make all will cycle through each item in SOURCES
all: $(SOURCES) link

# make clean will remove all .o files as well as the kernel binary
clean:
	-rm *.o kernel.bin

# make link will link the specified file using i586-elf-ld so we use our linker
link:
	i586-elf-ld $(LDFLAGS) -o kernel.bin $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<

# make will use our version of gcc to make c(pp) files
.c.o:
	i586-elf-g++ $(CFLAGS) -c $<

# make will use our version of gcc to make c(pp) files
.cpp.o:
	i586-elf-g++ $(CFLAGS) -c $<
