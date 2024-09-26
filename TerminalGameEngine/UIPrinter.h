#include "SimulationPrinter.h"
#include "Terminal.h"

class UIPrinter : public Printer
{
//---------------------------------------------------------- Fields
private:
	static const char GAME_OVER_FRAME_IGNORED_CHAR = '#';
	static const char MARGIN_HORIZONTAL_CHAR = '=';
	static const char MARGIN_VERTICAL_CHAR = '|';

//---------------------------------------------------------- Methods
public:
	UIPrinter(size_t screenSizeX, size_t screenSizeY, size_t screenPadding, int marginsColor);

	void PrintGameOverWindow (const Frame& UIMessage, int color);
	void PrintOnHeader(const string& header, int xPos, int color);

private:
	void DrawMargins(int color);
	void DrawHorizontalMargin();
};