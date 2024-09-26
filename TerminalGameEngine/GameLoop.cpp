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
#include "SpaceInvadersLevel.h"

using namespace std;
using namespace InputUtils;

GameLoop::GameLoop()
{
    bool returnToMainMenu = false;

    while (true)
    {
        AudioManager::Instance().StopMusic();
        Level* level = ShowLevelSelection();
        while (true)
        {
           returnToMainMenu = LoopSimulation(level);
           if (returnToMainMenu)
               break;
        }

        delete(level);
    }
}

bool GameLoop::LoopSimulation(Level* level)
{
    Simulation::Instance().LoadLevel(level);
    while (level->IsTerminated() == false)
    {
        Simulation::Instance().Step();
        if (IsKeyPressed(Key::ESC))
            return true;
    }
    return false;
}

Level* GameLoop::ShowLevelSelection()
{
    Terminal::Instance().Clear();
    Terminal::Instance().SetColor(Terminal::WHITE);
    cout << "Press:" << endl
         << "1 -> play space invaders demo" << endl
         << "2 -> play endless runner demo" << endl
         << "3 -> play puzzle game demo" << endl
         << "4 -> play pong game demo" << endl
         << "5 -> collisions test" << endl
         << endl
         << "esc (inside levels) -> return to main menu" << endl
         << endl
         << "Music by 'Cody O'Quinn'" << endl;

    while (true)
    {
        if (IsKeyPressed(Key::NUM_1))
        {
            return new SpaceInvadersLevel();
            break;
        }
        else if (IsKeyPressed(Key::NUM_2))
        {
            return new EndlessRunnerLevel();
            break;
        }
        else if (IsKeyPressed(Key::NUM_3))
        {
            return new PuzzleLevel();
            break;
        }
        else if (IsKeyPressed(Key::NUM_4))
        {
            return new PongLevel();
            break;
        }
        else if (IsKeyPressed(Key::NUM_5))
        {
            return new CollisionsTestLevel();
            break;
        }
    }
}