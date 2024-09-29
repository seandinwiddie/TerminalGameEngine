#pragma once
#include "GameObject.h"
#include "Event.h"

class Alien : public GameObject
{
friend class AliensController;

//------------------------------------------------------ Settings
private:
	static const size_t PROJECTILE_SPEED = 8;

//------------------------------------------------------ Fields
public:
	Event<GameObject*> OnDestroyEvent;

private:
	size_t gridIndexX;
	size_t gridIndexY;

protected:
	bool isFirsAnimationFrameTime;
//------------------------------------------------------ Methods
public:
	Alien(int xPos, int yPos, size_t xIndexInFormation, size_t yIndexInFormation) :
		GameObject(xPos, yPos), gridIndexX(xIndexInFormation), gridIndexY(yIndexInFormation) { }

public:
	virtual bool CanExitScreenSpace() const override { return false; }
	size_t GetIndexInGridX() { return gridIndexX; }
	size_t GetIndexInGridY() { return gridIndexY; }
	virtual size_t GetScore() const = 0;
	void Shot();

protected:
	virtual double GetGravityScale() const override { return 0; }
	virtual void OnDestroy() override;
	virtual void Update();
	virtual void StepAnimation() = 0;
};