#include "PushableObject.h"
#include "Bunny.h"

PushableObject::PushableObject(int xPos, int yPos) : CollidingObject(xPos, yPos)
{ 
    model = CreteModelUsingChar('@',4,2);
}

void PushableObject::OnCollisionEnter(CollidingObject* other, Direction collisionDirection)
{
    if (collisionDirection == Direction::right || collisionDirection == Direction::left)
    {
        MoveContinuous(GetInverseDirection(collisionDirection), 9999);
        collidingDirections[static_cast<int>(collisionDirection)] = false;
    }
    else if (dynamic_cast<Bunny*>(other) == nullptr)
    {
        AudioManager::Instance().PlayFx("hit.wav", 0.2);
    }
    
}