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
//---------------------------------------------------------- Fields
private:
	Terminal& terminal = Terminal::Instance();
	std::vector<Frame> backgrounds;

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
		const std::vector<string>& backgroundFileNames = {}
	);

	//void PrintUI();
	void PrintObject(GameObject* obj);
	void Clear(int worldXPos, int worldYPos, uint xSize, uint ySize);

	void ShowUIFrame(const Frame& UIMessage){ this->frameUIMessage = UIMessage; }

	uint GetScreenSizeX() const { return screenSizeX; }
	uint GetScreenSizeY() const { return screenSizeY; }

	void SetHeader(const string& header) { this->header = header; }
	void SetMarginsColor(int color) { screenMarginsColor = color; }

	int GetScreenPos(int worldPos) const { return worldPos - padding; }

private:
	void PrintUIMessageOnFrame();
	void InitBackgrounds(const std::vector<string>& backgroundFilesNames);
	Frame GetCurrentBackground() const;
	bool IsBackgroundEnabled() const { return backgrounds.size() > 0; }

	//void InsertHorizontalMarginLine();
	//void InsertVerticalMarginChar(bool addEndLine);

//---------------------------------------------------------- Debug
#if DEBUG_MODE
private:
	static constexpr double REFRESH_FPS_EVERY_SECONDS = 0.5;
	std::list<double> fpsRecord;
	double lastTimePrintedFps = 0;
	double shownAverageFps = 0;

	//void DEBUG_PrintAverageFps();
#endif

};