#include "screen.h"

screen::screen(unsigned char *videoram)
{
	buffer = videoram;
	cursorX = 0;
	cursorY = 0;
}

screen::~screen()
{
}

unsigned short screen::getSizeX()
{
	return SCREEN_MAX_X;
}

unsigned short screen::getSizeY()
{
	return SCREEN_MAX_Y;
}

unsigned short screen::getCursorX()
{
	return cursorX;
}

unsigned short screen::getCursorY()
{
	return cursorY;
}

unsigned char screen::getChar(unsigned short posX, unsigned short posY)
{
	if(posX <SCREEN_MAX_X && posY < SCREEN_MAX_Y)
	{
		unsigned short truePos = (posX + SCREEN_MAX_X * posY) * 2;
		return buffer[truePos];
	}
	else
	{
		return '\0';
	}
}

void screen::setChar(unsigned short posX, unsigned short posY, char character)
{
	if(posX < SCREEN_MAX_X && posY < SCREEN_MAX_Y)
	{
		unsigned short truePos = (posX + SCREEN_MAX_X * posY) * 2; // x2 as each is described by 2 bytes
		buffer[truePos] = character;
	}
}

void screen::setColor(unsigned short posX, unsigned short posY, unsigned short foreColor, unsigned short backColor)
{
	if(posX < SCREEN_MAX_X && posY < SCREEN_MAX_Y)
	{
		unsigned short truePos = (posX + SCREEN_MAX_X * posY) * 2; // x2 as each is described by 2 bytes
		buffer[truePos+1] = (foreColor << 4) + backColor;
	}
}

void screen::setChar(unsigned short posX, unsigned short posY, char character, unsigned short foreColor, unsigned short backColor)
{
	setChar(posX, posY, character);
	setColor(posX, posY, foreColor, backColor);
}

void screen::setCursor(unsigned short posX, unsigned short posY)
{
	/* Use the hardware cursor */
	/* Cursor location is sent in high bit, then low bit format using 0x3D4 to specify */
	/* which bit is being sent (14 for high bit, 15 for low bit */
	/* The actual bits are sent on 0x3D5 */
	unsigned short truePos = posX + SCREEN_MAX_X * posY;
	outb(0x3D4, 14);
	outb(0x3D5, truePos >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, truePos);
}

void screen::clearToColor(unsigned short foreColor, unsigned short backColor)
{
	for(unsigned short i=0; i<SCREEN_MAX_X; ++i)
	{
		for(unsigned short j=0; j<SCREEN_MAX_Y; ++j)
		{
			setColor(i, j, foreColor, backColor);
		}
	}
}

void screen::clearColor()
{
	clearToColor(DEFAULT_FORE_COLOR, DEFAULT_BACK_COLOR);
}

void screen::clearChars()
{
	for(unsigned short i=0; i<SCREEN_MAX_X; ++i)
	{
		for(unsigned short j=0; j<SCREEN_MAX_Y; ++j)
		{
			setChar(i, j, ' ');
		}
	}
}

void screen::clear()
{
	clearChars();
	clearColor();
}

void screen::scroll(unsigned short numRows)
{
	/* Set each character to the one numRows beneath it */
	for(unsigned short y=0; y<SCREEN_MAX_Y-numRows; ++y)
	{
		for(unsigned short x=0; x<SCREEN_MAX_X; ++x)
		{
			setChar(x, y, getChar(x, y+numRows));
		}
	}
	/* Fill the new lines with spaces */
	for(unsigned short y=SCREEN_MAX_Y-numRows; y<SCREEN_MAX_Y; ++y)
	{
		for(unsigned short x=0; x<SCREEN_MAX_X; ++x)
		{
			setChar(x, y, ' ');
		}
	}
}
