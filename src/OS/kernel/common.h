#ifndef COMMON_H
#define COMMON_H

//A few typedefs to make life easier
typedef	unsigned	int		u32int;
typedef	signed		int		s32int;
typedef	unsigned	short	u16int;
typedef	signed		short	s16int;
typedef	unsigned	char	u8int;
typedef	signed		char	s8int;

/* function to write a byte to the specified port */
void outb(u16int port, u8int value);
/* function to read in a char from the specified port */
unsigned char inb(u16int port);
/* function to read in a word from the specified port */
unsigned short inw(u16int port);
/* funciton to write val to dest len times */
void *memset(void *dest, u8int val, u32int len);

#endif
