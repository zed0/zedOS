#ifndef CONSOLE_H
#define CONSOLE_H

#include "screen.h"

class console
{
	private:
		screen &output;
		unsigned short cursorX;
		unsigned short cursorY;
		unsigned short sizeX;
		unsigned short sizeY;
	public:
		console(screen &newOutput);
		~console();

/* functions to get information about the console */
		unsigned short getCursorX();
		unsigned short getCursorY();
		unsigned short getSizeX();
		unsigned short getSizeY();
		unsigned char getChar(unsigned short posX, unsigned short posY);

/* functions to set things on the console */
		void put(unsigned char);
		void clear();
		void scroll();
		void scroll(unsigned short numRows);
		void flush();

/* shortcut functions */
		void write(const char *word);

/* operators etc */
		console& operator<<(const int number);
		console& operator<<(const char character);
		console& operator<<(const char *word);
		console& operator<<(console& (*stream)(console&));
		static console& endl(console& stream);
};

#endif
