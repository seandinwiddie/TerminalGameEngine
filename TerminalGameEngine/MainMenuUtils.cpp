#include "MainMenuUtils.h"

#include "Level.h";
#include "PuzzleLevel.h"
#include "ObstaclesLevel.h"
#include "InputUtils.h"
#include "SimulationPrinter.h"
#include "RandomUtils.h"

#include <iostream>

    const char* MainMenuUtils::colorCodes = "0123456789ABCDEF";
    uint MainMenuUtils::backgroundColorId = 0;
    uint MainMenuUtils::foregroundColorId = 0;

    void MainMenuUtils::RefreshTerminalColor()
    {
        char backgroundChar = colorCodes[backgroundColorId];
        char foregroundChar = colorCodes[foregroundColorId];
        std::string colorCode = "color ";
        colorCode += backgroundChar;
        colorCode += foregroundChar;
        system(colorCode.c_str());
    }

    void MainMenuUtils::ChangeBackgroundColor()
    {
        uint previousColorId = backgroundColorId;
        while (backgroundColorId == foregroundColorId || backgroundColorId == previousColorId)
            backgroundColorId = RandomUtils::GetRandomInt(0, 15);
        RefreshTerminalColor();
    }

    void MainMenuUtils::ChangeForegroundColor()
    {
        uint previousColorId = foregroundColorId;
        while (foregroundColorId == backgroundColorId || foregroundColorId == previousColorId)
            foregroundColorId = RandomUtils::GetRandomInt(0, 15);
        RefreshTerminalColor();
    }

    Level* MainMenuUtils::ShowLevelSelection()
    {
        SimulationPrinter::ClearTerminal();
        std::cout
            << "Press:" << std::endl
            << "1 -> play endless runner demo" << std::endl
            << "2 -> play puzzle game demo" << std::endl << std::endl
            << "esc (inside levels) -> main menu" << std::endl
            << "9 -> change background color" << std::endl
            << "0 -> change foreground color" << std::endl;

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

