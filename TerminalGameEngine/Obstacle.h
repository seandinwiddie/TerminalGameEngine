#pragma once

#include "MovingStraightObject.h"

class Obstacle : public MovingStraightObject
{
private:
    static Model model;
//---------------------------------------------------------- Methods
public:
    Obstacle(int xPos, int yPos, Direction moveDir, double moveSpeed);

    virtual bool CanExitScreenSpace() const override { return true; }
    virtual double GetGravityScale() const override { return 0; }
    virtual int GetColor() const { return Terminal::RED; }

protected:
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDir) override;
    virtual void OnCollisionExit(Direction endingCollisionDir) {}
    virtual void InitModel()
    { 
        if(model.size() == 0)
            model = CreteModelUsingChar(-37, size_t(4), size_t(2));
        SetModel(model);
    }
};