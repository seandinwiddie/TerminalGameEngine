#pragma once
#include "VariableSizeCollider.h"

class AutomaticDoor : public VariableSizeCollider
{
//---------------------------------------------------------- Fields
private:
    static constexpr float MOVE_SPEED = 0.4;
    bool isOpen = false;
    int startingY = -1;

//---------------------------------------------------------- Methods
public:
    AutomaticDoor
    (
        const int xPos,
        const int yPos,
        const int sizeX,
        const int sizeY,
        const unsigned char modelChar
    );

    void SetOpen() { isOpen = true; }
    void SetClosed() { isOpen = false; }
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }
    virtual void Update() override;

protected:
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) override {}
    virtual void OnCollisionExit(Direction collisionDirection) override {}
};