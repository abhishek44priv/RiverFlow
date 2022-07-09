#pragma once
struct RfMouseEvent
{
	enum {
		B_LEFT, B_RIGHT, UNKNOWN, SCROLL_UP, SCROLL_DOWN
	};
	int x = 0, y = 0;
	int button = 0;
	int extraButton = 0;/*MK_CONTROL L|M|RBUTTON SHIFT*/
	int delta = 0;
};
struct RfSizeEvent
{
	int width = 0, height = 0;
	int flag = 0;
};
struct RfKeyEvent
{
	unsigned char key = 0;
};