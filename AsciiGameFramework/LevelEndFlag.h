#pragma once
#include "GameObject.h"


class LevelEndFlag : public GameObject
{
private:
    const std::vector<std::vector<unsigned char>> flagModel
    {
         {'|',' '},
         {'|','/'},
         {'|','\\'}
    };


public:
    LevelEndFlag(const int x, const int y) :GameObject(x, y){ model = flagModel;}

protected:
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override { return 0; }
};