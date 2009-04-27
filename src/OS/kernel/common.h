#ifndef COMMON_H
#define COMMON_H

/* function to write a byte to the specified port */
void outb(unsigned short port, unsigned char value);
/* function to read in a char from the specified port */
unsigned char inb(unsigned short port);
/* function to read in a word from the specified port */
unsigned short inw(unsigned short port);

#endif
