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
		u8int *buffer;
		u16int cursorX;
		u16int cursorY;
	public:
		screen(u8int *videoram);
		~screen();

/* functions to get information about the screen */
		u16int getSizeX();
		u16int getSizeY();
		u16int getCursorX();
		u16int getCursorY();
		u8int getChar(u16int posX, u16int posY);

/* functions to set things on the screen */
		void setChar(u16int posX, u16int posY, u8int character);
		void setColor(u16int posX, u16int posY, u16int foreColor, u16int backColor);
		void setChar(u16int posX, u16int posY, u8int character, u16int foreColor, u16int backColor);
		void setCursor(u16int posX, u16int posY);

/* shortcut functions to avoid calling above functions repeatedly */
		void clearToColor(u16int foreColor, u16int backColor);
		void clearColor();
		void clearChars();
		void clear();
		void scroll(u16int numRows);
};

#endif
