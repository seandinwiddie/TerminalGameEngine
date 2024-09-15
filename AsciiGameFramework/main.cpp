#include "Config.h"

#include "Level.h";
#include "MainMenuUtils.h"
#include "Simulation.h"
#include "InputUtils.h"
#include "AudioManager.h"
#include "RepeatedCollisionTestLevel.h"

//void FastCollisionsTest()
//{
//        RepeatedCollisionTestLevel level;
//        level.Load();
//        while (true)
//            Simulation::Instance().Step();
//}

int main()
{
    system("COLOR 0A");

    Simulation& simulation = Simulation::Instance();
    bool returnToMainMenu = false;

    while (true)
    {
        AudioManager::Instance().StopMusic();

        

        Level* level = MainMenuUtils::ShowLevelSelection();
        returnToMainMenu = false;

       
        level->Load();

        while (returnToMainMenu == false)
        {
            level->Load();

            //step simulation until it ends
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

    return 0;
}