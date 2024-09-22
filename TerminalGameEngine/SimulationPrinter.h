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
	TerminalUtils& terminal = TerminalUtils::Instance();
	Frame frame;
	std::vector<Frame> backgrounds;

	string header = "";
	uint screenSizeX;
	uint screenSizeY;
	uint padding;
	bool isShowingUIMessage;
	Frame frameUIMessage;

	std::list<PrintOperation> printOperations;
	string printOperationBuffer;

	int screenMarginsColor = TerminalUtils::Instance().BLUE_DARK;
	int uiColor = TerminalUtils::WHITE;
	int backgroundColor = TerminalUtils::BLUE_DARK;

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


	void InsertHorizontalMarginLine();
	void InsertVerticalMarginChar(bool addEndLine);

	void InsertInPrintBuffer(string& str, int color);
	void InsertInPrintBuffer(char c, int color);
	void AddPrintBufferToOperations();

//---------------------------------------------------------- Debug
#if DEBUG_MODE
private:
	static constexpr double REFRESH_FPS_EVERY_SECONDS = 0.5;
	std::list<double> fpsRecord;
	double lastTimePrintedFps = 0;
	double shownAverageFps = 0;

	void DEBUG_PrintAverageFps();
#endif

};