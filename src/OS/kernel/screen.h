#ifndef SCREEN_H
#define SCREEN_H

#include "common.h"

#define SCREEN_MAX_X 80
#define SCREEN_MAX_Y 25

#define DEFAULT_FORE_COLOR 0
#define DEFAULT_BACK_COLOR 7
class screen
{
	private:
		unsigned char *buffer;
		unsigned short cursorX;
		unsigned short cursorY;
	public:
		screen(unsigned char *videoram);
		~screen();

/* functions to get information about the screen */
		unsigned short getSizeX();
		unsigned short getSizeY();
		unsigned short getCursorX();
		unsigned short getCursorY();
		unsigned char getChar(unsigned short posX, unsigned short posY);

/* functions to set things on the screen */
		void setChar(unsigned short posX, unsigned short posY, char character);
		void setColor(unsigned short posX, unsigned short posY, unsigned short foreColor, unsigned short backColor);
		void setChar(unsigned short posX, unsigned short posY, char character, unsigned short foreColor, unsigned short backColor);
		void setCursor(unsigned short posX, unsigned short posY);

/* shortcut functions to avoid calling above functions repeatedly */
		void clearToColor(unsigned short foreColor, unsigned short backColor);
		void clearColor();
		void clearChars();
		void clear();
		void scroll(unsigned short numRows);
};

#endif
