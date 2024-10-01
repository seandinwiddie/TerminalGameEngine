#pragma once
#include "Config.h"
#include "Frame.h"
#include "Terminal.h"
#include "Printer.h"
#include <vector>
#include <list>
#include <string>

using string = std::string;

class KinematicObject;

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

	void PrintObject(KinematicObject* obj);
	void ClearObject(KinematicObject* obj);
	void ClearArea(int worldXPos, int worldYPos, size_t xSize, size_t ySize);

private:
	void PrintInternal(int worldXPos, int worldYPos, size_t xSize, size_t ySize, KinematicObject* go);
	void InitBackground(const string& backgroundFileName);
	void PrintBackground();
};