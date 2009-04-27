#include "console.h"

console::console(screen &newOutput):output(newOutput)
{
	cursorX = 0;
	cursorY = 0;
	sizeX = output.getSizeX();
	sizeY = output.getSizeY();
}

console::~console()
{
}

unsigned short console::getCursorX()
{
	return cursorX;
}

unsigned short console::getCursorY()
{
	return cursorY;
}

unsigned short console::getSizeX()
{
	return sizeX;
}

unsigned short console::getSizeY()
{
	return sizeY;
}

unsigned char console::getChar(unsigned short posX, unsigned short posY)
{
	return output.getChar(posX, posY);
}

void console::put(unsigned char character)
{
/* If character is a newline then move the cursor to the start of the next line */
	if(character == '\n')
	{
		cursorX = 0;
		++cursorY;
	}
/* otherwise print the character and move the cursor to the next positon */
	else
	{
		output.setChar(cursorX, cursorY, character);
		++cursorX;
		if(cursorX >= sizeX)
		{
			cursorX = 0;
			++cursorY;
		}
	}
/* If we need to scroll the screen for a new line then do so */
	if(cursorY >= sizeY)
	{
		scroll();
		--cursorY;
	}
}

void console::clear()
{
	output.clear();
}

void console::scroll()
{
	scroll(1);
}

void console::scroll(unsigned short numRows)
{
	output.scroll(numRows);
}

void console::flush()
{
	output.setCursor(cursorX, cursorY);
}

void console::write(const char *word)
{
	/* While the pointed to char isn't 0 put it on display and move to the next char */
	while(*word)
	{
		put(*word);
		++word;
	}
}

console& console::operator<<(const int input)
{
	int number = input;
	if(number < 0)
	{
		put('-');
		number *= -1;
	}
	// HORRIBLE HACK
	// reverses the number so it comes out the right way round
	// need a stack implementation to do this nicely
	/*
	int temp = number;
	int length = 0;
	while(temp)
	{
		temp /= 10;
		++length;
	}
	*/
	// end horrible hack
	if(number)
	{
		while(number)
		{
			
			put('0'+number%10);
			number/=10;
		}
	}
	else
	{
		put('0');
	}
	return *this;
}

console& console::operator<<(const char character)
{
	put(character);
	return *this;
}

console& console::operator<<(const char *word)
{
	write(word);
	return *this;
}

console& console::operator<<(console& (*stream)(console&))
{
	return (*stream)(*this);
}

console& console::endl(console& stream)
{
	stream.put('\n');
	stream.flush();
	return stream;
}
