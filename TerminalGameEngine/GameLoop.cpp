#include "GameLoop.h"
#include "Config.h"
#include "EndlessRunnerLevel.h"
#include "PuzzleLevel.h"
#include "Terminal.h"
#include "CollisionsTestLevel.h"
#include "PongLevel.h"
#include "InputUtils.h"
#include "AudioManager.h"
#include "Simulation.h"

GameLoop::GameLoop()
{
    AudioManager& audioManager = AudioManager::Instance();
    Simulation& simulation = Simulation::Instance();
    bool returnToMainMenu = false;

    while (true)
    {
        audioManager.StopMusic();
        Level* level = ShowLevelSelection();
        returnToMainMenu = false;

        while (returnToMainMenu == false)
        {
            simulation.LoadLevel(level);

            while (level->IsTerminated() == false)
            {
                simulation.Step();

                if (InputUtils::IsPressingEsc())
                {
                    returnToMainMenu = true;
                    break;
                }
            }
        }
        delete(level);
    }
}

Level* GameLoop::ShowLevelSelection()
{
    Terminal::Instance().Clear();
    Terminal::Instance().SetColor(Terminal::WHITE);
    std::cout
        << "Press:" << std::endl
        << "1 -> play endless runner demo" << std::endl
        << "2 -> play puzzle game demo" << std::endl
        << "3 -> play pong game demo" << std::endl
        << "4 -> collisions test" << std::endl
        << std::endl
        << "esc (inside levels) -> return to main menu" << std::endl
        << std::endl
        << "All music by 'Cody O'Quinn'" << std::endl;

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
        if (InputUtils::IsPressing3())
        {
            return new PongLevel();
            break;
        }
        if (InputUtils::IsPressing4())
        {
            return new CollisionsTestLevel();
            break;
        }
    }
}