#include "PongBar.h"
#include "InputUtils.h"

void PongBar::Update()
{
    if (isLeftBar)
    {
        if (InputUtils::IsPressingA() || InputUtils::IsPressingS())
            Move(Direction::up, moveSpeed);
        else if (InputUtils::IsPressingD() || InputUtils::IsPressingW())
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
