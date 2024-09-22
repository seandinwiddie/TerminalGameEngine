#pragma once
#include "Config.h"
#include "Frame.h"
#include "TerminalUtils.h"
#include <vector>
#include <list>
#include <string>

using string = std::string;

class GameObject;

class SimulationPrinter
{
//---------------------------------------------------------- Settings
private:
	static const char UI_MESSAGE_FRAME_IGNORED_CHAR = '#';
	static const int UI_COLOR = TerminalUtils::WHITE;
	static const int BACKGROUND_COLOR = TerminalUtils::BLUE_DARK;

	int screenMarginsColor = TerminalUtils::BLUE_DARK;
//---------------------------------------------------------- Fields
private:
	Frame frame;
	std::vector<Frame> backgrounds;

	string header = "";
	uint screenSizeX;
	uint screenSizeY;
	uint padding;
	bool isShowingUIMessage;
	Frame frameUIMessage;

//---------------------------------------------------------- Methods
public:
	SimulationPrinter
	(
		uint screenSizeX,
		uint screenSizeY,
		uint screenPadding,
		const std::vector<string>& backgroundFileNames = {}
	);

	void PrintFrameOnTerminal();

	void PrintObjectOnFrame(GameObject* go);
	void ClearFrame();

	void ShowUIFrame(const Frame& UIMessage){ this->frameUIMessage = UIMessage; }

	uint GetScreenSizeX() const { return screenSizeX; }
	uint GetScreenSizeY() const { return screenSizeY; }

	void SetHeader(const string& header) { this->header = header; }
	void SetMarginsColor(int color) { screenMarginsColor = color; }

private:
	void PrintUIMessageOnFrame();
	void InitBackgrounds(const std::vector<string>& backgroundFilesNames);
	Frame GetCurrentBackground() const;
	bool IsBackgroundEnabled() const { return backgrounds.size() > 0; }

	void InsertHorizontalMarginLine(string& toPrintBuffer, int& currentColor);
	void InsertVerticalMarginChar(string& toPrintBuffer, int& currentColor, bool addEndLine);
	void PrintBufferOnTerminal(string& toPrintBuffer);

//---------------------------------------------------------- Debug
#if DEBUG_MODE
private:
	static constexpr double REFRESH_FPS_EVERY_SECONDS = 0.5;
	std::list<double> fpsRecord;
	double lastTimePrintedFps = 0;
	double shownAverageFps = 0;

	void DEBUG_PrintAverageFps(string& frameString);
#endif

};