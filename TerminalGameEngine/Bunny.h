#pragma once

#include "Config.h"
#include "GameObject.h"
#include "InputUtils.h"
#include "AudioManager.h"
#include "TimeHelper.h"
#include "Obstacle.h"
#include "Simulation.h"
#include "Terminal.h"

#include <string>

class Level;

class Bunny : public GameObject
{
    enum class State
    {
        idle,
        walking,
        jumpingUp,
        jumpingDown,
        defeated
    };
    
//---------------------------------------------------------- Model
private:
    static const char NOSE_CHAR = '.';
    static const char EYE_CHAR = 'O';
    static const char GAMEOVER_EYE_CHAR = '*';
    static const char CHEST_CHAR = ':';

    static const std::vector<std::vector<char>> walkLeftModel;
    static const std::vector<std::vector<char>> walkRightModel;
    static const std::vector<std::vector<char>> jumpRightModel;
    static const std::vector<std::vector<char>> jumpLeftModel;
    static const std::vector<std::vector<char>> defeatedModel;
    static const std::vector<std::vector<char>> idleModelRight;
    static const std::vector<std::vector<char>> idleModelLeft;

    Level* level;

//---------------------------------------------------------- Fields

    static const uint JUMP_HEIGHT = 10;
    static constexpr double MOVE_UP_SPEED = 24;
    static constexpr double MOVE_DOWN_SPEED = 24;
    static constexpr double MOVE_DOWN_CONTROLLED_SPEED = 8;
    static constexpr double SIDE_MOVEMENT_SPEED = 24;
    static constexpr double STEP_ANIM_EVERY_SECONDS = 0.7f;

    State state;
    double lastTimeMovedOnX = 0;
    int previousPositionX;
    int jumpStartingY = -1;

//---------------------------------------------------------- Methods
public:
    Bunny(int xPos, int yPos, Level* level);
   
    virtual bool CanExitScreenSpace() const override { return false; }
    virtual double GetGravityScale() const override;
    virtual int GetColor() const { return Terminal::GREEN; }

protected:
    void Update() override;
    virtual void Move(Direction direction, double moveSpeed) override;
    virtual void OnCollisionEnter(GameObject* other, Direction collisionDirection) override;
    virtual void OnCollisionExit(Direction collisionDirection) override {}
    virtual void InitModel() { SetModel(idleModelLeft); }

private:
    std::vector<std::vector<char>> jumpingModel;
    std::vector<std::vector<char>> idleModel;
    std::vector<std::vector<char>> walkingModel;

    bool IsJumping() const { return state == State::jumpingDown || state == State::jumpingUp; }
    void SetState(State newState);
    void UpdateModel();
    void HandleIdleWalkState();
    void HandleVerticalMovement();
    void HandleHorizontalMovement();
    void HandleSounds(State oldState, State newState);
    bool IsTouchingGround() { return collidingDirections[static_cast<int>(Direction::down)]; }
    bool IsJumping() { return state == State::jumpingDown || state == State::jumpingUp; }

#pragma endregion Methods
};