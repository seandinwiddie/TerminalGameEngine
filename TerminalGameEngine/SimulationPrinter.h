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
	static const uint MARGIN_OFFSET_X = 1; //left margin
	static const uint MARGIN_OFFSET_Y = 1; //top margin

//---------------------------------------------------------- Fields
private:
	Terminal& terminal = Terminal::Instance();
	Frame background;

	string header = "";
	uint screenSizeX;
	uint screenSizeY;
	uint padding;
	bool isShowingUIMessage;
	Frame frameUIMessage;

	int screenMarginsColor = Terminal::Instance().BLUE_DARK;
	int uiColor = Terminal::WHITE;
	int backgroundColor = Terminal::BLUE_DARK;

//---------------------------------------------------------- Methods
public:
	SimulationPrinter
	(
		uint screenSizeX,
		uint screenSizeY,
		uint screenPadding,
		const string& backgroundFileName = ""
	);

	//void PrintUI();
	void PrintObject(GameObject* obj);
	void Clear(GameObject* obj);
	void Clear(int worldXPos, int worldYPos, uint xSize, uint ySize);

	void ShowUIFrame(const Frame& UIMessage){ this->frameUIMessage = UIMessage; }

	uint GetMaxTerminalX() const { return screenSizeX + MARGIN_OFFSET_X; }
	uint GetMaxTerminalY() const { return screenSizeY + MARGIN_OFFSET_Y; }

	void SetHeader(const string& header) { this->header = header; }
	void SetMarginsColor(int color) { screenMarginsColor = color; }

	int GetScreenPos(int worldPos) const { return worldPos - padding; }

private:
	void PrintUIMessageOnFrame();
	void InitBackgrounds(const string& backgroundFileName);
	void DrawMargins();
	void DrawHorizontalMargin();
	void PrintBackground();

//---------------------------------------------------------- Debug
#if DEBUG_MODE
private:
	static constexpr double REFRESH_FPS_EVERY_SECONDS = 0.5;
	std::list<double> fpsRecord;
	double lastTimePrintedFps = 0;
	double shownAverageFps = 0;

#endif

};