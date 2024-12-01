#pragma once
#include "Config.h"
#include "Frame.h"
#include "Terminal.h"
#include "Printer.h"
#include <list>
#include <string>
#include <memory>

namespace Engine
{
	template<typename T> using shared_ptr = std::shared_ptr<T>;
	using string = std::string;
	class GameObject;
	class Frame;

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
			const char* backgroundFileName = ""
		);

		void PrintObject(shared_ptr<GameObject> obj);
		void ClearObject(shared_ptr<GameObject> obj);
		void ClearArea(int worldXPos, int worldYPos, size_t xSize, size_t ySize);

	private:
		void PrintInternal(int worldXPos, int worldYPos, size_t xSize, size_t ySize, shared_ptr<GameObject> go);
		void InitBackground(const char* backgroundFileName);
		void PrintBackground();
	};
}