#pragma once
#include "Config.h"
class Level;

class MainMenuUtils
{
//--------------------------------------------- Fields
private:
    static const char* colorCodes;
    static uint backgroundColorId;
    static uint foregroundColorId;

//--------------------------------------------- Methods
public:
    static void ChangeBackgroundColor();
    static void ChangeForegroundColor();
    static Level* ShowLevelSelection();

private:
    static void RefreshTerminalColor();
};