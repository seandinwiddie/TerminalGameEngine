#pragma once
#include <windows.h>

namespace TerminalUtils
{

    const static int BG_WHITE = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
    const static int BG_RED = FOREGROUND_RED;
    const static int BG_GREEN = FOREGROUND_GREEN;
    const static int BG_BLUE = FOREGROUND_BLUE;

    const static int FG_WHITE = BG_WHITE | FOREGROUND_INTENSITY;
    const static int FG_RED = BG_RED | FOREGROUND_INTENSITY;
    const static int FG_GREEN = BG_GREEN | FOREGROUND_INTENSITY;
    const static int FG_BLUE = BG_BLUE | FOREGROUND_INTENSITY;
    
    inline void ClearTerminal()
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord = { 0, 0 };  // Top left corner
        DWORD cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD dwConSize;

        // Get the console screen buffer info
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

        // Fill the entire screen with spaces
        FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coord, &cCharsWritten);

        // Fill the entire screen with the current attributes
        GetConsoleScreenBufferInfo(hConsole, &csbi);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coord, &cCharsWritten);

        // Move the cursor back to the top-left corner
        SetConsoleCursorPosition(hConsole, coord);
    }

    inline void SetColor(int color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
}