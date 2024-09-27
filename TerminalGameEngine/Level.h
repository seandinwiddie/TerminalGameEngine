#pragma once

#include "ISimulationEntity.h"
#include "Terminal.h"

#include <vector>
#include "Frame.h"

class Level : public ISimulationEntity
{
    friend class Simulation;

 //---------------------------------------------------------- Settings
private:
    constexpr static double PRESS_ANY_KEY_TO_TERMINATE_GAME_DELAY = 1.5;

//---------------------------------------------------------- Fields
private:
    bool hasCalledOnPostGameOverDelayEnded = false;
    double gameOverTime = -1;
    double levelStartedTime = 0;
    bool isTerminated = false;

protected:
    Frame gameOverWindow;

//---------------------------------------------------------- Methods
public:   
    virtual void NotifyGameOver();
    virtual int GetWorldSizeX() const = 0;
    virtual int GetWorldSizeY() const = 0;
    virtual int GetScreenPadding() const = 0;
    virtual int GetMarginsColor() const { return Terminal::BLUE_DARK; }
    virtual const string GetBackgroundFileName()const { return ""; }
    virtual int GetBackgroundColor() const { return Terminal::BLUE_DARK; }

    double GetLevelTime() const;
    bool IsGameOver() const { return gameOverTime > -1; }
    bool IsTerminated() const { return isTerminated; }

    //todo try to merge this with simulation printer ones
    //todo try to use this in other levels
    virtual int GetScreenMaxX() { return GetWorldSizeX() - GetScreenPadding()*2; }
    virtual int GetScreenMaxY() { return GetWorldSizeY() - GetScreenPadding()*2; }

protected:
    virtual double ShowGameOverScreenDelay() const = 0;
    virtual void Update() override;
    virtual void OnPostGameOverDelayEnded() { hasCalledOnPostGameOverDelayEnded = true; }
    virtual void LoadInSimulation();
    virtual string GetGameOverWindowPath() { return ""; }

    bool IsPostGameOverPauseEnded() const;
    bool CanPlayerPressKeyToRestartGame() const;
    void Terminate() { isTerminated = true; }

};