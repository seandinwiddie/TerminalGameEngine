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
	static constexpr double REFRESH_FPS_EVERY_SECONDS = 0.5;
	std::list<double> fpsRecord;
	double lastTimePrintedFps = 0;
	double shownAverageFps = 0;
	int debugColor = Terminal::CYAN;

	int coutCalls = 0;

public:
	void DEBUG_PrintAverageFps();
private:
	void DEBUG_IncreaseCoutCallsCount();
#endif

};