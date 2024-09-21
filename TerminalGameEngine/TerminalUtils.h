#pragma once
#include <windows.h>

namespace TerminalUtils
{

    const static int WHITE_DARK = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
    const static int RED_DARK = FOREGROUND_RED;
    const static int GREEN_DARK = FOREGROUND_GREEN;
    const static int BLUE_DARK = FOREGROUND_BLUE;
    const static int CYAN_DARK = FOREGROUND_GREEN | FOREGROUND_BLUE;
    const static int MAGENTA_DARK = FOREGROUND_RED | FOREGROUND_BLUE;
    const static int YELLOW_DARK = FOREGROUND_RED | FOREGROUND_GREEN;

    const static int WHITE = WHITE_DARK | FOREGROUND_INTENSITY;
    const static int RED = RED_DARK | FOREGROUND_INTENSITY;
    const static int GREEN = GREEN_DARK | FOREGROUND_INTENSITY;
    const static int BLUE = BLUE_DARK | FOREGROUND_INTENSITY;
    const static int CYAN = CYAN_DARK | FOREGROUND_INTENSITY;
    const static int MAGENTA = MAGENTA_DARK | FOREGROUND_BLUE;
    const static int YELLOW = YELLOW_DARK | FOREGROUND_GREEN;
    

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