#include "SimulationPrinter.h"
#include "Terminal.h"

class UIPrinter : public Printer
{
private:
	static const char GAME_OVER_FRAME_IGNORED_CHAR = '#';

	static const char MARGIN_HORIZONTAL_CHAR = '=';
	static const char MARGIN_VERTICAL_CHAR = '|';

	int screenMarginsColor = Terminal::BLUE_DARK;

public:
	UIPrinter(size_t screenSizeX, size_t screenSizeY, size_t screenPadding);

	void PrintGameOverWindow (const Frame& UIMessage, int color);
	void PrintOnHeader(const string& header, int xPos, int color);
	void SetMarginsColor(int color) { screenMarginsColor = color; }

private:
	void DrawMargins();
	void DrawHorizontalMargin();
};