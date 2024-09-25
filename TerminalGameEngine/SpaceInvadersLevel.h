#pragma once
#include "Level.h"

// 11 x 4 -> 44
// + 2 alieni -> 52
// + 12 padding -> 64
// spazi = 1x10 -> 10 -> 74

class SpaceInvadersLevel : public Level
{
//------------------------------------------------------------------- Fields
private:
    static const size_t ALIEN_WIDTH = 4;
    static const size_t ALIEN_HEIGHT = 2;

    static const size_t ALIENS_ROWS_COUNT = 5;
    static const size_t ALIENS_COLUMNS_COUNT = 11;
    static const size_t SPACE_BETWEEN_ALIENS_X = 2;
    static const size_t SPACE_BETWEEN_ALIENS_Y = 1;

    static const size_t ALIENS_SPACE_FROM_MARGINS_X = 4;
    static const size_t ALIENS_SPACE_FROM_TOP_MARGIN = 3;

//------------------------------------------------------------------- Methods
public:
    virtual int GetWorldSizeX() const override;
    virtual int GetWorldSizeY() const override { return 50; }
    virtual int GetScreenPadding() const override { return 6; }

    virtual void LoadInSimulation() override;
    virtual void NotifyGameOver() override;

protected:
    virtual void Update()override;
    virtual double ShowGameOverScreenDelay() const { return 1.5; }
    virtual void OnPostGameOverDelayEnded() override;
    void ShowGameOverScreen();

private:
    void AddAliensToSimulation();
    void AddAliensRowToSimulation(int posY);
};