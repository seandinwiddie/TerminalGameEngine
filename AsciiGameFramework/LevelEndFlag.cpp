#include "LevelEndFlag.h"
#include "Bunny.h"

const std::vector<std::vector<unsigned char>> LevelEndFlag::flagModel
{
     {'|',' '},
     {'|','/'},
     {'|','\\'}
};

LevelEndFlag::LevelEndFlag(const int x, const int y) : CollidingObject(x, y)
{
    model = flagModel;
}

void LevelEndFlag::OnCollisionEnter(CollidingObject* other, Direction collisionDirection)
{
    if (static_cast<Bunny*>(other) != nullptr)
    {
        Simulation::Instance().NotifyGameOver(true);
    }
}