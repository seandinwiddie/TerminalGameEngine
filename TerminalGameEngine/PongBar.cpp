#include "PongBar.h"
#include "InputUtils.h"
#include "Simulation.h"

void PongBar::Update()
{
    if (Simulation::Instance().GetActiveLevel()->IsGameOver())
        return;
    
    if (isLeftBar)
    {
        if (InputUtils::IsPressingA())
            Move(Direction::left, moveSpeed);
        else if (InputUtils::IsPressingD())
            Move(Direction::right, moveSpeed);
    }
    else
    {
        if (InputUtils::IsPressingArrowLeft())
            Move(Direction::left, moveSpeed);
        else if (InputUtils::IsPressingArrowRight())
            Move(Direction::right, moveSpeed);
    }
}
