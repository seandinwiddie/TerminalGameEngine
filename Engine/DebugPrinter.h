#pragma once
#include "Printer.h"
#include "Terminal.h"

#include <iostream>
#include <string>

using string = std::string;

//todo add cpp file
class DebugPrinter : public Printer
{
//------------------------------------------ Settings
private:
    const int DEBUG_COLOR = Terminal::CYAN;
    const size_t FPS_POSITION = 1;
    const size_t POSITION_COUT_CALLS = 2;
    const size_t GENERIC_LOG_POSITION = 3;

//------------------------------------------ Methodss
public:
    using Printer::Printer;

public:
    void PrintCoutCallsCount(size_t coutCallsCount)
    {
        int startingColor = Terminal::Instance().GetColor();
        COORD cursorStartingPos = terminal.GetCursorPosition();

        Terminal::Instance().SetColor(DEBUG_COLOR);
        terminal.SetCursorPosition(0, GetMaxTerminalY() + POSITION_COUT_CALLS);
        //final space makes sure old string is cleared
        string output = "COUT CALLS: " + std::to_string(coutCallsCount) + string("     ");
        std::cout << output;

        terminal.SetCursorPosition(cursorStartingPos);
        terminal.SetColor(startingColor);
    }

    void PrintFpsString(size_t fps)
    {
        terminal.SetColor(DEBUG_COLOR);
        terminal.SetCursorPosition(0, GetMaxTerminalY() + FPS_POSITION);
        string output = "FPS: " + std::to_string(fps) + '\n';
        std::cout << output;
    }

    void PrintGenericLog(const string& log, int lineIndex)
    {
        terminal.SetColor(DEBUG_COLOR);
        terminal.SetCursorPosition(0, GetMaxTerminalY() + GENERIC_LOG_POSITION + lineIndex  );
        std::cout << log;
    }
};