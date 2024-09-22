#include "TerminalUtils.h"
#include <windows.h>

const int TerminalUtils::WHITE_DARK = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN;
const int TerminalUtils::RED_DARK = FOREGROUND_RED;
const int TerminalUtils::GREEN_DARK = FOREGROUND_GREEN;
const int TerminalUtils::BLUE_DARK = FOREGROUND_BLUE;
const int TerminalUtils::CYAN_DARK = FOREGROUND_GREEN | FOREGROUND_BLUE;
const int TerminalUtils::MAGENTA_DARK = FOREGROUND_RED | FOREGROUND_BLUE;
const int TerminalUtils::YELLOW_DARK = FOREGROUND_RED | FOREGROUND_GREEN;

const int TerminalUtils::WHITE = WHITE_DARK | FOREGROUND_INTENSITY;
const int TerminalUtils::RED = RED_DARK | FOREGROUND_INTENSITY;
const int TerminalUtils::GREEN = GREEN_DARK | FOREGROUND_INTENSITY;
const int TerminalUtils::BLUE = BLUE_DARK | FOREGROUND_INTENSITY;
const int TerminalUtils::CYAN = CYAN_DARK | FOREGROUND_INTENSITY;
const int TerminalUtils::MAGENTA = MAGENTA_DARK | FOREGROUND_BLUE;
const int TerminalUtils::YELLOW = YELLOW_DARK | FOREGROUND_GREEN;

void TerminalUtils::ClearTerminal()
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

void TerminalUtils::SetColor(int color)
{
    currentColor = color;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void TerminalUtils::SetCursorPosition(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void TerminalUtils::HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false; // Hide cursor
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}