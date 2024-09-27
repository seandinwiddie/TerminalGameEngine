#pragma once
#include "Level.h"

class Alien;
class AliensController;

// 11 x 4 -> 44
// + 2 alieni -> 52
// + 12 padding -> 64
// spazi = 1x10 -> 10 -> 74

using type_info = std::type_info;

class SpaceInvadersLevel : public Level
{
//------------------------------------------------------------------- World settings
private:
    static const size_t ALIEN_WIDTH = 4;
    static const size_t ALIEN_HEIGHT = 2;

    static const size_t ALIENS_COUNT_Y = 5;
    static const size_t ALIENS_COUNT_X = 11;
    static const size_t SPACE_BETWEEN_ALIENS_X = 2;
    static const size_t SPACE_BETWEEN_ALIENS_Y = 1;

    static const size_t ALIENS_SPACE_FROM_MARGINS_X = 4;
    static const size_t ALIENS_SPACE_FROM_TOP_MARGIN = 3;

//------------------------------------------------------------------- Fields
private:
    size_t health = 3;
    size_t waveNumber = 5;
    size_t score = 0;

//------------------------------------------------------------------- Methods
public:
    virtual int GetWorldSizeX() const override;
    virtual int GetWorldSizeY() const override { return 50; }
    virtual int GetScreenPadding() const override { return 6; }

    virtual void LoadInSimulation() override;
    virtual void NotifyGameOver() override;

    size_t GetWaveNumber() { return waveNumber; }

    void IncreasePlayerScore(size_t increment);

protected:
    virtual void Update()override;
    virtual double ShowGameOverScreenDelay() const { return 0.1; }
    virtual void OnPostGameOverDelayEnded() override;
    void ShowGameOverScreen();

private:
    void LoadAliens(AliensController* controller);
    void LoadPlayerTank();

    void InitHeader();
    void PrintScore();
    void PrintHealth();
    void PrintWave();
    
    const type_info& GetAlienTypeForRow(int rowIndex);
    void AddAliensRowToSimulation(int yPos, int rowIndex, AliensController* controller);
    Alien* CreateAlienOfType (const type_info& alienType, int xPos, int yPos, int xIndex, int yIndex);
};