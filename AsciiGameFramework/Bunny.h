#pragma once

#include "CollidingObject.h"
#include "InputUtils.h"
#include "AudioManager.h"
#include "TimeUtils.h"
#include "Obstacle.h"
#include "Simulation.h"

#include <string>

class Level;

class Bunny : public CollidingObject
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
    static const unsigned char NOSE_CHAR = '.';
    static const unsigned char EYE_CHAR = 'O';
    static const unsigned char GAMEOVER_EYE_CHAR = '*';
    static const unsigned char CHEST_CHAR = ':';

    static const std::vector<std::vector<unsigned char>> walkLeftModel;
    static const std::vector<std::vector<unsigned char>> walkRightModel;
    static const std::vector<std::vector<unsigned char>> jumpRightModel;
    static const std::vector<std::vector<unsigned char>> jumpLeftModel;
    static const std::vector<std::vector<unsigned char>> defeatedModel;
    static const std::vector<std::vector<unsigned char>> idleModelRight;
    static const std::vector<std::vector<unsigned char>> idleModelLeft;

    Level* level;

//---------------------------------------------------------- Fields

    static constexpr unsigned int JUMP_HEIGHT = 10;
    static constexpr float MOVE_UP_SPEED = 3;
    static constexpr float MOVE_DOWN_SPEED = 3;
    static constexpr float MOVE_DOWN_CONTROLLED_SPEED = 0.8;
    static constexpr float SIDE_MOVEMENT_SPEED = 3.0;
    static constexpr float STEP_ANIM_EVERY_SECONDS = 0.7f;

    State state;
    float lastTimeMovedOnX = 0;
    int previousPositionX;
    int jumpStartingY = -1;

//---------------------------------------------------------- Methods
public:
    Bunny(int xPos, int yPos, Level* level);
    void Update() override;

    virtual bool CanExitScreenSpace() const override { return false; }
    virtual float GetGravityScale() const override;

protected:
    virtual void Move(Direction direction, float moveSpeed) override;
    virtual void OnCollisionEnter(CollidingObject* other, Direction collisionDirection) override;
    virtual void OnCollisionExit(Direction collisionDirection) override {}

private:
    std::vector<std::vector<unsigned char>> jumpingModel;
    std::vector<std::vector<unsigned char>> idleModel;
    std::vector<std::vector<unsigned char>> walkingModel;

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