#pragma once

#include "Config.h"
#include "VariableSizeCollider.h"

class AutomaticDoor : public VariableSizeCollider
{
//---------------------------------------------------------- Fields
private:
    static constexpr float MOVE_SPEED = 0.4;
    int startingPosY = -1;
    int energySourcesCounter = 0;

//---------------------------------------------------------- Methods
public:
    AutomaticDoor
    (
        const int xPos,
        const int yPos,
        const uint sizeX,
        const uint sizeY,
        const char modelChar
    );

    bool IsOpen() const { return energySourcesCounter > 0; }
    void AddEnergySource() { ++energySourcesCounter; }
    void RemoveEnergySource() { --energySourcesCounter; }
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }
    virtual void Update() override;

protected:
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) override {}
    virtual void OnCollisionExit(Direction collisionDirection) override {}
};