#pragma once

#include "Config.h"
#include "VariableSizeCollider.h"

class AutomaticDoor : public VariableSizeCollider
{
//---------------------------------------------------------- Fields
private:
    static constexpr float MOVE_SPEED = 4;
    int startingPosY = -1;
    int energySourcesCounter = 0;

//---------------------------------------------------------- Methods
public:
    AutomaticDoor
    (
        int xPos,
        int yPos,
        uint sizeX,
        uint sizeY,
        char modelChar
    );

    bool IsOpen() const { return energySourcesCounter > 0; }
    void AddEnergySource() { ++energySourcesCounter; }
    void RemoveEnergySource();
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::CYAN; }

protected:
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) override {}
    virtual void OnCollisionExit(Direction collisionDirection) override {}
    virtual void Update() override;

    //todo check Update() is protected in all classes
};