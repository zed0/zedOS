#include "screen.h"

screen::screen(u8int *videoram)
{
	buffer = videoram;
	cursorX = 0;
	cursorY = 0;
}

screen::~screen()
{
}

u16int screen::getSizeX()
{
	return SCREEN_MAX_X;
}

u16int screen::getSizeY()
{
	return SCREEN_MAX_Y;
}

u16int screen::getCursorX()
{
	return cursorX;
}

u16int screen::getCursorY()
{
	return cursorY;
}

u8int screen::getChar(u16int posX, u16int posY)
{
	if(posX <SCREEN_MAX_X && posY < SCREEN_MAX_Y)
	{
		u16int truePos = (posX + SCREEN_MAX_X * posY) * 2;
		return buffer[truePos];
	}
	else
	{
		return '\0';
	}
}

void screen::setChar(u16int posX, u16int posY, u8int character)
{
	if(posX < SCREEN_MAX_X && posY < SCREEN_MAX_Y)
	{
		u16int truePos = (posX + SCREEN_MAX_X * posY) * 2; // x2 as each is described by 2 bytes
		buffer[truePos] = character;
	}
}

void screen::setColor(u16int posX, u16int posY, u16int foreColor, u16int backColor)
{
	if(posX < SCREEN_MAX_X && posY < SCREEN_MAX_Y)
	{
		u16int truePos = (posX + SCREEN_MAX_X * posY) * 2; // x2 as each is described by 2 bytes
		buffer[truePos+1] = (foreColor << 4) + backColor;
	}
}

void screen::setChar(u16int posX, u16int posY, u8int character, u16int foreColor, u16int backColor)
{
	setChar(posX, posY, character);
	setColor(posX, posY, foreColor, backColor);
}

void screen::setCursor(u16int posX, u16int posY)
{
	/* Use the hardware cursor */
	/* Cursor location is sent in high bit, then low bit format using 0x3D4 to specify */
	/* which bit is being sent (14 for high bit, 15 for low bit */
	/* The actual bits are sent on 0x3D5 */
	u16int truePos = posX + SCREEN_MAX_X * posY;
	outb(0x3D4, 14);
	outb(0x3D5, truePos >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, truePos);
}

void screen::clearToColor(u16int foreColor, u16int backColor)
{
	for(u16int i=0; i<SCREEN_MAX_X; ++i)
	{
		for(u16int j=0; j<SCREEN_MAX_Y; ++j)
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
	for(u16int i=0; i<SCREEN_MAX_X; ++i)
	{
		for(u16int j=0; j<SCREEN_MAX_Y; ++j)
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

void screen::scroll(u16int numRows)
{
	/* Set each character to the one numRows beneath it */
	for(u16int y=0; y<SCREEN_MAX_Y-numRows; ++y)
	{
		for(u16int x=0; x<SCREEN_MAX_X; ++x)
		{
			setChar(x, y, getChar(x, y+numRows));
		}
	}
	/* Fill the new lines with spaces */
	for(u16int y=SCREEN_MAX_Y-numRows; y<SCREEN_MAX_Y; ++y)
	{
		for(u16int x=0; x<SCREEN_MAX_X; ++x)
		{
			setChar(x, y, ' ');
		}
	}
}
