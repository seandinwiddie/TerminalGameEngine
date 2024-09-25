#pragma once
#include "Config.h"
#include "Frame.h"
#include "Terminal.h"
#include <vector>
#include <list>
#include <string>

using string = std::string;

class GameObject;

class SimulationPrinter
{
//---------------------------------------------------------- Settings
private:

	static const char GAME_OVER_FRAME_IGNORED_CHAR = '#';

	static const char MARGIN_HORIZONTAL_CHAR = '=';
	static const char MARGIN_VERTICAL_CHAR = '|';

	static const size_t MARGIN_OFFSET_X = 1; 
	static const size_t MARGIN_OFFSET_TOP_Y = 2; 
	static const size_t MARGIN_OFFSET_BOTTOM_Y = 1;

//---------------------------------------------------------- Fields
private:
	Terminal& terminal = Terminal::Instance();
	Frame background;

	size_t screenSizeX;
	size_t screenSizeY;
	size_t padding;

	int screenMarginsColor = Terminal::Instance().BLUE_DARK;
	int uiColor = Terminal::WHITE;
	int backgroundColor = Terminal::BLUE_DARK;

//---------------------------------------------------------- Methods
public:
	SimulationPrinter
	(
		size_t screenSizeX,
		size_t screenSizeY,
		size_t screenPadding,
		const string& backgroundFileName = ""
	);

	void PrintObject(GameObject* obj);
	void ClearObject(GameObject* obj);
	void ClearArea(int worldXPos, int worldYPos, size_t xSize, size_t ySize);

	void PrintGameOverWindow(const Frame& UIMessage);
	void SetHeader(const string& header);

	void SetMarginsColor(int color) { screenMarginsColor = color; }
	void SetUIColor(int color) { uiColor = color; }
	void SetBackgroundColor(int color) { backgroundColor = color; }

private:
	void PrintInternal(int worldXPos, int worldYPos, size_t xSize, size_t ySize, GameObject* go);
	void InitBackground(const string& backgroundFileName);
	void DrawMargins();
	void DrawHorizontalMargin();
	void PrintBackground();

	//used to count cout calls
	void Cout(const string& s);
	void Cout(char s);

	int GetScreenPos(int worldPos) const { return worldPos - static_cast<int>(padding); }
	size_t GetMaxTerminalX() const { return screenSizeX + MARGIN_OFFSET_X; }
	size_t GetMaxTerminalY() const { return screenSizeY + MARGIN_OFFSET_TOP_Y; }

//---------------------------------------------------------- Debug
#if DEBUG_MODE
private:
	const int DEBUG_COLOR = Terminal::CYAN;
	const size_t DEBUG_POSITION_FPS = 1;
	const size_t DEBUG_POSITION_COUT_CALLS = 2;
public:
	void DEBUG_PrintFpsString(size_t fps);
	void DEBUG_UpdateCoutCalls();
#endif

};