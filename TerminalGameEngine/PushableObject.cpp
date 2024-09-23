#include "PushableObject.h"
#include "Bunny.h"

PushableObject::PushableObject(int xPos, int yPos) : CollidingObject(xPos, yPos)
{ 
   SetModel(CreteModelUsingChar('@',4,2));
}

void PushableObject::OnCollisionEnter(CollidingObject* other, Direction collisionDirection)
{
    if (collisionDirection == Direction::right || collisionDirection == Direction::left)
    {
        Move(GetInverseDirection(collisionDirection), 9999);
        collidingDirections[static_cast<int>(collisionDirection)] = false;
    }
    else if (dynamic_cast<Bunny*>(other) == nullptr)
    {
        AudioManager::Instance().PlayFx("Platform/hit.wav", 0.2);
    }
    
}