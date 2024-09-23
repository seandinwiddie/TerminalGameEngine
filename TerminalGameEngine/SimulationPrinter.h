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
	struct PrintOperation
	{
		string str;
		int color;
		PrintOperation(const string& str, int color) :str(str), color(color) {}
	};

//---------------------------------------------------------- Settings
private:
	static const char UI_MESSAGE_FRAME_IGNORED_CHAR = '#';
	static const size_t MARGIN_OFFSET_X = 1; //left margin
	static const size_t MARGIN_OFFSET_TOP_Y = 2; //top margin + header
	static const size_t MARGIN_OFFSET_BOTTOM_Y = 1; //bottom margin

//---------------------------------------------------------- Fields
private:
	Terminal& terminal = Terminal::Instance();
	Frame background;

	size_t screenSizeX;
	size_t screenSizeY;
	size_t padding;
	bool isShowingUIMessage;

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

private:
	void PrintInternal(int worldXPos, int worldYPos, size_t xSize, size_t ySize, GameObject* go);
	void InitBackground(const string& backgroundFileName);
	void DrawMargins();
	void DrawHorizontalMargin();
	void PrintBackground();
	void Cout(const string& s);
	void Cout(char s);

	int GetScreenPos(int worldPos) const { return worldPos - padding; }
	size_t GetMaxTerminalX() const { return screenSizeX + MARGIN_OFFSET_X; }
	size_t GetMaxTerminalY() const { return screenSizeY + MARGIN_OFFSET_TOP_Y; }
	size_t GetTerminalPosX(int worldPosX)const { return GetScreenPos(worldPosX) + MARGIN_OFFSET_X; }
	size_t GetTerminalPosY(int worldPosY)const { return GetScreenPos(worldPosY) + MARGIN_OFFSET_TOP_Y; }

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