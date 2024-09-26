#pragma once
#include "Printer.h"
#include "Terminal.h"

#include <iostream>
#include <string>

using string = std::string;

class DebugPrinter : public Printer
{
//------------------------------------------ Settings
private:
    const int DEBUG_COLOR = Terminal::CYAN;
    const size_t DEBUG_POSITION_FPS = 1;
    const size_t DEBUG_POSITION_COUT_CALLS = 2;

//------------------------------------------ Methodss
public:
    DebugPrinter
    (
        size_t screenSizeX,
        size_t screenSizeY,
        size_t screenPadding
    ) : Printer(screenSizeX, screenSizeY, screenPadding){ }


public:
    void PrintCoutCallsCount(size_t coutCallsCount)
    {
        int startingColor = Terminal::Instance().GetColor();
        COORD cursorStartingPos = terminal.GetCursorPosition();

        Terminal::Instance().SetColor(DEBUG_COLOR);
        terminal.SetCursorPosition(0, GetMaxTerminalY() + DEBUG_POSITION_COUT_CALLS);
        //final space makes sure old string is cleared
        string output = "COUT CALLS: " + std::to_string(coutCallsCount) + string("     ");
        std::cout << output;

        terminal.SetCursorPosition(cursorStartingPos);
        terminal.SetColor(startingColor);
    }

    void PrintFpsString(size_t fps)
    {
        terminal.SetColor(DEBUG_COLOR);
        terminal.SetCursorPosition(0, GetMaxTerminalY() + DEBUG_POSITION_FPS);
        string output = "FPS: " + std::to_string(fps) + '\n';
        std::cout << output;
    }
};