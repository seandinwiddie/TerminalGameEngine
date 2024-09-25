#pragma once

#include "Config.h"
#include "VariableSizeCollider.h"

class AutomaticDoor : public VariableSizeCollider
{
//---------------------------------------------------------- Fields
private:
    static constexpr double MOVE_SPEED = 4;
    int startingPosY = -1;
    int energySourcesCounter = 0;

//---------------------------------------------------------- Methods
public:
    AutomaticDoor
    (
        int xPos,
        int yPos,
        size_t sizeX,
        size_t sizeY,
        char modelChar
    );

    bool IsOpen() const { return energySourcesCounter > 0; }
    void AddEnergySource() { ++energySourcesCounter; }
    void RemoveEnergySource();
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::CYAN; }

protected:
    virtual void OnCollisionEnter(uset<GameObject*>collidingObjects, Direction collisionDir) override {}
    virtual void OnCollisionExit(Direction endingCollisionDir) override {}
    virtual void Update() override;
};