#include "PongBar.h"
#include "InputUtils.h"

void PongBar::Update()
{
    if (isLeftBar)
    {
        if (InputUtils::IsPressingA() || InputUtils::IsPressingW())
            Move(Direction::up, moveSpeed);
        else if (InputUtils::IsPressingS() || InputUtils::IsPressingW())
            Move(Direction::down, moveSpeed);
    }
    else
    {
        if (InputUtils::IsPressingArrowUp() || InputUtils::IsPressingArrowLeft())
            Move(Direction::up, moveSpeed);
        else if (InputUtils::IsPressingArrowDown() || InputUtils::IsPressingArrowRight())
            Move(Direction::down, moveSpeed);
    }
}
