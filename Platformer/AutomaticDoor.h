#pragma once
#include "Config.h"
#include "VariableSizeCollider.h"

class AutomaticDoor : public VariableSizeCollider
{
//---------------------------------------------------------- Fields
private:
    double moveSpeed;
    int startingPosY;
    int energySourcesCounter = 0;

//---------------------------------------------------------- Methods
public:
    AutomaticDoor
    (
        int xPos,
        int yPos,
        size_t sizeX,
        size_t sizeY,
        char modelChar,
        double moveSpeed
    );

    bool IsOpen() const { return energySourcesCounter > 0; }
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::CYAN; }
    void AddEnergySource() { ++energySourcesCounter; }
    void RemoveEnergySource();

protected:
    virtual void Update() override;
};