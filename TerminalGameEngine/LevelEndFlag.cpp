#include "LevelEndFlag.h"
#include "Bunny.h"
#include "Level.h"

const std::vector<std::vector<char>> LevelEndFlag::flagModel
{
     {'|',' '},
     {'|','/'},
     {'|','\\'}
};

LevelEndFlag::LevelEndFlag(Level* level, int xPos, int yPos) : CollidingObject(xPos, yPos), level(level)
{
    model = flagModel;
}

void LevelEndFlag::OnCollisionEnter(CollidingObject* other, Direction collisionDirection)
{
    if (static_cast<Bunny*>(other) != nullptr)
    {
        level->OnGameOver();
    }
}