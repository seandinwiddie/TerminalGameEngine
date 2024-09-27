#pragma once
#include "Config.h"
#include "Frame.h"
#include "Terminal.h"
#include "Printer.h"
#include <vector>
#include <list>
#include <string>

using string = std::string;

class GameObject;

class SimulationPrinter : public Printer
{
//---------------------------------------------------------- Fields
	int backgroundColor;
	Frame background;
//---------------------------------------------------------- Methods
public:
	SimulationPrinter
	(
		size_t screenSizeX,
		size_t screenSizeY,
		size_t screenPadding,
		int backgroundColor,
		const string& backgroundFileName = ""
	);

	void PrintObject(GameObject* obj);
	void ClearObject(GameObject* obj);
	void ClearArea(int worldXPos, int worldYPos, size_t xSize, size_t ySize);

private:
	void PrintInternal(int worldXPos, int worldYPos, size_t xSize, size_t ySize, GameObject* go);
	void InitBackground(const string& backgroundFileName);
	void PrintBackground();
};