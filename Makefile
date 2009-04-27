floppy.img: stage1 stage2 pad kernel.bin
	cat stage1 stage2 pad kernel.bin > floppy.img

kernel.bin: src/OS/kernel/kernel.bin
	cp src/OS/kernel/kernel.bin .

