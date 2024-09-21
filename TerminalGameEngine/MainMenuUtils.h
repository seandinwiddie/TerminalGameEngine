#pragma once
#include "Config.h"
#include "EndlessRunnerLevel.h"
#include "PuzzleLevel.h"
#include "TerminalUtils.h"
#include "InputUtils.h"
class Level;

namespace MainMenuUtils
{
    inline Level* ShowLevelSelection()
    {
        TerminalUtils::ClearTerminal();
        TerminalUtils::SetColor(TerminalUtils::WHITE);
        std::cout
            << "Press:" << std::endl
            << "1 -> play endless runner demo" << std::endl
            << "2 -> play puzzle game demo" << std::endl << std::endl
            << "esc (inside levels) -> main menu" << std::endl;

        while (true)
        {
            if (InputUtils::IsPressing1())
            {
                return new EndlessRunnerLevel();
                break;
            }
            if (InputUtils::IsPressing2())
            {
                return new PuzzleLevel();
                break;
            }
        }
    }
};