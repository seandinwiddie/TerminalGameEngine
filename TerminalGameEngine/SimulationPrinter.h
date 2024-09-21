#pragma once
#include "Config.h"
#include "Frame.h"
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

//---------------------------------------------------------- Fields
private:
	Frame frame;
	std::vector<Frame> backgrounds;

	uint screenSizeX;
	uint screenSizeY;
	uint padding;
	bool showTimeUI = false;
	bool isShowingUIMessage;
	Frame frameUIMessage;

//---------------------------------------------------------- Methods
public:
	SimulationPrinter
	(
		uint screenSizeX,
		uint screenSizeY,
		uint screenPadding,
		bool showTimeUI,
		const std::vector<string>& backgroundFileNames = {}
	);

	void PrintFrameOnTerminal();

	void PrintObjectOnFrame(GameObject* go);
	void ClearFrame();

	void ShowUIFrame(const Frame& UIMessage){ this->frameUIMessage = UIMessage; }

	uint GetScreenSizeX() const { return screenSizeX; }
	uint GetScreenSizeY() const { return screenSizeY; }

private:
	void PrintUIMessageOnFrame();
	void InitBackgrounds(const std::vector<string>& backgroundFilesNames);
	Frame GetCurrentBackground() const;
	bool IsBackgroundEnabled() const { return backgrounds.size() > 0; }

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