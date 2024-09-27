#pragma once
#include "Terminal.h"

class Printer
{
//---------------------------------------------------------- Margins
protected:
	static const size_t MARGIN_OFFSET_X = 1;
	static const size_t MARGIN_OFFSET_TOP_Y = 2;
	static const size_t MARGIN_OFFSET_BOTTOM_Y = 1;

//---------------------------------------------------------- Fields
protected:
	size_t screenSizeX;
	size_t screenSizeY;
	size_t padding;

	Terminal& terminal = Terminal::Instance();

//---------------------------------------------------------- Methods
public:
	Printer
	(
		size_t screenSizeX,
		size_t screenSizeY,
		size_t screenPadding
	) :
		screenSizeX(screenSizeX),
		screenSizeY(screenSizeY),
		padding(screenPadding)
	{ }

	size_t GetMaxTerminalX() const { return screenSizeX + MARGIN_OFFSET_X; }
	size_t GetMaxTerminalY() const { return screenSizeY + MARGIN_OFFSET_TOP_Y; }

protected:
	int ConvertWorldPosToScreenPos(int worldPos) const { return worldPos - static_cast<int>(padding); }
};