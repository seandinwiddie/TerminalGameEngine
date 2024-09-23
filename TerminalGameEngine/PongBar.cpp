#include "PongBar.h"
#include "InputUtils.h"
#include "Simulation.h"

void PongBar::Update()
{
    if (Simulation::Instance().GetActiveLevel()->IsGameOver())
        return;
    
    if ((isBottomBar && InputUtils::IsPressingA()) || !isBottomBar && InputUtils::IsPressingArrowLeft())
        Move(Direction::left, moveSpeed);
    else if ((isBottomBar && InputUtils::IsPressingD()) || (!isBottomBar && InputUtils::IsPressingArrowRight()))
        Move(Direction::right, moveSpeed);
}
