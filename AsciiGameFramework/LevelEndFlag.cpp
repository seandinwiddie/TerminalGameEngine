#include "LevelEndFlag.h"
#include "Bunny.h"
#include "Level.h"

const std::vector<std::vector<unsigned char>> LevelEndFlag::flagModel
{
     {'|',' '},
     {'|','/'},
     {'|','\\'}
};

LevelEndFlag::LevelEndFlag(Level* level, const int x, const int y) : CollidingObject(x, y), level(level)
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