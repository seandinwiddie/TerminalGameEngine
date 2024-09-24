#pragma once
#include "Singleton.h"
#include <Windows.h>

class Terminal : public Singleton<Terminal>
{
friend class Singleton;

//---------------------------------------------------------- Fields
public:
    const static int WHITE_DARK;
    const static int RED_DARK;
    const static int GREEN_DARK;
    const static int BLUE_DARK;
    const static int CYAN_DARK;
    const static int MAGENTA_DARK;
    const static int YELLOW_DARK;

    const static int WHITE;
    const static int RED;
    const static int GREEN;
    const static int BLUE;
    const static int CYAN;
    const static int MAGENTA;
    const static int YELLOW;

private:
    int currentColor;

//---------------------------------------------------------- Fields
public:
    void Clear();
    void SetColor(int color);
    int GetColor() { return currentColor; }
    void SetCursorPosition(const COORD& coord);
    void SetCursorPosition(size_t x, size_t y);
    COORD GetCursorPosition();

protected:
    Terminal(){HideCursor();}

private:
    void HideCursor();
};