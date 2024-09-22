#pragma once
#include "Singleton.h"


class TerminalUtils : public Singleton<TerminalUtils>
{
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

public:
    void ClearTerminal();
    void SetColor(int color);
    inline int GetColor() { return currentColor; }
};