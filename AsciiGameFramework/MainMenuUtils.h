#pragma once

#include "Config.h"
#include "Level.h";
#include "PuzzleLevel.h"
#include "ObstaclesLevel.h"
#include "InputUtils.h"
#include "ScreenManager.h"
#include "RandomUtils.h"

#include <iostream>

using namespace std;

namespace MainMenuUtils
{
    static const char* colorCodes = "0123456789ABCDEF";
    static uint backgroundColorId;
    static uint foregroundColorId;

    static void RefreshTerminalColor()
    {
        char backgroundChar = colorCodes[backgroundColorId];
        char foregroundChar = colorCodes[foregroundColorId];
        std::string colorCode = "color ";
        colorCode += backgroundChar;
        colorCode += foregroundChar;
        system(colorCode.c_str());
    }

    static void ChangeBackgroundColor()
    {
        uint previousColorId = backgroundColorId;
        while (backgroundColorId == foregroundColorId || backgroundColorId == previousColorId)
            backgroundColorId = RandomUtils::GetRandomInt(0, 15);
        RefreshTerminalColor();
    }

    static void ChangeForegroundColor()
    {
        uint previousColorId = foregroundColorId;
        while (foregroundColorId == backgroundColorId || foregroundColorId == previousColorId)
            foregroundColorId = RandomUtils::GetRandomInt(0, 15);
        RefreshTerminalColor();
    }

    static Level* ShowLevelSelection()
    {
        ScreenManager::ClearTerminal();
        cout
            << "Press:" << endl
            << "1 -> play endless runner demo" << endl
            << "2 -> play puzzle game demo" << endl << endl
            << "esc (inside levels) -> main menu" << endl
            << "9 -> change background color" << endl
            << "0 -> change foreground color" << endl;

        while (true)
        {
            if (InputUtils::IsPressing1())
            {
                return new ObstaclesLevel();
                break;
            }
            if (InputUtils::IsPressing2())
            {
                return new PuzzleLevel();
                break;
            }
            if (InputUtils::IsPressing9())
            {
                ChangeBackgroundColor();
                Sleep(200);
            }
            if (InputUtils::IsPressing0())
            {
                ChangeForegroundColor();
                Sleep(200);
            }
        }
    }
}